//
// Created by Alexander Fedosov on 2019-06-21.
//

#include "AudioNode.h"

void AudioNode::render() {
    if (!hasInputs && !hasOutputs) return;

    inputBuffer.assign(audioContextInfo.framesInBlock, 0);
    for (auto input: inputs) {
        input->render();
        for (size_t i = 0; i < input->outputBuffer.size(); i++) {
            inputBuffer[i] = inputBuffer[i] + input->outputBuffer[i];
        }
    }

    transform();

    if (hasOutputs) {
        outputBuffer = inputBuffer;
    }
}

void AudioNode::transform() {
    // implement any dsp transformations here
}

void AudioNode::updateAudioContext(AudioContextInfo audioContextInfo) {
    this->audioContextInfo = audioContextInfo;
    this->audioContextHasChanged();
}

void AudioNode::audioContextHasChanged() {
    outputBuffer.assign(audioContextInfo.framesInBlock, 0);
    inputBuffer.assign(audioContextInfo.framesInBlock, 0);
    for (auto input: inputs) {
        input->updateAudioContext(audioContextInfo);
    }
}

void AudioNode::addInput(std::shared_ptr<AudioNode> audioNode) {
    if (!hasInputs)
        return;
    inputs.push_back(audioNode);
    this->audioContextHasChanged();
}

