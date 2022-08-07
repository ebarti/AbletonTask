//
// Created by Eloi on 9/17/20.
//

#ifndef ABLETONTASK1_IAUDIOMODULE_H
#define ABLETONTASK1_IAUDIOMODULE_H

#include <string>
#include <memory>
#include <list>
class IAudioModuleVisitor;
class IAudioModule {
public:
    enum AudioModuleType {
        echo,
        noop,
        reverse,
        delay
    };

    virtual ~IAudioModule() = 0;
    virtual void setInfeed(std::string iInfeedToken) = 0;
    virtual void getInfeed() = 0;
    virtual void executeModule() = 0;
    virtual std::string getOutfeed() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void connect(std::shared_ptr<IAudioModule> ispAudioModule, bool iIsAfter) = 0;
    virtual std::string getName() const = 0;
    virtual AudioModuleType GetType() const = 0;
    virtual void accept(IAudioModuleVisitor& iVisitor) = 0;
    virtual void reset() = 0;
};


#endif //ABLETONTASK1_IAUDIOMODULE_H
