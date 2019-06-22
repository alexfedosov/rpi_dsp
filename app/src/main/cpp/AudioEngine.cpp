//
// Created by Alexander Fedosov on 2019-06-21.
//
#include "AudioEngine.h"
#include <vector>
#include "logging_macros.h"

constexpr int32_t kBufferSizeInBursts = 4;

bool AudioEngine::start(int deviceId) {
    oboe::AudioStreamBuilder *builder = new oboe::AudioStreamBuilder();

    AudioContextInfo audioContextInfo;
    audioContextInfo.framesInBlock = 1024;

    oboe::Result result = builder->
            setDeviceId(deviceId)->
            setChannelCount(1)->
            setFormat(AudioFormat::Float)->
            setFramesPerCallback(audioContextInfo.framesInBlock)->
            setSharingMode(oboe::SharingMode::Exclusive)->
            setPerformanceMode(oboe::PerformanceMode::LowLatency)->
            setCallback(this)->
            openStream(&audioStream);

    if (result == Result::OK) {
        audioContextInfo.sampleRate = audioStream->getSampleRate();
        audioContextInfo.channelCount = audioStream->getChannelCount();
        outputNode.updateAudioContext(audioContextInfo);

        std::vector<float> freq = { 110.00, 277.18, 164.81};

        for (int i = 0; i < freq.size(); i++) {
            std::shared_ptr<SineWaveOscillatorNode> oscillator (new SineWaveOscillatorNode(freq[i]));
            outputNode.addInput(oscillator);
        }

        audioStream->setBufferSizeInFrames(audioStream->getFramesPerBurst() * kBufferSizeInBursts);
        Result startResult = audioStream->requestStart();
        LOGI("Audio stream sample rate: %d %s", audioStream->getSampleRate(), convertToText(startResult));

    }
    delete(builder);
    return true;
}

DataCallbackResult AudioEngine::onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) {
    LOGI("num frames %d", numFrames);
    outputNode.writeNextAudioBlock(static_cast<float *>(audioData));
    return DataCallbackResult::Continue;
}

void AudioEngine::onErrorBeforeClose(AudioStream *oboeStream, Result error) {
    LOGE("onErrorBeforeClose", convertToText(error));
}

void AudioEngine::onErrorAfterClose(AudioStream *oboeStream, Result error) {
    LOGE("onErrorAfterClose", convertToText(error));
}
