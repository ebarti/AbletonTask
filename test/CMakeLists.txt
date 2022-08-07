cmake_minimum_required(VERSION 3.16)
project(AbletonTask1_Tests)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TEST_DATA_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR})
configure_file(Config.h.in Config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(CATCH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/third_party/catch/include)
add_library(Catch::Catch IMPORTED INTERFACE)

set_property(TARGET Catch::Catch APPEND PROPERTY
        INTERFACE_INCLUDE_DIRECTORIES
        ${CMAKE_SOURCE_DIR}/third_party/catch/include
        )
set(AbletonTask1_Tests_SOURCES CatchMain.cpp tst_AudioModules.cpp tst_AudioApplication.cpp)

add_executable(AbletonTask1_Tests ${audiomodules_HEADERS} ${audioapplication_HEADERS} ${AbletonTask1_Tests_SOURCES})
target_link_libraries(AbletonTask1_Tests Catch::Catch AudioModules AudioApplication)

#Force cmake reload
add_custom_target(RerunCmake ${CMAKE_COMMAND} -DTEST_INPUT_ROOT_DIR=${CMAKE_CURRENT_SOURCE_DIR} -DTEST_OUTPUT_ROOT_DIR=${CMAKE_CURRENT_BINARY_DIR} -P ${CMAKE_CURRENT_SOURCE_DIR}/ResetTestData.cmake)
add_dependencies(AbletonTask1_Tests RerunCmake)
