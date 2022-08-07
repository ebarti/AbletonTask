cmake_minimum_required(VERSION 3.16)
project(AbletonTask1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)

add_executable(AbletonTask1 main.cpp)
target_link_libraries(AbletonTask1 AudioModules AudioApplication)

