#include <jni.h>
#include <SDL.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <unistd.h>
extern "C" {
#include "host.h"
#include "win32hle.h"
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_arcadelab_spinwin_MainActivity_nativeEngineStatus(JNIEnv* env, jobject) {
    SDL_version version{};
    SDL_GetVersion(&version);
    char message[128];
    SDL_snprintf(message, sizeof(message),
                 "Spin & Win native runtime linked • SDL2 %u.%u.%u",
                 version.major, version.minor, version.patch);
    return env->NewStringUTF(message);
}

extern "C" JNIEXPORT void JNICALL
Java_com_arcadelab_spinwin_SDLGameActivity_nativeConfigureFileTrace(JNIEnv* env, jobject, jstring logPath) {
    if (logPath == nullptr) return;
    const char* path = env->GetStringUTFChars(logPath, nullptr);
    if (path == nullptr) return;
    setenv("HLE_FILETRACE", "1", 1);
    if (freopen(path, "a", stderr) == nullptr) {
        fprintf(stderr, "[filetrace] Cannot open log file: %s\\n", path);
    } else {
        fprintf(stderr, "[filetrace] Logging enabled: %s\\n", path);
        fflush(stderr);
    }
    env->ReleaseStringUTFChars(logPath, path);
}

/* SDLActivity supplies the imported game directory as argv[1]. */
extern "C" int SDL_main(int argc, char** argv) {
    if (argc < 2 || !argv || !argv[1] || !argv[1][0]) {
        SDL_Log("Spin & Win: game folder argument is missing");
        return 10;
    }
    const std::string gameDir(argv[1]);
    /* Log original game file opens so save-file paths can be identified. */
    setenv("HLE_FILETRACE", "1", 1);
    if (chdir(gameDir.c_str()) != 0) {
        SDL_Log("Spin & Win: cannot open game folder %s", gameDir.c_str());
        return 11;
    }
    const std::string exePath = gameDir + "/SpinWin.exe";
    hle_set_drive('C', gameDir.c_str());
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) != 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 12;
    }
    recomp_host_init();
    if (hle_screen_open("Spin & Win", 1, 0) != 0) {
        SDL_Log("Could not open the game display");
        SDL_Quit();
        return 13;
    }
    if (recomp_host_boot_permissive(exePath.c_str()) != 0) {
        SDL_Log("Could not load SpinWin.exe");
        SDL_Quit();
        return 14;
    }
    SDL_Log("Starting reconstructed Spin & Win executable");
    const uint32_t result = recomp_host_run();
    SDL_Log("Spin & Win exited with code %u", result);
    SDL_Quit();
    return static_cast<int>(result);
}
