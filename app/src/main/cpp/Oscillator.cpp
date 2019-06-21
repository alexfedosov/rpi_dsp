//
// Created by Alexander Fedosov on 2019-06-21.
//

#include "Oscillator.h"

#include "Oscillator.h"
#include <math.h>

#define TWO_PI (3.14159 * 2)
#define AMPLITUDE 2

void Oscillator::setSampleRate(int32_t sampleRate) {
    this->sampleRate = sampleRate;
}

void Oscillator::setWaveOn(bool isWaveOn) {
    isWaveOn_.store(isWaveOn);
}

void Oscillator::setFrequency(double frequency) {
    this->frequency.store(frequency);
}


void Oscillator::render(float *audioData, int32_t numFrames, bool mix) {

//    if (!isWaveOn_.load()) phase_ = 0;

    for (int i = 1; i < numFrames * 2; i+=2) {
//        if (isWaveOn_.load()) {

            // Calculates the next sample value for the sine wave.
            float nextSample = (float) (sin(phase_) * AMPLITUDE);

            if (mix) {
                audioData[i] = audioData[i] / 8 + nextSample / 2;
            } else {
                audioData[i] = nextSample;
            }


            // Increments the phase, handling wrap around.
            phase_ += (TWO_PI * this->frequency.load()) / (double) sampleRate;
            if (phase_ > TWO_PI) phase_ -= TWO_PI;
//
//        } else {
//            // Outputs silence by setting sample value to zero.
//            audioData[i] = 0;
//        }
    }
}
