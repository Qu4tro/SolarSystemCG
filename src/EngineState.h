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

#include "Command.cpp"

class EngineState {
  public:
    EngineState();
    void addSceneCommand(Command* command);

    void printCommands();
    void applyCommands();


  private:
    std::vector<Command*> sceneCommands;
    std::vector<std::vector<int>> models;
};

#endif
