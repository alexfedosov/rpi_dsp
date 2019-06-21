//
// Created by Alexander Fedosov on 2019-06-21.
//

#include <jni.h>
#include "AudioEngine.h"

static AudioEngine *audioEngine = new AudioEngine();

extern "C" {

JNIEXPORT void JNICALL
Java_com_alexfedosov_groovebox_MainActivity_startEngine(JNIEnv *env, jobject instance, jint deviceId) {
    audioEngine->start(deviceId);
}

}
