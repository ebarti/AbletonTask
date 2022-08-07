//
// Created by Eloi on 9/22/20.
//

#include "AudioModuleBaseVisitor.h"

//-----------------------------------------------------------------------------
// AudioModuleBaseVisitor : constructor
//-----------------------------------------------------------------------------
AudioModuleBaseVisitor::AudioModuleBaseVisitor():
_visitedNodes() {
    // Nothing to do
}

//-----------------------------------------------------------------------------
// AudioModuleBaseVisitor : destructor
//-----------------------------------------------------------------------------
AudioModuleBaseVisitor::~AudioModuleBaseVisitor() = default;

//-----------------------------------------------------------------------------
// Implements IAudioModuleVisitor::visit
//-----------------------------------------------------------------------------
void AudioModuleBaseVisitor::visit(IAudioModule &ipAudioModule) {
    if(!hasBeenVisited(&ipAudioModule))
        return visit_impl(ipAudioModule);
}

//-----------------------------------------------------------------------------
// AudioModuleBaseVisitor : hasBeenVisited
//-----------------------------------------------------------------------------
bool AudioModuleBaseVisitor::hasBeenVisited(IAudioModule const* ipAudioModule) {
    if(_visitedNodes.find(ipAudioModule) != _visitedNodes.end())
        return true;
    _visitedNodes.insert(ipAudioModule);
    return false;
}
