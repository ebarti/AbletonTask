//
// Created by Eloi on 9/20/20.
//

#include "ReverseAudioModule.h"

//-----------------------------------------------------------------------------
// ReverseAudioModule : constructor
//-----------------------------------------------------------------------------
ReverseAudioModule::ReverseAudioModule(std::string name)
:NoopAudioModule(std::move(name)){
    // Nothing to do
}

//-----------------------------------------------------------------------------
// ReverseAudioModule : destructor
//-----------------------------------------------------------------------------
ReverseAudioModule::~ReverseAudioModule() = default;

//-----------------------------------------------------------------------------
// Implements IAudioModule::GetType
//-----------------------------------------------------------------------------
IAudioModule::AudioModuleType ReverseAudioModule::GetType() const{
    return AudioModuleType::reverse;
}

//-----------------------------------------------------------------------------
// overrides NoopAudioModule::executeModule_Internal
//-----------------------------------------------------------------------------
std::string ReverseAudioModule::executeModule_Internal(std::string iCurrentString) {
    // This module reverses the input string
    std::string retStr(iCurrentString.rbegin(), iCurrentString.rend());
    return retStr;
}
