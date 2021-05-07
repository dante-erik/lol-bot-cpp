#include <iostream>
#include "../headers/client_bot.hpp"

#define seconds *1000

client_bot::client_bot() : bot{} { }
client_bot::~client_bot() = default;

DWORD client_bot::run() {
    std::cout << "Client Bot Running" << std::endl;
    Sleep(5 seconds);
    std::cout << "Client Bot Done" << std::endl;
    return 0;
}
