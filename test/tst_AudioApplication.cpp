//
// Created by Eloi on 9/24/20.
//

#include "../include/AudioApplication/AudioApplication.h"
#include "../third_party/catch/include/catch.hpp"
#include <Config.h>
#include <fstream>

void GetTestDataPath(std::string & oInputDataPath, std::string & oOutputPath, std::string & oOutputRefPath, const std::string &iTestDataFileBaseName) {
    std::string basePath = TEST_DATA_SOURCE_DIR;
    std::string basePathInput = basePath + "/resources/inputData/";
    std::string basePathOutput = basePath + "/output/";
    std::string basePathRef = basePath + "/resources/outputRef/";

    oInputDataPath = basePathInput + iTestDataFileBaseName + "_tstData.txt";
    oOutputPath = basePathOutput + iTestDataFileBaseName + "_tstData_out.txt";
    oOutputRefPath = basePathRef + iTestDataFileBaseName + "_tstData_outputref.txt";
}

int RunFileApplication(const std::string & iTestName, const std::string & iInputDataPath, std::string & oOutputPath){
    std::ifstream dataStream(iInputDataPath);
    std::ofstream testOutput(oOutputPath);
    SECTION("Test " + iTestName + ": Check input data file OK")
    {
        REQUIRE(dataStream);
    }
    SECTION("Test " + iTestName + ": Check output file to stream to was created OK")
    {
        REQUIRE(testOutput);
    }

    auto spAudioApplication = std::make_unique<AudioApplication>();
    SECTION("Test " + iTestName + ": Check AudioApplication was created OK"){
        REQUIRE(nullptr != spAudioApplication);
    }
    SECTION("Test " + iTestName + ": Check AudioApplication was ran OK"){
        return spAudioApplication->run(dataStream, testOutput);
    }
    return 0;
}

void CompareOutput(const std::string & iTestName, const std::string &iOutputFilePath, const std::string &oOutputRefPath) {
    std::ifstream f1(iOutputFilePath, std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(oOutputRefPath, std::ifstream::binary|std::ifstream::ate);

    SECTION("Test " + iTestName + ": Check input and ouputREf files OK"){
        REQUIRE(true == (!f1.fail() && !f2.fail()));
    }

    SECTION("Test " + iTestName + ": Compare input and ouputRef sizes"){
        REQUIRE(f1.tellg() == f2.tellg());
    }

    //seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    SECTION("Test " + iTestName + ": Compare input and outputRef contents") {
        REQUIRE(std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                           std::istreambuf_iterator<char>(),
                           std::istreambuf_iterator<char>(f2.rdbuf())));
    }
}

void RunApplicationFileTestCase(std::string iTestName){
    std::string inputPath, outputPath, outputRefPath;
    GetTestDataPath(inputPath, outputPath, outputRefPath, iTestName);
    SECTION("Run Application"){
        RunFileApplication(iTestName, inputPath, outputPath);
    }
    SECTION("Compare Application Output with Reference"){
        CompareOutput(iTestName, outputPath, outputRefPath);
    }
}

TEST_CASE("Audio Application Stdin redirected test cases - helloworld", "[AudioApplication][TestFromFile]")
{
    RunApplicationFileTestCase("helloworld");
}
TEST_CASE("Audio Application Stdin redirected test cases - echoreverseloop", "[AudioApplication][TestFromFile]")
{
    RunApplicationFileTestCase("echoreverseloop");
}
TEST_CASE("Audio Application Stdin redirected test cases - nooutput1", "[AudioApplication][TestFromFile]")
{
    RunApplicationFileTestCase("nooutput1");
}
TEST_CASE("Audio Application Stdin redirected test cases - live", "[AudioApplication][TestFromFile]")
{
    RunApplicationFileTestCase("live");
}
TEST_CASE("Audio Application Stdin redirected test cases - push", "[AudioApplication][TestFromFile]")
{
    RunApplicationFileTestCase("push");
}