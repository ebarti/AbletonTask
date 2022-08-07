//
// Created by Eloi on 9/24/20.
//

#include "include/AudioApplication/AudioApplication.h"

// Application EntryPoint
int main(int argc, char *argv[]) {
    // Init application
    auto spApplication = std::make_unique<AudioApplication>();
    return spApplication->run(argc, argv);
}