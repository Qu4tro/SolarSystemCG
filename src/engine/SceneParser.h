#ifndef SCENEPARSER_H
#define SCENEPARSER_H

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

#include "tinyxml2.h"
#include "Command.cpp"

std::vector<Command*> parse_scene(char* filename);

#endif
