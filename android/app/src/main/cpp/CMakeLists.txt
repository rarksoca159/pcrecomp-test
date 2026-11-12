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

add_library(spinwin_android SHARED native-lib.cpp)
target_compile_features(spinwin_android PRIVATE cxx_std_17)
target_link_libraries(spinwin_android PRIVATE SDL2-static)


# Compile the reconstructed Spin & Win machine-code translation as an isolated
# object target first. It is intentionally not linked into the APK yet: the
# Win32 HLE host, PE loader, and FMOD imports still need to be wired up.
set(SPINWIN_RECON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/reconstructed)
add_library(spinwin_reconstructed OBJECT
    ${SPINWIN_RECON_DIR}/c/recomp_0000.c
    ${SPINWIN_RECON_DIR}/c/recomp_dispatch.c
)
target_include_directories(spinwin_reconstructed PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../runtime/recomp32
    ${SPINWIN_RECON_DIR}/c
)
target_compile_definitions(spinwin_reconstructed PRIVATE RECOMP_GENERATED_CODE)

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
    ${SPINWIN_HLE_DIR}/kernel32.c
    ${SPINWIN_HLE_DIR}/kernel32_ext.c
    ${SPINWIN_HLE_DIR}/kernel32_crt.c
    ${SPINWIN_HLE_DIR}/user32.c
    ${SPINWIN_HLE_DIR}/gdi32.c
    ${SPINWIN_HLE_DIR}/winmm.c
    ${SPINWIN_HLE_DIR}/ddraw.c
    ${SPINWIN_HLE_DIR}/dinput.c
    ${SPINWIN_HLE_DIR}/dsound.c
    ${SPINWIN_HLE_DIR}/advapi32.c
    ${SPINWIN_HLE_DIR}/storage.c
    ${SPINWIN_HLE_DIR}/lz32.c
    ${SPINWIN_HLE_DIR}/wsock32.c
    ${SPINWIN_HLE_DIR}/ole32.c
    ${SPINWIN_HLE_DIR}/mss.c
)
target_include_directories(spinwin_win32hle PRIVATE
    ${SPINWIN_HLE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../runtime/recomp32
)
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
