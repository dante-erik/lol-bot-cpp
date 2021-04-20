#pragma once

#include "../champion_bot.hpp"

class ashe_bot : public champion_bot
{
private:
protected:
    DWORD run();
public:
    ashe_bot();
    ~ashe_bot();
};