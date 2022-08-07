//
// Created by Eloi on 9/22/20.
//

#include "AudioModuleCyclicReferenceFinder.h"

//-----------------------------------------------------------------------------
// AudioModuleCyclicReferenceFinder : constructor
//-----------------------------------------------------------------------------
AudioModuleCyclicReferenceFinder::AudioModuleCyclicReferenceFinder()
:AudioModuleBaseVisitor()
,_ipStartAudioModule(nullptr)
,_isCyclicReference(false){
    // Nothing to do
}

//-----------------------------------------------------------------------------
// AudioModuleCyclicReferenceFinder : destructor
//-----------------------------------------------------------------------------
AudioModuleCyclicReferenceFinder::~AudioModuleCyclicReferenceFinder() = default;

//-----------------------------------------------------------------------------
// AudioModuleCyclicReferenceFinder : setStartAudioModule
//-----------------------------------------------------------------------------
void AudioModuleCyclicReferenceFinder::setStartAudioModule(IAudioModule *ipStartAudioModule) {
    _ipStartAudioModule =ipStartAudioModule;
}

//-----------------------------------------------------------------------------
// AudioModuleCyclicReferenceFinder : isCyclicReference
//-----------------------------------------------------------------------------
bool AudioModuleCyclicReferenceFinder::isCyclicReference() const {
    return _isCyclicReference;
}

//-----------------------------------------------------------------------------
// Implements AudioModuleBaseVisitor::visit_impl
//-----------------------------------------------------------------------------
void AudioModuleCyclicReferenceFinder::visit_impl(IAudioModule &ipAudioModule) {
    IAudioModule * pAudioModule = &ipAudioModule;
    if(_ipStartAudioModule && pAudioModule && _ipStartAudioModule == pAudioModule)
        _isCyclicReference = true;
}
