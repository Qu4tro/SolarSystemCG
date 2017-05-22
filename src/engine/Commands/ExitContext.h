#pragma once

#include "Command.h"

struct ExitContext : Command {
    void apply();
    std::string toString();
};
