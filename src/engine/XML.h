#ifndef XML_H
#define XML_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <iostream>
#include <functional>
#include <utility>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Models.h"
#include "EngineState.h"

void parse(FILE* fp, EngineState& state);
std::string get_raw(std::vector<std::string> element, std::string key);

#endif
