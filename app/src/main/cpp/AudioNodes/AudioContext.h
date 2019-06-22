//
// Created by Alexander Fedosov on 2019-06-22.
//

#ifndef GROOVEBOX_AUDIOCONTEXT_H
#define GROOVEBOX_AUDIOCONTEXT_H


struct AudioContextInfo {
    int32_t channelCount;
    u_int32_t framesInBlock;
    int32_t sampleRate;
};

#endif //GROOVEBOX_AUDIOCONTEXT_H
