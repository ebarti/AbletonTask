//
// DelayAudioModule
//

#ifndef ABLETONTASK1_DELAYAUDIOMODULE_H
#define ABLETONTASK1_DELAYAUDIOMODULE_H

#include "NoopAudioModule.h"

class DelayAudioModule: public NoopAudioModule {
public:
    // Constructor & destructor
    explicit DelayAudioModule(std::string name);
    virtual ~DelayAudioModule();

    //-----------------------------------------------------------------------------
    // IAudioModule methods
    //-----------------------------------------------------------------------------
    AudioModuleType GetType() const final;
    bool isEmpty() const override;
    void reset() override;

protected:
    //-----------------------------------------------------------------------------
    // NoopAudioModule overriden methods
    //-----------------------------------------------------------------------------
    std::string executeModule_Internal(std::string iCurrentString) final;

private:
    //-----------------------------------------------------------------------------
    // Data members
    //-----------------------------------------------------------------------------
    std::string _previousString;
    bool _isInitialized;
};


#endif //ABLETONTASK1_DELAYAUDIOMODULE_H
