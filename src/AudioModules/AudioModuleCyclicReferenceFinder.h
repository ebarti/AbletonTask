//
// Created by Eloi on 9/22/20.
//

#ifndef ABLETONTASK1_AUDIOMODULECYCLICREFERENCEFINDER_H
#define ABLETONTASK1_AUDIOMODULECYCLICREFERENCEFINDER_H

#include "AudioModuleBaseVisitor.h"

class AudioModuleCyclicReferenceFinder: public AudioModuleBaseVisitor {
public:
    // Constructor & destructor
    AudioModuleCyclicReferenceFinder();
    virtual ~AudioModuleCyclicReferenceFinder();

    //-----------------------------------------------------------------------------
    // AudioModuleCyclicReferenceFinder methods
    //-----------------------------------------------------------------------------
    void setStartAudioModule(IAudioModule* ipStartAudioModule);
    bool isCyclicReference() const;

protected:
    //-----------------------------------------------------------------------------
    // AudioModuleBaseVisitor methods
    //-----------------------------------------------------------------------------
    void visit_impl(IAudioModule &ipAudioModule) override;

private:
    IAudioModule * _ipStartAudioModule;
    bool _isCyclicReference;
};


#endif //ABLETONTASK1_AUDIOMODULECYCLICREFERENCEFINDER_H
