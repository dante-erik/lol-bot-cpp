#pragma once

#include "../../cpp-robot/lib/Robot.hpp"

class bot : Robot
{
private:
protected:
public:
    bot() = default;
    virtual ~bot() = default;
    virtual HANDLE start() = 0;
};