//
// Created by Eloi on 9/22/20.
//

#ifndef ABLETONTASK1_AUDIOMODULEUTILS_H
#define ABLETONTASK1_AUDIOMODULEUTILS_H

#include <memory>
#include "IAudioModule.h"
#include "IAudioModuleVisitor.h"
class AudioModuleInfeedProcessorVisitor;
class AudioModuleExecutorVisitor;
class AudioModuleCyclicReferenceFinder;
class AudioModuleUtils {
public:
    static bool isCyclicReference(IAudioModule * ipAudioModule, IAudioModule * ipChildModule);

    static std::shared_ptr<IAudioModule> CreateAudioModule(const std::string &iModuleName, IAudioModule::AudioModuleType iType);

    // NOTE: Caller must release pointer
    static std::unique_ptr<IAudioModuleVisitor> CreateAudioModuleVisitor(IAudioModuleVisitor::type iType);
};


#endif //ABLETONTASK1_AUDIOMODULEUTILS_H
