#include <iostream>

// Gives the different bot types, bot, client_bot, champion_bot
#include "headers/bots.hpp"
// Gives the different champion bot implementations
#include "headers/champions.hpp"
// Gives the shell that users can use to command the driver
#include "headers/shell.hpp"
// Gives string modifiers like stolower and stopretty
#include "headers/string_modifiers.hpp"
// Gives control data struct used in shell
#include "headers/control.hpp"

#define seconds *1000

std::string HandleArgument(int &arg, char *argv[]);
bool MatchArgument(int &arg, char *argv[], std::string const &argument);
std::string &HandleArgumentWithPrefix(int &arg, char *argv[], std::string const &prefix, std::string &argument);

int main(int argc, char *argv[])
{
    const std::string default_champion_name{"Ashe"};
    const std::string default_client_window_class{"RCLIENT"};
    const std::string default_client_window_description{"League of Legends"};
    const std::string default_game_window_class{"RiotWindowClass"};
    const std::string default_game_window_description{"League of Legends (TM) Client"};
    ControlData data{
        default_champion_name,
        default_client_window_class,
        default_client_window_description,
        default_game_window_class,
        default_game_window_description,
        gameplay::champion::INVALID,
        gameplay::role::NONE,
        nullptr,
        nullptr};
    int i = 1;
    while (i < argc)
    {
        int j = i;
        HandleArgumentWithPrefix(i, argv, "-champion", data.champion_name);
        if (i != j)
            continue;
        HandleArgumentWithPrefix(i, argv, "-clientwc", data.client_window_class);
        if (i != j)
            continue;
        HandleArgumentWithPrefix(i, argv, "-clientwd", data.client_window_description);
        if (i != j)
            continue;
        HandleArgumentWithPrefix(i, argv, "-gamewc", data.game_window_class);
        if (i != j)
            continue;
        HandleArgumentWithPrefix(i, argv, "-gamewd", data.game_window_description);
        if (i != j)
            continue;
        if (MatchArgument(i, argv, "-h") || MatchArgument(i, argv, "-help") || MatchArgument(i, argv, "help") || MatchArgument(i, argv, "h"))
        {
            std::cout << "Usage " << argv[0] << ":\n"
                      << "\t-champion: Sets the champion name (default: \"" << default_champion_name << "\")\n"
                      << "\t-clientwc: Sets the client's WINDOW_CLASS (default: \"" << default_client_window_class << "\")\n"
                      << "\t-clientwd: Sets the client's Window Description (default: \"" << default_client_window_description << "\")\n"
                      << "\t-gamewc: Sets the game's WINDOW_CLASS (default: \"" << default_game_window_class << "\")\n"
                      << "\t-clientwd: Sets the game's Window Description (default: \"" << default_game_window_description << "\")"
                      << std::endl;
            std::cout << "The champion's name is case-insensitive." << std::endl;
            std::cout << "You can use the Windows tool spy.exe to get the Window information." << std::endl;
            return 0;
        }
        if (i == j)
        {
            std::cerr << "Invalid Option: \"" << argv[i] << '"' << std::endl;
            return 1;
        }
    }

    stopretty(data.champion_name);

    std::cout << "Options:\n"
              << "Champion Name: \"" << data.champion_name << "\"\n"
              << "Client Window Class: \"" << data.client_window_class << "\"\n"
              << "Client Window Description: \"" << data.client_window_description << "\"\n"
              << "Game Window Class: \"" << data.game_window_class << "\"\n"
              << "Game Window Description: \"" << data.game_window_description << "\"\n"
              << std::endl;

    data.champion = atoc(data.champion_name);
    if (data.champion == gameplay::champion::INVALID)
    {
        std::cerr << "Champion \"" << data.champion_name << "\" is invalid and likely isn't implemented yet." << std::endl;
        return 2;
    }

    data.client_bot = new client_bot();

    // Sleep(2500);
    switch (data.champion)
    {
    case gameplay::champion::ASHE:
        data.champion_bot = new ashe_bot();
        break;
    case gameplay::champion::INVALID:
    default:
        std::cerr << "failed\nChampion \"" << data.champion_name << "\" does not have a rule to be constructed in the driver." << std::endl;
        return 3;
    }

    // std::cout << argc << std::endl;
    // std::cout << argv[0] << std::endl;

    HandleCommandInput(data);

    return 0;
}

std::string HandleArgument(int &arg, char *argv[]) { return argv[arg++]; }

bool MatchArgument(int &arg, char *argv[], std::string const &argument)
{
    if (argument == argv[arg])
    {
        ++arg;
        return true;
    }
    else
        return false;
}

std::string &HandleArgumentWithPrefix(int &arg, char *argv[], std::string const &prefix, std::string &argument)
{
    if (prefix == argv[arg])
    {
        argument = argv[arg + 1];
        arg += 2;
    }
    return argument;
}