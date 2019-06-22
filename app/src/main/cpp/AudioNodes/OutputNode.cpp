//
// Created by Alexander Fedosov on 2019-06-22.
//

#include "OutputNode.h"
#include "../logging_macros.h"

OutputNode::OutputNode() {
    this->hasInputs = true;
    this->hasOutputs = false;
}

void OutputNode::writeNextAudioBlock(float *audioData) {
    render();
    for (auto i = 0; i < inputBuffer.size(); ++i) {
        for (int ci = 0; ci < this->audioContextInfo.channelCount; ++ci) {
            audioData[i * this->audioContextInfo.channelCount + ci] = inputBuffer[i];
        }
    }
}
