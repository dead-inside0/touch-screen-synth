#include <jni.h>
#include "AudioEngine.h"
#include <android/log.h>

static AudioEngine engine;

extern "C"
JNIEXPORT void JNICALL
Java_com_ernestlevkovich_touchsynth_MainActivity_initAudio(JNIEnv *env, jobject obj) {
    engine.init();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_ernestlevkovich_touchsynth_MainActivity_closeAudio(JNIEnv *env, jobject obj) {
    engine.close();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_ernestlevkovich_touchsynth_MainActivity_changeFrequency(JNIEnv *env, jobject obj, jfloat f) {
    engine.changeFreq(f);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_ernestlevkovich_touchsynth_MainActivity_changeAmplitude(JNIEnv *env, jobject obj,
                                                                 jfloat a) {
    engine.changeAmp(a);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_ernestlevkovich_touchsynth_MainActivity_playSynth(JNIEnv *env, jobject obj) {
    engine.play();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_ernestlevkovich_touchsynth_MainActivity_pauseSynth(JNIEnv *env, jobject obj) {
    engine.pause();
}