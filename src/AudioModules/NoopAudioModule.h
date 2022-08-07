//
// NoopAudioModule
//

#ifndef ABLETONTASK1_NOOPAUDIOMODULE_H
#define ABLETONTASK1_NOOPAUDIOMODULE_H

#include "../../include/AudioModules/IAudioModule.h"
#include <queue>
class IAudioModuleVisitor;

class NoopAudioModule: public IAudioModule {
public:
    // Constructor & destructor
    explicit NoopAudioModule(std::string name);
    virtual ~NoopAudioModule();

    //-----------------------------------------------------------------------------
    // IAudioModule methods
    //-----------------------------------------------------------------------------
    void setInfeed(std::string iInfeedToken) final;
    void getInfeed() final;
    void executeModule() final;
    std::string getOutfeed() const final;
    bool isEmpty() const override; //This method is not final, as the delay module needs to override it
    void connect(std::shared_ptr<IAudioModule> ispAudioModule, bool iIsAfter) final;
    std::string getName() const final;
    AudioModuleType GetType() const override;
    void accept(IAudioModuleVisitor& iVisitor) final;

    void reset() override;

protected:
    //-----------------------------------------------------------------------------
    // NoopAudioModule methods - override per derived class
    //-----------------------------------------------------------------------------
    virtual std::string executeModule_Internal(std::string iCurrentString);

private:
    //-----------------------------------------------------------------------------
    // Data members
    //-----------------------------------------------------------------------------
    std::string _name;
    std::queue<std::string> _infeedList;
    std::list<std::shared_ptr<IAudioModule>>  _parentModules;
    std::list<std::shared_ptr<IAudioModule>>  _childrenModules;
    std::string _currentString;
    std::string _outfeedString;
};


#endif //ABLETONTASK1_NOOPAUDIOMODULE_H
