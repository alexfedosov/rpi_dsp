//
// Created by Alexander Fedosov on 2019-06-21.
//
#include "AudioEngine.h"
#include "logging_macros.h"

constexpr int32_t kBufferSizeInBursts = 4;

bool AudioEngine::start(int deviceId) {
    oboe::AudioStreamBuilder *builder = new oboe::AudioStreamBuilder();

    oboe::Result result = builder->
            setDeviceId(deviceId)->
            setChannelCount(2)->
            setFormat(AudioFormat::Float)->
            setSharingMode(oboe::SharingMode::Exclusive)->
            setPerformanceMode(oboe::PerformanceMode::LowLatency)->
            setCallback(this)->
            openStream(&audioStream);

    if (result == Result::OK) {
        double freq[3] = { 220.00, 277.18, 164.81};

        for (int i = 0; i < 3; i++) {
            Oscillator *oscillator = new Oscillator();
            oscillator->setSampleRate(audioStream->getSampleRate());
            oscillator->setFrequency(freq[i]);
            oscillators.push_back(oscillator);
        }
        audioStream->setBufferSizeInFrames(audioStream->getFramesPerBurst() * kBufferSizeInBursts);
        Result startResult = audioStream->requestStart();
        LOGI("Audio stream sample rate: %d %s", audioStream->getSampleRate(), convertToText(startResult));

    }
    delete(builder);
    return true;
}

DataCallbackResult AudioEngine::onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) {

    oscillators[0]->render(static_cast<float *>(audioData), numFrames, false);
    oscillators[1]->render(static_cast<float *>(audioData), numFrames, true);
    oscillators[2]->render(static_cast<float *>(audioData), numFrames, true);

    return DataCallbackResult::Continue;
}

void AudioEngine::onErrorBeforeClose(AudioStream *oboeStream, Result error) {
    LOGE("onErrorBeforeClose", convertToText(error));
}

void AudioEngine::onErrorAfterClose(AudioStream *oboeStream, Result error) {
    LOGE("onErrorAfterClose", convertToText(error));
}
