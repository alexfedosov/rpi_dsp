//
// Created by Alexander Fedosov on 2019-06-21.
//

#include <jni.h>
#include <android/log.h>
#include <stdlib.h>
#include <thread>
#include "AudioEngine.h"
#include "atomicops.h"
#include "readerwriterqueue.h"

using namespace std;
using namespace moodycamel;

static JavaVM* jvm = 0;
static jobject activity = 0;

static AudioEngine *audioEngine = new AudioEngine();

thread jniUI;
std::shared_ptr<ReaderWriterQueue<float>> queue(new ReaderWriterQueue<float >(1));

extern "C" {

void renderJavaUI() {
    JNIEnv* jniEnv;
    jvm->AttachCurrentThread(&jniEnv, NULL);
    jclass clazz = jniEnv->GetObjectClass(activity);
    jmethodID setSampleDataMethodId = jniEnv->GetMethodID(clazz, "setSampleData", "([B)V");

    bool finished = false;
    while (!finished) {
        float length;
        bool succeeded = queue->try_dequeue(length);
        if (succeeded) {
            jbyteArray bytes = jniEnv->NewByteArray(static_cast<jsize>(length));
            jniEnv->CallVoidMethod(activity, setSampleDataMethodId, bytes);
        }
    }

}

JNIEXPORT void JNICALL
Java_com_alexfedosov_groovebox_MainActivity_nativeInit(JNIEnv *env, jobject thiz)
{
    env->GetJavaVM(&jvm);
    activity = env->NewGlobalRef(thiz);
    jniUI = thread(renderJavaUI);
}

JNIEXPORT void JNICALL
Java_com_alexfedosov_groovebox_MainActivity_startEngine(JNIEnv *env, jobject instance, jint deviceId) {
    audioEngine->queue = queue;
    audioEngine->start(deviceId);
}

}
