#include "EngineState.h"

EngineState::EngineState() {
    camera = new FPSCamera();
}


void EngineState::addSceneCommand(Command* command) {
    sceneCommands.push_back(command);
}

void EngineState::VBOify(){
    std::vector<Command*> sceneCommandsVBO;

    for(auto it: sceneCommands){
        if (DrawModel* draw = dynamic_cast<DrawModel*>(it)) {
            sceneCommandsVBO.push_back(new DrawModelVBO(draw -> model_path));
        } else {
            sceneCommandsVBO.push_back(it);
        }
    }

    sceneCommands = sceneCommandsVBO;
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
