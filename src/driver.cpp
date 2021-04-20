#include <iostream>

// Gives the different bot types, bot, client_bot, champion_bot
#include "headers/bots.hpp"
// Gives the different champion bot implementations
#include "headers/champions.hpp"

char *HandleArgument(int &arg, char *argv[]);
bool MatchArgument(int &arg, char *argv[], const char* argument);
char *HandleArgumentWithPrefix(int &arg, char *argv[], const char *prefix, char *&argument);

int main(int argc, char *argv[])
{
    constexpr char* default_champion_name = "Ashe";
    constexpr char* default_client_window_class = "RCLIENT";
    constexpr char* default_client_window_description = "League of Legends";
    constexpr char* default_game_window_class = "RiotWindowClass";
    constexpr char* default_game_window_description = "League of Legends (TM) Client";
    char *champion_name = default_champion_name;
    char *client_window_class = "RCLIENT";
    char *client_window_description = "League of Legends";
    char *game_window_class = "RiotWindowClass";
    char *game_window_description = "League of Legends (TM) Client";
    int i = 1;
    while(i < argc) {
        int j = i;
        HandleArgumentWithPrefix(i, argv, "-champion", champion_name);
        if(i != j) continue;
        HandleArgumentWithPrefix(i, argv, "-clientwc", client_window_class);
        if(i != j) continue;
        HandleArgumentWithPrefix(i, argv, "-clientwd", client_window_description);
        if(i != j) continue;
        HandleArgumentWithPrefix(i, argv, "-gamewc", game_window_class);
        if(i != j) continue;
        HandleArgumentWithPrefix(i, argv, "-gamewd", game_window_description);
        if(i != j) continue;
        if(MatchArgument(i, argv, "-h") || MatchArgument(i, argv, "-help") || MatchArgument(i, argv, "help") || MatchArgument(i, argv, "h")) {
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
        if(i == j) {
            std::cerr << "Invalid Option: \"" << argv[i] << '"' << std::endl;
            return 1;
        }
    }
    std::cout << "Options:\n"
    << "Champion Name: \"" << champion_name << "\"\n"
    << "Client Window Class: \"" << client_window_class << "\"\n"
    << "Client Window Description: \"" << client_window_description << "\"\n"
    << "Game Window Class: \"" << game_window_class << "\"\n"
    << "Game Window Description: \"" << game_window_description << "\"\n"
    << std::endl;

    champion champ = atoc(champion_name);
    if(champ == champion::INVALID) {
        std::cerr << "Champion \"" << champion_name << "\" is invalid and likely isn't implemented yet." << std::endl;
        return 2;
    }

    std::cout << "Creating Client Bot..." << std::flush;
    client_bot client;
    std::cout << "done" << std::endl;
    std::cout << "Creating " << champion_name << " Bot..." << std::flush;
    champion_bot *champion = new ashe_bot();
    std::cout << "done" << std::endl;
    champion->start();
    WaitForSingleObject(champion->get_hThread(), INFINITE);
    return 0;
}

char *HandleArgument(int &arg, char *argv[]) { return argv[arg++]; }

bool MatchArgument(int &arg, char *argv[], const char* argument) {
    if(strcmp(argument, argv[arg])) {
        ++arg;
        return true;
    } else return false;
}

char *HandleArgumentWithPrefix(int &arg, char *argv[], const char *prefix, char *&argument) {
    if(strcmp(prefix, argv[arg]) == 0) {
        argument = argv[arg + 1];
        arg += 2;
    }
    return argument;
}