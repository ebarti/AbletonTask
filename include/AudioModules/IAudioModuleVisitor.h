//
// Created by Eloi on 9/21/20.
//

#ifndef ABLETONTASK1_IAUDIOMODULEVISITOR_H
#define ABLETONTASK1_IAUDIOMODULEVISITOR_H
class IAudioModule;
class IAudioModuleVisitor {
public:
    enum type {
        infeed,
        executor
    };
    virtual ~IAudioModuleVisitor() = 0;
    virtual void visit(IAudioModule& ipAudioModule) = 0;
};

#endif //ABLETONTASK1_IAUDIOMODULEVISITOR_H
