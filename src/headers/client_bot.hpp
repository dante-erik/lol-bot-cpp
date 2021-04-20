#pragma once

#include "bot.hpp"

class client_bot : private bot
{
private:
protected:
public:
    client_bot();
    ~client_bot();
    HANDLE start();
};