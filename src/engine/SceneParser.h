#pragma once

#include <vector>
#include <assert.h>
#include <iostream>
#include <string>

#include "tinyxml2.h"

/* #include "Model_obj.h" */
/* #include "Model_stl.h" */
#include "Model_3D.h"

#include "Commands/Command.h"
#include "Commands/EnterContext.h"
#include "Commands/ExitContext.h"
#include "Commands/Color.h"
#include "Commands/Scale.h"
#include "Commands/Rotate.h"
#include "Commands/RotateT.h"
#include "Commands/Translate.h"
#include "Commands/TranslateT.h"
#include "Commands/DrawModel.h"
#include "Commands/DrawModelVBO.h"


std::vector<Command*> parse_scene(char* filename);
