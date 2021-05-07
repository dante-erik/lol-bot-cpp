#pragma once

#include <string>

#include "bot.hpp"

#define pure = 0

class champion_bot : public bot
{
private:
    std::string _champion_name;
protected:
    virtual DWORD run() pure;
public:
    champion_bot(std::string const& champion_name);
    virtual ~champion_bot();
    void chat(const char* msg);
    std::string const& champion_name() const; 
};

#undef pure