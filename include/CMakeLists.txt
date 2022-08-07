cmake_minimum_required(VERSION 3.16)
project(AbletonTask1Core)

set(audiomodules_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/AudioModules)
set(audioapplication_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/AudioApplication)

set(audiomodules_HEADERS
        ${audiomodules_SOURCE_DIR}/IAudioModule.h
        ${audiomodules_SOURCE_DIR}/IAudioModuleVisitor.h
        ${audiomodules_SOURCE_DIR}/AudioModuleUtils.h
        PARENT_SCOPE)

set(audioapplication_HEADERS
        ${audioapplication_SOURCE_DIR}/AudioApplication.h
        PARENT_SCOPE)