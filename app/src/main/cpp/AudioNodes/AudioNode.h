//
// Created by Alexander Fedosov on 2019-06-21.
//

#ifndef GROOVEBOX_AUDIONODE_H
#define GROOVEBOX_AUDIONODE_H

#include <stdlib.h>
#include <vector>
#include <memory.h>
#include "AudioContext.h"


class AudioNode {
public:
    void updateAudioContext(AudioContextInfo audioContextInfo);
    void render();

    virtual void transform();
    void addInput(std::shared_ptr<AudioNode> audioNode);

protected:
    bool hasInputs;
    bool hasOutputs;
    AudioContextInfo audioContextInfo;
    std::vector<float> inputBuffer;
    std::vector<float> outputBuffer;
    std::vector<std::shared_ptr<AudioNode>> inputs;

    void audioContextHasChanged();
};


#endif //GROOVEBOX_AUDIONODE_H
