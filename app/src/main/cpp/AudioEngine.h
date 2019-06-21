//
// Created by Alexander Fedosov on 2019-06-21.
//

#ifndef GROOVEBOX_AUDIOENGINE_H
#define GROOVEBOX_AUDIOENGINE_H

#include <stdlib.h>
#include <vector>
#include <oboe/Oboe.h>
#include "Oscillator.h"

using namespace oboe;

class AudioEngine: AudioStreamCallback {
public:
    bool start(int deviceId);

    DataCallbackResult onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames);
    void onErrorBeforeClose(AudioStream *oboeStream, Result error);
    void onErrorAfterClose(AudioStream *oboeStream, Result error);
private:
    std::vector<Oscillator *> oscillators;
    oboe::AudioStream *audioStream;
};


#endif //GROOVEBOX_AUDIOENGINE_H
