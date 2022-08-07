//
// Created by Eloi on 9/22/20.
//

#include "../include/AudioModules/IAudioModuleVisitor.h"
#include "../include/AudioModules/IAudioModule.h"
#include "../include/AudioModules/AudioModuleUtils.h"
#include "../third_party/catch/include/catch.hpp"
#include <sstream>

const std::string tstName("tstAudioModuleName");
const std::string tstInputStr("this is a test");
const int tstInputStringWordCount = 4;

// Helper functions
// Utility to feed tokens
void feedTokens(std::shared_ptr<IAudioModule> & spAudioModule){
    std::istringstream tstInputStrStream(tstInputStr);
    std::string token;
    while(tstInputStrStream >> token){
        spAudioModule->setInfeed(token);
    }
}

// Utility to execute a single module
void executeSingleModule(std::shared_ptr<IAudioModule> & spAudioModule, std::string & ioOutputString){
    // The word count is equal to the number of spaces + 1
    //Get num of spaces
    int outWordCount = std::count_if(ioOutputString.begin(), ioOutputString.end(),[](unsigned char c) { return std::isspace(c); });
    if (outWordCount) // if there are spaces that means there are words, add one (words = spaces + 1)
        outWordCount++;

    // if we are done then return
    if(spAudioModule->isEmpty() || outWordCount > tstInputStringWordCount*4)
        return;

    spAudioModule->getInfeed();
    spAudioModule->executeModule();
    std::string moduleoutput = spAudioModule->getOutfeed();
    if(!ioOutputString.empty() && !moduleoutput.empty())
        ioOutputString+=" ";
    ioOutputString += moduleoutput;
    return executeSingleModule(spAudioModule, ioOutputString);
}


// Delay Module tests
TEST_CASE("DelayAudioModule", "[AudioModules][DelayAudioModule]") {
    std::string objName("spDelayAudioModule");
    IAudioModule::AudioModuleType objType = IAudioModule::AudioModuleType::delay;
    std::shared_ptr<IAudioModule> spAudioModule = AudioModuleUtils::CreateAudioModule(tstName, objType);
    SECTION("Factory creation"){
        REQUIRE(nullptr != spAudioModule);
    }
    SECTION("Test Name") {
        REQUIRE(spAudioModule->getName() == tstName);
    }
    SECTION("Test Type") {
        REQUIRE(spAudioModule->GetType() == objType);
    }
    SECTION("Test empty")
    {
        REQUIRE(spAudioModule->isEmpty() == true);
    }
    SECTION("Test individual module behavior")
    {
        std::string moduleOutput;
        std::string expectedOutput = "hello " + tstInputStr; //Delay
        feedTokens(spAudioModule);
        executeSingleModule(spAudioModule, moduleOutput);
        REQUIRE(moduleOutput == expectedOutput);
    }
}

// Delay Module tests
TEST_CASE("EchoAudioModule", "[AudioModules][EchoAudioModule]") {
    std::string objName("spEchoAudioModule");
    IAudioModule::AudioModuleType objType = IAudioModule::AudioModuleType::echo;
    std::shared_ptr<IAudioModule> spAudioModule = AudioModuleUtils::CreateAudioModule(tstName, objType);
    SECTION("Factory creation"){
        REQUIRE(nullptr != spAudioModule);
    }
    SECTION("Test Name") {
        REQUIRE(spAudioModule->getName() == tstName);
    }
    SECTION("Test Type") {
        REQUIRE(spAudioModule->GetType() == objType);
    }
    SECTION("Test empty")
    {
        REQUIRE(spAudioModule->isEmpty() == true);
    }
    SECTION("Test individual module behavior")
    {
        std::string moduleOutput("");
        std::string expectedOutput = "thisthis isis aa testtest"; //Echo
        feedTokens(spAudioModule);
        executeSingleModule(spAudioModule, moduleOutput);
        REQUIRE(moduleOutput == expectedOutput);
    }
}

TEST_CASE("ReverseAudioModule", "[AudioModules][ReverseAudioModule]") {
    std::string objName("spReverseAudioModule");
    IAudioModule::AudioModuleType objType = IAudioModule::AudioModuleType::reverse;
    std::shared_ptr<IAudioModule> spAudioModule = AudioModuleUtils::CreateAudioModule(tstName, objType);
    SECTION("Factory creation"){
        REQUIRE(nullptr != spAudioModule);
    }
    SECTION("Test Name") {
        REQUIRE(spAudioModule->getName() == tstName);
    }
    SECTION("Test Type") {
        REQUIRE(spAudioModule->GetType() == objType);
    }
    SECTION("Test empty")
    {
        REQUIRE(spAudioModule->isEmpty() == true);
    }
    SECTION("Test individual module behavior")
    {
        std::string moduleOutput("");
        std::string expectedOutput = "siht si a tset"; //Reverse
        feedTokens(spAudioModule);
        executeSingleModule(spAudioModule, moduleOutput);
        REQUIRE(moduleOutput == expectedOutput);
    }
}

TEST_CASE("NoopAudioModule", "[AudioModules][NoopAudioModule]") {
    std::string objName("spNoopAudioModule");
    IAudioModule::AudioModuleType objType = IAudioModule::AudioModuleType::noop;
    std::shared_ptr<IAudioModule> spAudioModule = AudioModuleUtils::CreateAudioModule(tstName, objType);
    SECTION("Factory creation"){
        REQUIRE(nullptr != spAudioModule);
    }
    SECTION("Test Name") {
        REQUIRE(spAudioModule->getName() == tstName);
    }
    SECTION("Test Type") {
        REQUIRE(spAudioModule->GetType() == objType);
    }
    SECTION("Test empty")
    {
        REQUIRE(spAudioModule->isEmpty() == true);
    }
    SECTION("Test individual module behavior")
    {
        std::string moduleOutput("");
        std::string expectedOutput = tstInputStr; //Noop
        feedTokens(spAudioModule);
        executeSingleModule(spAudioModule, moduleOutput);
        REQUIRE(moduleOutput == expectedOutput);
    }
}
