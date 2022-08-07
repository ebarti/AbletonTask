//
// Created by Eloi on 9/21/20.
//

#ifndef ABLETONTASK1_AUDIOMODULEINFEEDPROCESSORVISITOR_H
#define ABLETONTASK1_AUDIOMODULEINFEEDPROCESSORVISITOR_H

#include "AudioModuleBaseVisitor.h"
class AudioModuleInfeedProcessorVisitor: public AudioModuleBaseVisitor {
public:
    // Constructor & destructor
    AudioModuleInfeedProcessorVisitor();
    virtual ~AudioModuleInfeedProcessorVisitor();

protected:
    //-----------------------------------------------------------------------------
    // AudioModuleBaseVisitor methods
    //-----------------------------------------------------------------------------
    void visit_impl(IAudioModule &ipAudioModule) override;
};


#endif //ABLETONTASK1_AUDIOMODULEINFEEDPROCESSORVISITOR_H
