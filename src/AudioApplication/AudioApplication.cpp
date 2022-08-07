//
// Created by Eloi on 9/22/20.
//

#include <cstdio>
#include <iostream>
#include <sstream>
#include "../../include/AudioApplication/AudioApplication.h"
#include "../../include/AudioModules/IAudioModuleVisitor.h"
#include "../../include/AudioModules/AudioModuleUtils.h"
#include <fstream>
//-----------------------------------------------------------------------------
// AudioApplication : constructor
//-----------------------------------------------------------------------------
AudioApplication::AudioApplication():
_modules()
,_hasProccessed(false)
,_firstNodeId("")
,_lastNodeId("")
,_delayTypeStr("delay")
,_echoTypeStr("echo")
,_reverseTypeStr("reverse")
,_noopTypeStr("noop")
,_moduleCmdStr("module")
,_connectCmdStr("connect")
,_processCmdStr("process"){
    // Nothing else to do
}

//-----------------------------------------------------------------------------
// AudioApplication : destructor
//-----------------------------------------------------------------------------
AudioApplication::~AudioApplication() = default;

//-----------------------------------------------------------------------------
// AudioApplication : run
//-----------------------------------------------------------------------------
int AudioApplication::run(int argc, char *argv[], std::ostream& outputstream) {
    std::vector<std::string> cmdList;
    if (1 == argc ){  // Run from redirect
        parseCmd(cmdList, std::cin);
    }
    else if (2 == argc){ // Filepath as input
        std::ifstream fileStream(argv[1], std::ios_base::in);
        parseCmd(cmdList, fileStream);

    } else { // All instructions as command line arguments
        parseCmd(cmdList, argc, argv);
    }
    for(const auto& cmd : cmdList){
        processCommand(cmd, outputstream);
    }
    return 0;
}

//-----------------------------------------------------------------------------
// AudioApplication : run
//-----------------------------------------------------------------------------
int AudioApplication::run(std::istream &istream, std::ostream &outputstream) {
    // Equals to running from redirect
    std::vector<std::string> cmdList;
    parseCmd(cmdList, istream);
    for(const auto& cmd : cmdList){
        processCommand(cmd, outputstream);
    }
    return 0;
}

//-----------------------------------------------------------------------------
// AudioApplication : parseCmd
//-----------------------------------------------------------------------------
void AudioApplication::parseCmd(std::vector<std::string> &ioCmdList, int argc, char *argv[]) {
    std::string curCmd;
    for(int ii = 1; ii<argc; ii++){
       std::string curArg(argv[ii]);
       if(_moduleCmdStr == curArg || _connectCmdStr == curArg || _processCmdStr == curArg){
           // store previous command, if any
           if(!curCmd.empty())
               ioCmdList.push_back(curCmd);
           // set new current command
           curCmd = curArg;
       } else {
           // append arguments to current command
           curCmd = curCmd + " " + curArg;
       }
    }
    // add last parsed command
    ioCmdList.push_back(curCmd);
}

//-----------------------------------------------------------------------------
// AudioApplication : parseCmd
//-----------------------------------------------------------------------------
void AudioApplication::parseCmd(std::vector<std::string> &ioCmdList, std::istream &inputsream) {
    std::string cmd;
    while(std::getline(inputsream, cmd)){
        ioCmdList.push_back(cmd);
    }
}

//-----------------------------------------------------------------------------
// AudioApplication : processCommand
//-----------------------------------------------------------------------------
void AudioApplication::processCommand(const std::string& iCommandLine, std::ostream& outputstream) {
    std::string currentCommand;
    std::istringstream currentLine(iCommandLine);
    currentLine >> currentCommand;

    if(_moduleCmdStr == currentCommand)
    {
        // Command syntax: module [module name] [module type]
        std::string moduleName, moduleType;
        currentLine>>moduleName;
        currentLine>>moduleType;
        return createModule(moduleName, moduleType);
    }
    else if (_connectCmdStr == currentCommand)
    {
        // Command syntax: connect [parent module name] [child module name]
        std::string firstModuleName, secondModuleName;
        currentLine>>firstModuleName;
        currentLine>>secondModuleName;
        return connectModule(firstModuleName, secondModuleName);
    }
    else if(_processCmdStr == currentCommand)
    {
        // Reset if we have previously processed
        if(_hasProccessed){
            outputstream<<std::endl;
            resetModules();
        }
        // Command syntax: process [args]
        // 1. Get first module
        // 2. Tokenize command arguments and feed tokens to the first module
        // 3. Execute process
        // 4. Get last module output and print it
        //Get module
        std::shared_ptr<IAudioModule> spFirstModule, spLastModule;
        if(!_modules.empty() && !_firstNodeId.empty() && !_lastNodeId.empty()){
            spFirstModule = _modules[_firstNodeId];
            spLastModule = _modules[_lastNodeId];
        }
        if(spFirstModule && spLastModule){
            std::string token;
            int tokenCount = 0;
            // Tokenize & feed
            while(currentLine >> token) {
                spFirstModule->setInfeed(token);
                tokenCount++;
            }
            if(tokenCount){
                std::string output("");
                stepModules(spFirstModule, spLastModule, tokenCount*16, output);
                outputstream<<output;
                _hasProccessed = true;
            }
        }
    }
}

//-----------------------------------------------------------------------------
// AudioApplication : createModule
//-----------------------------------------------------------------------------
void AudioApplication::createModule(const std::string& iModuleName, const std::string& iModuleType) {

    std::shared_ptr<IAudioModule> spNewModule = AudioModuleUtils::CreateAudioModule(iModuleName, stringToType(std::move(iModuleType)));
    _modules[iModuleName] = spNewModule;
    // store the Module IDs
    // Convention here is that the first module created is the first module in the chain
    // and the last node created is the last one in the chain
    if("" == _firstNodeId)
        _firstNodeId = iModuleName;
    _lastNodeId = iModuleName;
}

//-----------------------------------------------------------------------------
// AudioApplication : connectModule
//-----------------------------------------------------------------------------
void AudioApplication::connectModule(const std::string& iParentModuleName, const std::string& iChildModuleName) {
    std::shared_ptr<IAudioModule> spParentModule, spChildModule;
    if(_modules.find(iParentModuleName) != _modules.end() && _modules.find(iChildModuleName) != _modules.end())
    {
        spParentModule = _modules[iParentModuleName];
        spChildModule = _modules[iChildModuleName];
    }
    if(spParentModule && spChildModule)
    {
        spParentModule->connect(spChildModule, true);
        spChildModule->connect(spParentModule, false);
    }
}

//-----------------------------------------------------------------------------
// AudioApplication : stepModules
//-----------------------------------------------------------------------------
void AudioApplication::stepModules(std::shared_ptr<IAudioModule>& spFirstModule, std::shared_ptr<IAudioModule>& spLastModule, int iMaxWords, std::string & ioOutputString) {
    // The word count is equal to the number of spaces + 1
    //Get num of spaces
    int outWordCount = std::count_if(ioOutputString.begin(), ioOutputString.end(),[](unsigned char c) { return std::isspace(c); });
    if (outWordCount) // if there are spaces that means there are words, add one (words = spaces + 1)
        outWordCount++;

    // if we are done then return
    if(areAllModulesEmpty() || outWordCount > iMaxWords)
        return;

    // We are not done, so step forward
    // 1. Process infeeds
    std::unique_ptr<IAudioModuleVisitor> spInfeedVisitor = AudioModuleUtils::CreateAudioModuleVisitor(IAudioModuleVisitor::infeed);
    spFirstModule->accept(*spInfeedVisitor.get());
    // 2. Execute modules
    std::unique_ptr<IAudioModuleVisitor> spExecutorVisitor = AudioModuleUtils::CreateAudioModuleVisitor(IAudioModuleVisitor::executor);
    spFirstModule->accept(*spExecutorVisitor.get());
    // 3. Get outfeed from last module
    std::string lastModuleOutput = spLastModule->getOutfeed();
    if(!lastModuleOutput.empty() && !ioOutputString.empty())
        ioOutputString += " ";
    ioOutputString += lastModuleOutput;
    return stepModules(spFirstModule, spLastModule, iMaxWords, ioOutputString);
}


//-----------------------------------------------------------------------------
// AudioApplication : resetModules
//-----------------------------------------------------------------------------
void AudioApplication::resetModules() {
    for(const auto& [key, value]: _modules){
        value->reset();
    }
}

//-----------------------------------------------------------------------------
// AudioApplication : stringToType
//-----------------------------------------------------------------------------
IAudioModule::AudioModuleType AudioApplication::stringToType(const std::string& iModuleType) const {
    if (_delayTypeStr == iModuleType)
        return IAudioModule::delay;
    else if (_echoTypeStr == iModuleType)
        return IAudioModule::echo;
    else if (_reverseTypeStr == iModuleType)
        return IAudioModule::reverse;
    else if (_noopTypeStr == iModuleType)
        return IAudioModule::noop;
    //default
    return IAudioModule::noop;
}

//-----------------------------------------------------------------------------
// AudioApplication : areAllModulesEmpty
//-----------------------------------------------------------------------------
bool AudioApplication::areAllModulesEmpty() const {
    for(const auto& [key, value]: _modules){
        if(!value->isEmpty()) return false;
    }
    return true;
}

