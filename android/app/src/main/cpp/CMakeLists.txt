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
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../runtime/recomp32
    ${SPINWIN_RECON_DIR}/c
)
target_compile_definitions(spinwin_reconstructed PRIVATE RECOMP_GENERATED_CODE)
