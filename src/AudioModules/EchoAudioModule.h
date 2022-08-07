//
// EchoAudioModule
//

#ifndef ABLETONTASK1_ECHOAUDIOMODULE_H
#define ABLETONTASK1_ECHOAUDIOMODULE_H

#include "NoopAudioModule.h"

class EchoAudioModule: public NoopAudioModule {
public:
    // Constructor & destructor
    explicit EchoAudioModule(std::string name);
    virtual ~EchoAudioModule();

    //-----------------------------------------------------------------------------
    // IAudioModule methods
    //-----------------------------------------------------------------------------
    AudioModuleType GetType() const final;

protected:
    //-----------------------------------------------------------------------------
    // NoopAudioModule overriden methods
    //-----------------------------------------------------------------------------
    std::string executeModule_Internal(std::string iCurrentString) final;
};


#endif //ABLETONTASK1_ECHOAUDIOMODULE_H
