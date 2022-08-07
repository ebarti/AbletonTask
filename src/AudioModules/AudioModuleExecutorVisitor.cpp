//
// Created by Eloi on 9/21/20.
//

#include "AudioModuleExecutorVisitor.h"

//-----------------------------------------------------------------------------
// AudioModuleExecutorVisitor : constructor
//-----------------------------------------------------------------------------
AudioModuleExecutorVisitor::AudioModuleExecutorVisitor()
:AudioModuleBaseVisitor(){
    // Nothing to do
}

//-----------------------------------------------------------------------------
// AudioModuleExecutorVisitor : destructor
//-----------------------------------------------------------------------------
AudioModuleExecutorVisitor::~AudioModuleExecutorVisitor() = default;

//-----------------------------------------------------------------------------
// Implements AudioModuleBaseVisitor::visit_impl
//-----------------------------------------------------------------------------
void AudioModuleExecutorVisitor::visit_impl(IAudioModule &ipAudioModule) {
    ipAudioModule.executeModule();
}
