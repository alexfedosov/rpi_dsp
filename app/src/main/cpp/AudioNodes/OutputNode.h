//
// Created by Alexander Fedosov on 2019-06-22.
//

#ifndef GROOVEBOX_OUTPUTNODE_H
#define GROOVEBOX_OUTPUTNODE_H


#include "AudioNode.h"

class OutputNode: public AudioNode {
public:
    OutputNode();
    void writeNextAudioBlock(float *audioData);
};


#endif //GROOVEBOX_OUTPUTNODE_H
