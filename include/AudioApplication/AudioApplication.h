//
// Created by Eloi on 9/22/20.
//

#ifndef ABLETONTASK1_AUDIOAPPLICATION_H
#define ABLETONTASK1_AUDIOAPPLICATION_H
#include <map>
#include <iostream>
#include <vector>
#include "../AudioModules/IAudioModule.h"

class AudioApplication {
public:
    // Constructor & destructor
    AudioApplication();
    virtual ~AudioApplication();

    //-----------------------------------------------------------------------------
    // IAudioApplication methods
    //-----------------------------------------------------------------------------
    int run(int argc, char *argv[], std::ostream& outputstream = std::cout);
    int run(std::istream & istream, std::ostream& outputstream);
protected:
    void parseCmd(std::vector<std::string> &ioCmdList, int argc, char *argv[]);
    void parseCmd(std::vector<std::string> &ioCmdList, std::istream & inputsream);
    void processCommand(const std::string& iCommandLine, std::ostream& outputstream);
    void createModule(const std::string& iModuleName, const std::string& iModuleType);
    void connectModule(const std::string& iParentModuleName, const std::string& iChildModuleName);
    void stepModules(std::shared_ptr<IAudioModule>& spFirstModule, std::shared_ptr<IAudioModule>& spLastModule, int iMaxWords, std::string & ioOutputString);
    void resetModules();
private:
    // Helper functions
    IAudioModule::AudioModuleType stringToType(const std::string& iModuleType) const;
    bool areAllModulesEmpty() const;

    //-----------------------------------------------------------------------------
    // Data members
    //-----------------------------------------------------------------------------
    typedef std::map<std::string, std::shared_ptr<IAudioModule>> audioModuleMap;
    const std::string _delayTypeStr;
    const std::string _echoTypeStr;
    const std::string _reverseTypeStr;
    const std::string _noopTypeStr;
    const std::string _moduleCmdStr;
    const std::string _connectCmdStr;
    const std::string _processCmdStr;
    std::string _firstNodeId;
    std::string _lastNodeId;
    audioModuleMap _modules;
    bool _hasProccessed;
};
#endif //ABLETONTASK1_AUDIOAPPLICATION_H
