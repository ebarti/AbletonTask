//
// Created by Eloi on 9/20/20.
//

#include "DelayAudioModule.h"

//-----------------------------------------------------------------------------
// DelayAudioModule : constructor
//-----------------------------------------------------------------------------
DelayAudioModule::DelayAudioModule(std::string name)
:NoopAudioModule(std::move(name))
,_isInitialized(false)
,_previousString("hello"){
    // First statement is always "hello"
}

//-----------------------------------------------------------------------------
// DelayAudioModule : destructor
//-----------------------------------------------------------------------------
DelayAudioModule::~DelayAudioModule() = default;

//-----------------------------------------------------------------------------
// Implements IAudioModule::GetType
//-----------------------------------------------------------------------------
IAudioModule::AudioModuleType DelayAudioModule::GetType() const{
    return AudioModuleType::delay;
}

//-----------------------------------------------------------------------------
// Implements IAudioModule::isEmpty
//----------------------------------------------------------------------------
bool DelayAudioModule::isEmpty() const{
    // if the module has never run then it is not initialized
    //  This condition is mostly used for testing, as for "running" a (NoopAudioModule::isEmpty() && "" != _previousString) would suffice
    //  since a module will never be executed if it is not connected
    return (NoopAudioModule::isEmpty() && (!_isInitialized || (_isInitialized && _previousString.empty())));
}

//-----------------------------------------------------------------------------
// Implements IAudioModule::reset
//----------------------------------------------------------------------------
void DelayAudioModule::reset() {
    _isInitialized = false;
    _previousString = "hello";
    return NoopAudioModule::reset();
}


//-----------------------------------------------------------------------------
// overrides NoopAudioModule::executeModule_Internal
//-----------------------------------------------------------------------------
std::string DelayAudioModule::executeModule_Internal(std::string iCurrentString) {
    // This module delays the input string
    // A delay can only hold one element in its queue, so store directly in a string member variable
    std::string retStr;
    if(!_isInitialized && !iCurrentString.empty())
        _isInitialized = true;
    if(_isInitialized)
    {
        retStr = _previousString;
        _previousString = iCurrentString;
    }
    return retStr;
}
