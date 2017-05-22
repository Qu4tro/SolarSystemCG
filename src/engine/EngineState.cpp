#include "EngineState.h"

EngineState::EngineState() {
    camera = new OrbitalCamera();
}

void EngineState::addSceneCommand(Command* command) {
    sceneCommands.push_back(command);
}
void EngineState::setSceneCommands(std::vector<Command*> commands){
    for(auto it: commands){
        addSceneCommand(it);
    }
}

void EngineState::VBOify(){
    std::vector<Command*> sceneCommandsVBO;

    for(auto it: sceneCommands){
        if (DrawModel* draw = dynamic_cast<DrawModel*>(it)) {
            sceneCommandsVBO.push_back(new DrawModelVBO(draw -> model));
        } else {
            sceneCommandsVBO.push_back(it);
        }
    }

    sceneCommands = sceneCommandsVBO;
}

void EngineState::printCommands() {
    for(auto it: sceneCommands){;
        std::cout << it -> toString();
    }
}

void EngineState::applyCommands() {
    for(auto it: sceneCommands){;
        it -> apply();
    }
}
