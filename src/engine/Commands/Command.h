#pragma once

#include <string>

struct Command {
    virtual void apply() = 0;
    virtual std::string toString() = 0;
    virtual ~Command() { }
};
