#include <iostream>

#include "../../headers/champions/ashe_bot.hpp"

#define seconds *1000

ashe_bot::ashe_bot() : champion_bot{"Ashe"} {}
ashe_bot::~ashe_bot() = default;

DWORD ashe_bot::run() {
    std::cout << "Ashe Bot Running" << std::endl;
    Sleep(5 seconds);
    std::cout << "Ashe Bot Done" << std::endl;
    return 0;
}