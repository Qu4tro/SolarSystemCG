#include "EngineState.h"

EngineState::EngineState() {
    ;
}


void EngineState::addSceneCommand(Command* command) {
    sceneCommands.push_back(command);

}

void EngineState::printCommands() {
    for(auto it: sceneCommands){;
        std::cout << it -> toString();
        std::cout << std::endl;
    }
}

void EngineState::applyCommands() {
    for(auto it: sceneCommands){;
        it -> apply();
    }
}
