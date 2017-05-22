#pragma once

#include <vector>

#include "Camera.h"
#include "Commands/Command.h"

#include "OrbitalCamera.h"
#include "FPSCamera.h"
#include "Commands/DrawModelVBO.h"
#include "Commands/DrawModel.h"

class EngineState {
  public:
    EngineState();
    void addSceneCommand(Command* command);
    void setSceneCommands(std::vector<Command*> command);
    void VBOify();

    void printCommands();
    void applyCommands();

    Camera* camera;
  private:
    std::vector<Command*> sceneCommands;
};
