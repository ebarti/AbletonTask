//
// Created by Eloi on 9/17/20.
//
#include <algorithm>
#include "NoopAudioModule.h"
#include "../../include/AudioModules/IAudioModuleVisitor.h"
#include "../../include/AudioModules/AudioModuleUtils.h"
//-----------------------------------------------------------------------------
// NoopAudioModule : constructor
//-----------------------------------------------------------------------------
NoopAudioModule::NoopAudioModule(std::string name):
        _name(std::move(name))
, _parentModules()
, _childrenModules()
, _currentString("")
, _outfeedString(""){
    // Nothing to do
}

//-----------------------------------------------------------------------------
// NoopAudioModule : destructor
//-----------------------------------------------------------------------------
NoopAudioModule::~NoopAudioModule() = default;

//-----------------------------------------------------------------------------
// Implements IAudioModule::setInfeed
//-----------------------------------------------------------------------------
void NoopAudioModule::setInfeed(std::string iInfeedToken) {
    _infeedList.push(iInfeedToken);
}

//-----------------------------------------------------------------------------
// Implements IAudioModule::getInfeed
//-----------------------------------------------------------------------------
void NoopAudioModule::getInfeed(){
    // Clear current string
    _currentString = "";

    if(!_infeedList.empty()) {
        // Case where this module is the first module
        _currentString = _infeedList.front();
        _infeedList.pop();
    }
    // Now add the parent modules feeding us
    for(auto & itrParentModule : _parentModules){
        _currentString += itrParentModule->getOutfeed();
    }
}

//-----------------------------------------------------------------------------
// Implements IAudioModule::executeModule
//-----------------------------------------------------------------------------
void NoopAudioModule::executeModule(){
    // Delegate call to a procted method
    _outfeedString = executeModule_Internal(_currentString);
}

//-----------------------------------------------------------------------------
// Implements IAudioModule::getOutfeed
//-----------------------------------------------------------------------------
std::string NoopAudioModule::getOutfeed() const{
    return _outfeedString;
}

//-----------------------------------------------------------------------------
// Implements IAudioModule::connect
//-----------------------------------------------------------------------------
void NoopAudioModule::connect(std::shared_ptr<IAudioModule> ispAudioModule, bool iIsAfter) {
    // Procedure to connect
    // 1. Check that this module is not already connected
    // 2. If this is a children (iIsAfter is true) we are trying to connect, verify that its addition does not incur in a cyclic reference
    if(iIsAfter) {
        auto childExists = std::find(_childrenModules.begin(), _childrenModules.end(), ispAudioModule);

        if(_childrenModules.end() == childExists && !AudioModuleUtils::isCyclicReference(this, ispAudioModule.get())){
            _childrenModules.push_back(ispAudioModule);
        }
    }
    else {
        // Add parent module
        auto parentExists = std::find(_parentModules.begin(), _parentModules.end(), ispAudioModule);
        if(_parentModules.end() == parentExists)
            _parentModules.push_back(ispAudioModule);
    }
}

//-----------------------------------------------------------------------------
// Implements IAudioModule::GetType
//-----------------------------------------------------------------------------
IAudioModule::AudioModuleType NoopAudioModule::GetType() const{
    return IAudioModule::AudioModuleType::noop;
}

//-----------------------------------------------------------------------------
// Implements IAudioModule::getName
//-----------------------------------------------------------------------------
std::string NoopAudioModule::getName() const{
    return _name;
}

//-----------------------------------------------------------------------------
// Implements IAudioModule::accept
//-----------------------------------------------------------------------------
void NoopAudioModule::accept(IAudioModuleVisitor& iVisitor) {
    iVisitor.visit(*this);
    for(auto & itrChildModule : _childrenModules){
        itrChildModule->accept(iVisitor);
    }
}

//-----------------------------------------------------------------------------
// Implements IAudioModule::reset
//-----------------------------------------------------------------------------
void NoopAudioModule::reset() {
    // Nothing to do
}

//-----------------------------------------------------------------------------
// Implements IAudioModule::isEmpty
//-----------------------------------------------------------------------------
bool NoopAudioModule::isEmpty() const{
    return (_currentString.empty() && _infeedList.empty());
}

//-----------------------------------------------------------------------------
// NoopAudioModule : executeModule_Internal
//-----------------------------------------------------------------------------
std::string NoopAudioModule::executeModule_Internal(std::string iCurrentString) {
    // This module does not do anything, so output the same string
    return iCurrentString;
}

