//
// Created by Alexander Fedosov on 2019-06-22.
//

#ifndef GROOVEBOX_SINEWAVEOSCILLATORNODE_H
#define GROOVEBOX_SINEWAVEOSCILLATORNODE_H

#include "AudioNode.h"
#include "AudioContext.h"

class SineWaveOscillatorNode: public AudioNode {
public:
    SineWaveOscillatorNode(double frequency);

    void setFrequency(double frequency);
    void transform() override;

private:
    double phase_ = 0.0;
    double phaseIncrement_ = 0.0;
    std::atomic<double > frequency {0};
};


#endif //GROOVEBOX_SINEWAVEOSCILLATORNODE_H
