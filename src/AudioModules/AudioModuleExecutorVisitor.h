//
// Created by Eloi on 9/21/20.
//

#ifndef ABLETONTASK1_AUDIOMODULEEXECUTORVISITOR_H
#define ABLETONTASK1_AUDIOMODULEEXECUTORVISITOR_H

#include "AudioModuleBaseVisitor.h"
class AudioModuleExecutorVisitor: public AudioModuleBaseVisitor {
public:
    // Constructor & destructor
    AudioModuleExecutorVisitor();
    virtual ~AudioModuleExecutorVisitor();

protected:
    //-----------------------------------------------------------------------------
    // AudioModuleBaseVisitor methods
    //-----------------------------------------------------------------------------
    void visit_impl(IAudioModule &ipAudioModule) override;
};


#endif //ABLETONTASK1_AUDIOMODULEEXECUTORVISITOR_H
