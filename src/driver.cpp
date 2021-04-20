#include <iostream>

#include "headers/client_bot.hpp"
#include "headers/champion_bot.hpp"
#include "headers/champions/ashe_bot.hpp"

int main(int argc, char *argv[]) {
    std::cout << "Starting" << std::endl;
    // client_bot client;
    champion_bot* champion = new ashe_bot();
    champion->start();
    WaitForSingleObject(champion->get_hThread(), INFINITE);
    return 0;
}