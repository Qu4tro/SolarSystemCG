#ifndef ENGINESTATE_H
#define ENGINESTATE_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <iterator>
#include <tuple>
#include <math.h>

#include "Camera.h"
#include "Command.cpp"

class EngineState {
  public:
    EngineState();
    void addSceneCommand(Command* command);

    void printCommands();
    void applyCommands();

    Camera camera;
  private:
    std::vector<Command*> sceneCommands;
    std::vector<std::vector<int>> models;

};

#endif
