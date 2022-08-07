//
// Created by Eloi on 9/22/20.
//

#include "../../include/AudioModules/AudioModuleUtils.h"
#include "EchoAudioModule.h"
#include "ReverseAudioModule.h"
#include "DelayAudioModule.h"
#include "AudioModuleExecutorVisitor.h"
#include "AudioModuleInfeedProcessorVisitor.h"
#include "AudioModuleCyclicReferenceFinder.h"


std::shared_ptr<IAudioModule> AudioModuleUtils::CreateAudioModule(const std::string &iModuleName, IAudioModule::AudioModuleType iType) {
    switch (iType) {
        case IAudioModule::AudioModuleType::delay:
            return std::make_shared<DelayAudioModule>(iModuleName);
        case IAudioModule::AudioModuleType::echo:
            return std::make_shared<EchoAudioModule>(iModuleName);
        case IAudioModule::AudioModuleType::reverse:
            return std::make_shared<ReverseAudioModule>(iModuleName);
        default:
            return std::make_shared<NoopAudioModule>(iModuleName);
    }
}

std::unique_ptr<IAudioModuleVisitor> AudioModuleUtils::CreateAudioModuleVisitor(IAudioModuleVisitor::type iType) {
    if (IAudioModuleVisitor::type::infeed == iType)
        return std::make_unique<AudioModuleInfeedProcessorVisitor>();
    return std::make_unique<AudioModuleExecutorVisitor>();
}

bool AudioModuleUtils::isCyclicReference(IAudioModule *ipAudioModule, IAudioModule *ipChildModule) {
    bool isCyclic= false;
    auto * pCyclicRefFinder = new AudioModuleCyclicReferenceFinder();
    if(pCyclicRefFinder){
        pCyclicRefFinder->setStartAudioModule(ipAudioModule);
        ipChildModule->accept(*pCyclicRefFinder);
        isCyclic = pCyclicRefFinder->isCyclicReference();
        delete pCyclicRefFinder;
        pCyclicRefFinder = nullptr;
    }
    return isCyclic;
}
