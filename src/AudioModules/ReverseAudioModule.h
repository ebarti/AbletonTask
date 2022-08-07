//
// ReverseAudioModule
//

#ifndef ABLETONTASK1_REVERSEAUDIOMODULE_H
#define ABLETONTASK1_REVERSEAUDIOMODULE_H

#include "NoopAudioModule.h"

class ReverseAudioModule: public NoopAudioModule {
public:
    // Constructor & destructor
    explicit ReverseAudioModule(std::string name);
    virtual ~ReverseAudioModule();

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


#endif //ABLETONTASK1_REVERSEAUDIOMODULE_H
