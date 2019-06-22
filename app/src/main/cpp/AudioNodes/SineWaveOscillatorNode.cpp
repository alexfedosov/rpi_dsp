//
// Created by Alexander Fedosov on 2019-06-22.
//

#include "SineWaveOscillatorNode.h"
#include <math.h>

#define TWO_PI (3.14159 * 2)
#define AMPLITUDE 1

SineWaveOscillatorNode::SineWaveOscillatorNode(double frequency) {
    this->frequency.store(frequency);
    this->hasInputs = false;
    this->hasOutputs = true;
}


void SineWaveOscillatorNode::transform() {
    for (int i = 0; i < inputBuffer.size(); ++i) {
        inputBuffer[i] = (float) (sin(phase_) * AMPLITUDE);
        phase_ += (TWO_PI * this->frequency.load()) / (double) this->audioContextInfo.sampleRate;
        if (phase_ > TWO_PI) phase_ -= TWO_PI;
    }
}

void SineWaveOscillatorNode::setFrequency(double frequency) {
    this->frequency.store(frequency);
}
