cmake_minimum_required(VERSION 3.22.1)
project(spinwin_android LANGUAGES C CXX)

include(FetchContent)

# Build SDL2 from its official source for each Android ABI.
# SDL2's Android platform backend is enabled automatically by the NDK toolchain.
set(SDL_SHARED OFF CACHE BOOL "Build SDL2 as a static library" FORCE)
set(SDL_STATIC ON CACHE BOOL "Build SDL2 static library" FORCE)
set(SDL_TEST OFF CACHE BOOL "Do not build SDL2 test programs" FORCE)
set(SDL_TESTS OFF CACHE BOOL "Do not build SDL2 test programs" FORCE)
set(SDL2_DISABLE_INSTALL ON CACHE BOOL "Skip SDL2 install rules" FORCE)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.11
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SDL2)

# SDL2_ttf supplies the font rendering used by the existing Win32 GDI layer.
# Build its FreeType dependency from the upstream submodule for Android.
set(SDL2TTF_VENDORED ON CACHE BOOL "Build FreeType from source" FORCE)
set(SDL2TTF_HARFBUZZ OFF CACHE BOOL "Disable optional text shaping" FORCE)
set(SDL2TTF_SAMPLES OFF CACHE BOOL "Do not build SDL_ttf samples" FORCE)
set(SDL2TTF_INSTALL OFF CACHE BOOL "Do not install SDL_ttf" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build SDL_ttf statically" FORCE)
FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.22.0
    GIT_SHALLOW TRUE
    GIT_SUBMODULES external/freetype
    GIT_SUBMODULES_RECURSE TRUE
)
FetchContent_MakeAvailable(SDL2_ttf)

# The HLE sources include SDL_ttf using the conventional SDL2/ header path.
FetchContent_GetProperties(SDL2_ttf SOURCE_DIR SDL2_TTF_SOURCE_DIR)
set(SPINWIN_TTF_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/sdl2-ttf-include)
file(MAKE_DIRECTORY ${SPINWIN_TTF_INCLUDE_DIR}/SDL2)
configure_file(${SDL2_TTF_SOURCE_DIR}/SDL_ttf.h
               ${SPINWIN_TTF_INCLUDE_DIR}/SDL2/SDL_ttf.h COPYONLY)

add_library(spinwin_android SHARED native-lib.cpp)
target_compile_features(spinwin_android PRIVATE cxx_std_17)
target_include_directories(spinwin_android PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../runtime/win32hle
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../runtime/recomp32
)
target_link_libraries(spinwin_android PRIVATE SDL2-static)


# Compile the reconstructed Spin & Win machine-code translation as an isolated
# object target first. It is intentionally not linked into the APK yet: the
# Win32 HLE host, PE loader, and FMOD imports still need to be wired up.
set(SPINWIN_RECON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/reconstructed)
# Compile the verified split translation units. The monolithic source exceeds
# practical source-reader/compiler limits and is not used by this Android build.
file(GLOB SPINWIN_RECOMP_SPLIT_SOURCES CONFIGURE_DEPENDS
    "${SPINWIN_RECON_DIR}/c/recomp_0000_split/recomp_0000_part*.c"
)
if(NOT SPINWIN_RECOMP_SPLIT_SOURCES)
    message(FATAL_ERROR "No split recomp_0000 source files found")
endif()
add_library(spinwin_reconstructed OBJECT
    ${SPINWIN_RECOMP_SPLIT_SOURCES}
    ${SPINWIN_RECON_DIR}/c/recomp_dispatch.c
)
target_include_directories(spinwin_reconstructed PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../runtime/recomp32
    ${SPINWIN_RECON_DIR}/c
    ${SPINWIN_RECON_DIR}/c/recomp_0000_split
)
target_compile_definitions(spinwin_reconstructed PRIVATE RECOMP_GENERATED_CODE)
# The generated function bodies call other lifted functions before their
# definitions; preload the generated prototypes to satisfy strict Clang C99.
target_compile_options(spinwin_reconstructed PRIVATE
    -include ${SPINWIN_RECON_DIR}/c/recomp_funcs.h
)

# Compile the portable Win32 compatibility host used by the reconstructed PE.
# Keep this as an object target while Android-specific display/audio wiring is
# being added; this validates the host sources with the NDK without linking an
# incomplete runtime into the app yet.
set(SPINWIN_HLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../runtime/win32hle)
add_library(spinwin_win32hle OBJECT
    ${SPINWIN_HLE_DIR}/host_lite.c
    ${SPINWIN_HLE_DIR}/guest_mem.c
    ${SPINWIN_HLE_DIR}/pe_loader.c
    ${SPINWIN_HLE_DIR}/host.c
    ${SPINWIN_HLE_DIR}/hle_path.c
    ${SPINWIN_HLE_DIR}/module.c
    ${SPINWIN_HLE_DIR}/shell32.c
    ${SPINWIN_HLE_DIR}/fmod.c
    ${SPINWIN_HLE_DIR}/kernel32.c
    ${SPINWIN_HLE_DIR}/kernel32_ext.c
    ${SPINWIN_HLE_DIR}/kernel32_crt.c
    ${SPINWIN_HLE_DIR}/user32.c
    ${SPINWIN_HLE_DIR}/gdi32.c
    ${SPINWIN_HLE_DIR}/winmm.c
    ${SPINWIN_HLE_DIR}/ddraw.c
    ${SPINWIN_HLE_DIR}/d3d.c
    ${SPINWIN_HLE_DIR}/d3d_raster.c
    ${SPINWIN_HLE_DIR}/screen.c
    ${SPINWIN_HLE_DIR}/gdidc.c
    ${SPINWIN_HLE_DIR}/dinput.c
    ${SPINWIN_HLE_DIR}/dsound.c
    ${SPINWIN_HLE_DIR}/advapi32.c
    ${SPINWIN_HLE_DIR}/storage.c
    ${SPINWIN_HLE_DIR}/lz32.c
    ${SPINWIN_HLE_DIR}/wsock32.c
    ${SPINWIN_HLE_DIR}/ole32.c
    ${SPINWIN_HLE_DIR}/mss.c
    ${SPINWIN_HLE_DIR}/bink.c
)
target_include_directories(spinwin_win32hle PRIVATE
    ${SPINWIN_HLE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../runtime/recomp32
    ${SPINWIN_TTF_INCLUDE_DIR}
)
target_link_libraries(spinwin_win32hle PRIVATE SDL2-static SDL2_ttf)
target_compile_features(spinwin_win32hle PRIVATE c_std_11)

# Compile the Android tap-to-Win32 input adapter as a separate object. It is
# not linked into the test screen yet; the game host will consume it once the
# PE runtime and SDL-backed display are connected.
add_library(spinwin_android_input OBJECT android_input_bridge.c)
target_include_directories(spinwin_android_input PRIVATE
    ${SPINWIN_HLE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../runtime/recomp32
)
target_link_libraries(spinwin_android_input PRIVATE SDL2-static)
target_compile_features(spinwin_android_input PRIVATE c_std_11)

# The 32-bit Android ABI can use direct guest virtual addresses, while the
# 64-bit ABI uses the HLE's 4-GB based guest-memory window. Keep the lifter
# and HLE memory models in sync for each ABI.
if(ANDROID_ABI STREQUAL "armeabi-v7a")
    target_compile_definitions(spinwin_reconstructed PRIVATE RECOMP_FLAT_MEMORY)
    target_compile_definitions(spinwin_win32hle PRIVATE HLE_FLAT)
endif()


# Android compatibility validation follows the API-23 Winsock fallback.
# Link the reconstructed engine and Win32 compatibility objects into the
# Android native library. SDL_main remains on the safe graphics test until
# runtime launch validation is complete.
target_link_libraries(spinwin_android PRIVATE
    spinwin_reconstructed
    spinwin_win32hle
    spinwin_android_input
    SDL2_ttf
)
