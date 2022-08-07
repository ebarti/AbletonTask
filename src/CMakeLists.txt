cmake_minimum_required(VERSION 3.16)
project(AbletonTask1_Libs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(audiomodules_private_HEADERS
        AudioModules/AudioModuleExecutorVisitor.h
        AudioModules/AudioModuleInfeedProcessorVisitor.h
        AudioModules/DelayAudioModule.h
        AudioModules/EchoAudioModule.h
        AudioModules/NoopAudioModule.h
        AudioModules/ReverseAudioModule.h
        AudioModules/AudioModuleBaseVisitor.h
        AudioModules/AudioModuleCyclicReferenceFinder.h)

set(audiomodules_SOURCES
        AudioModules/AudioModuleExecutorVisitor.cpp
        AudioModules/AudioModuleInfeedProcessorVisitor.cpp
        AudioModules/DelayAudioModule.cpp
        AudioModules/EchoAudioModule.cpp
        AudioModules/NoopAudioModule.cpp
        AudioModules/ReverseAudioModule.cpp
        AudioModules/AudioModuleBaseVisitor.cpp
        AudioModules/AudioModuleUtils.cpp
        AudioModules/AudioModuleCyclicReferenceFinder.cpp
        AudioModules/IAudioModule.cpp
        AudioModules/IAudioModuleVisitor.cpp)

set(audiomodules_build_include_dirs
        ${audiomodules_HEADERS}
        ${audiomodules_private_HEADERS})

add_library(AudioModules SHARED
        ${audiomodules_build_include_dirs}
        ${audiomodules_SOURCES})

target_include_directories(AudioModules INTERFACE
        $<BUILD_INTERFACE:${audiomodules_build_include_dirs}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/AudioModules>)

set(audioapplication_SOURCES
        AudioApplication/AudioApplication.cpp)


set(audioapplication_build_include_dirs
        ${audioapplication_HEADERS})

add_library(AudioApplication SHARED
        ${audioapplication_build_include_dirs}
        ${audioapplication_SOURCES})

target_include_directories(AudioApplication INTERFACE
        $<BUILD_INTERFACE:${audioapplication_build_include_dirs}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/AudioApplication>)

target_link_libraries(AudioApplication AudioModules)
