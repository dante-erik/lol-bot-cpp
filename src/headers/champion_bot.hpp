#pragma once

#include "bot.hpp"

#define pure = 0

class champion_bot : public bot
{
private:
protected:
    virtual DWORD run() pure;
public:
    champion_bot();
    virtual ~champion_bot();
};

#undef pure