//
// Created by Eloi on 9/21/20.
//

#include "AudioModuleInfeedProcessorVisitor.h"

//-----------------------------------------------------------------------------
// AudioModuleInfeedProcessorVisitor : constructor
//-----------------------------------------------------------------------------
AudioModuleInfeedProcessorVisitor::AudioModuleInfeedProcessorVisitor()
:AudioModuleBaseVisitor(){
    // Nothing to do
}

//-----------------------------------------------------------------------------
// AudioModuleInfeedProcessorVisitor : destructor
//-----------------------------------------------------------------------------
AudioModuleInfeedProcessorVisitor::~AudioModuleInfeedProcessorVisitor() = default;

//-----------------------------------------------------------------------------
// Implements AudioModuleBaseVisitor::visit_impl
//-----------------------------------------------------------------------------
void AudioModuleInfeedProcessorVisitor::visit_impl(IAudioModule &ipAudioModule) {
    ipAudioModule.getInfeed();
}
