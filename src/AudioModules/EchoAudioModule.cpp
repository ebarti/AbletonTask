//
// Created by Eloi on 9/20/20.
//

#include "EchoAudioModule.h"
//-----------------------------------------------------------------------------
// EchoAudioModule : constructor
//-----------------------------------------------------------------------------
EchoAudioModule::EchoAudioModule(std::string name)
:NoopAudioModule(std::move(name)){
    // Nothing to do
}

//-----------------------------------------------------------------------------
// EchoAudioModule : destructor
//-----------------------------------------------------------------------------
EchoAudioModule::~EchoAudioModule() = default;

//-----------------------------------------------------------------------------
// Implements IAudioModule::GetType
//-----------------------------------------------------------------------------
IAudioModule::AudioModuleType EchoAudioModule::GetType() const{
    return AudioModuleType::echo;
}

//-----------------------------------------------------------------------------
// overrides NoopAudioModule::executeModule_Internal
//-----------------------------------------------------------------------------
std::string EchoAudioModule::executeModule_Internal(std::string iCurrentString) {
    // This module echoes the input string
    return iCurrentString + iCurrentString;
}
