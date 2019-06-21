//
// Created by Alexander Fedosov on 2019-06-21.
//

#ifndef GROOVEBOX_OSCILATOR_H
#define GROOVEBOX_OSCILATOR_H


#include <atomic>
#include <stdint.h>

class Oscillator {
public:
    void setFrequency(double frequency);
    void setWaveOn(bool isWaveOn);
    void setSampleRate(int32_t sampleRate);
    void render(float *audioData, int32_t numFrames, bool mix);

private:
    std::atomic<bool> isWaveOn_{true};
    double phase_ = 0.0;
    double phaseIncrement_ = 0.0;
    int32_t sampleRate = 0;
    std::atomic<double > frequency {0};
};


#endif //GROOVEBOX_OSCILATOR_H
