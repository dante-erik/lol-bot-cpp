#pragma once

#include "bot.hpp"

class champion_bot : protected bot
{
private:
protected:
public:
    champion_bot();
    virtual ~champion_bot();
    virtual HANDLE start();
};