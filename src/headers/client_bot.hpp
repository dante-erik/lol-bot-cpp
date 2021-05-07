#pragma once

#include "bot.hpp"

class client_bot : public bot
{
private:
protected:
    DWORD run();
public:
    client_bot();
    ~client_bot();
};