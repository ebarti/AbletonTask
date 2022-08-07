//
// Created by Eloi on 9/22/20.
//

#ifndef ABLETONTASK1_AUDIOMODULEBASEVISITOR_H
#define ABLETONTASK1_AUDIOMODULEBASEVISITOR_H

#include <set>
#include "../../include/AudioModules/IAudioModuleVisitor.h"
#include "../../include/AudioModules/IAudioModule.h"

class AudioModuleBaseVisitor: public IAudioModuleVisitor {
public:
    // Constructor & destructor
    AudioModuleBaseVisitor();
    virtual ~AudioModuleBaseVisitor();

    //-----------------------------------------------------------------------------
    // IAudioModuleVisitor methods
    //-----------------------------------------------------------------------------
    void visit(IAudioModule &ipAudioModule) override;

protected:
    //-----------------------------------------------------------------------------
    // AudioModuleBaseVisitor methods
    //-----------------------------------------------------------------------------
    virtual void visit_impl(IAudioModule &ipAudioModule) = 0;

private:
    bool hasBeenVisited(IAudioModule const* ipAudioModule);

    //-----------------------------------------------------------------------------
    // Data members
    //-----------------------------------------------------------------------------
    std::set<const IAudioModule*> _visitedNodes;
};


#endif //ABLETONTASK1_AUDIOMODULEBASEVISITOR_H
