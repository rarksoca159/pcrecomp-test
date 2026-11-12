#include <jni.h>
#include <SDL.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_arcadelab_spinwin_MainActivity_nativeEngineStatus(JNIEnv* env, jobject) {
    SDL_version version{};
    SDL_GetVersion(&version);

    char message[128];
    SDL_snprintf(message, sizeof(message),
                 "SDL2 native runtime linked: %u.%u.%u",
                 version.major, version.minor, version.patch);
    return env->NewStringUTF(message);
}
