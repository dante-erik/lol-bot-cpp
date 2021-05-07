#pragma once

#include <string>

#include "client_bot.hpp"
#include "champion_bot.hpp"
#include "champions.hpp"
#include "roles.hpp"

struct ControlData {
    std::string champion_name;
    std::string client_window_class;
    std::string client_window_description;
    std::string game_window_class;
    std::string game_window_description;
    gameplay::champion champion;
    gameplay::role role;
    client_bot* client_bot;
    champion_bot *champion_bot;
};
