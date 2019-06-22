//
// Created by Alexander Fedosov on 2019-06-21.
//

#ifndef GROOVEBOX_AUDIOENGINE_H
#define GROOVEBOX_AUDIOENGINE_H

#include <stdlib.h>
#include <oboe/Oboe.h>
#include "atomicops.h"
#include "readerwriterqueue.h"
#include "AudioNodes/AudioContext.h"
#include "AudioNodes/SineWaveOscillatorNode.h"
#include "AudioNodes/OutputNode.h"

using namespace oboe;

class AudioEngine: AudioStreamCallback {
public:
    bool start(int deviceId);
    std::shared_ptr<moodycamel::ReaderWriterQueue<float>> queue;

    DataCallbackResult onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames);
    void onErrorBeforeClose(AudioStream *oboeStream, Result error);
    void onErrorAfterClose(AudioStream *oboeStream, Result error);

private:
    OutputNode outputNode;
    oboe::AudioStream *audioStream;
};


#endif //GROOVEBOX_AUDIOENGINE_H
