#include <jni.h>
extern "C" JNIEXPORT jstring JNICALL
Java_com_arcadelab_spinwin_MainActivity_nativeEngineStatus(JNIEnv* env, jobject) {
    return env->NewStringUTF("Placeholder: the x86 Windows game engine still needs porting.");
}
