#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "../headers/shell.hpp"

std::ostream &shellprompt(std::ostream &os) { return os << shell::prompt; }

std::string GetInput(std::istream &is);

std::vector<std::string> GetTokens(std::string input);

void HandleCommandInput(ControlData &cd, std::istream &is, std::ostream &os, std::ostream &er)
{
    bool loop = true;
    while (loop)
    {
        while(cd.client_bot->get_Status() != bot::status::COMPLETED || cd.champion_bot->get_Status() != bot::status::COMPLETED) {
            os << shellprompt;
            std::vector<std::string> tokens = GetTokens(GetInput(is));
            if(tokens.empty()) continue;
            std::string command = tokens.front();
            tokens.erase(tokens.begin());
            if(command == "help") {
                os << "help: Prints this dialogue\n"
                << "chat: Has the bot print a message into the chat\n"
                << std::endl;
            } else if (command == "start") {
                if(tokens.empty() || tokens.front() == "client") {
                    cd.client_bot->start();
                } else if (tokens.front() == "champion") {
                    cd.champion_bot->start();
                }
            } else if (command == "stop") {
                if(tokens.empty() || tokens.front() == "champion") {
                    cd.champion_bot->stop();
                } else if (tokens.front() == "client") {
                    cd.client_bot->stop();
                }
            } else if (command == "chat") {
                std::string chat_msg;
                for(auto const& token : tokens) {
                    chat_msg += token;
                    if(&token != &tokens.back()) {
                        chat_msg += ' ';
                    }
                }
                cd.champion_bot->chat(chat_msg.c_str());
            } else if (command == "champion") {
                if(tokens.empty()) {
                    os << "Current Champion: " << cd.champion_bot->champion_name() << std::endl;
                } else {
                    gameplay::champion champion = atoc(tokens.front());
                    if(champion == gameplay::champion::INVALID) {
                        os << "Champion: " << tokens.front() << " cannot be set because it is not a valid champion.\n" << "It will remain as " << cd.champion_name << ".\n" << tokens.front() << " may not be implemented yet or you may have made a spelling error." << std::endl;
                    } else {
                        if(cd.champion_name != cd.champion_bot->champion_name() && cd.champion_name != tokens.front()) {
                            os << "Champion was set to change from " << cd.champion_bot->champion_name() << " to " << cd.champion_name << " after the current game but now:\n";
                        }
                        os << "Champion will change from " << cd.champion_bot->champion_name() << " to " << stopretty(tokens.front()) << " as soon as the current game ends." << std::endl;
                        cd.champion_name = tokens.front();
                    }
                }
            } else if (command == "quit") {
                loop = false;
                if(tokens.empty()) {
                    os << "Will quit when the current actions are complete." << std::endl;
                    os << "Try 'quit force' to forcefully quit immediately." << std::endl;
                } else if(tokens.at(0) == "force") {
                    delete cd.client_bot;
                    delete cd.champion_bot;
                    break;
                }
            } else {
                er << "Error: Command \"" << command << "\" not found. Try \"help\" to get help on commands." << std::endl;
            }
        }
        // TODO: Fire client bot events
        // TODO: Reconstruct Bot
        // TODO: Fire champion bot again
    }
}

std::string GetInput(std::istream &is)
{
    std::string input;
    std::getline(is, input);
    return input;
}

std::vector<std::string> GetTokens(std::string input)
{
    std::vector<std::string> tokens;
    if(!input.empty()) {
        std::istringstream stream(input);
        std::string token;
        while(stream >> token) {
            if(token.front() == '"') {
                std::string temp;
                std::getline(stream, temp, '"');
                token.erase(token.begin());
                token += temp;
            }
            if(token.front() == '\'') {
                std::string temp;
                std::getline(stream, temp, '\'');
                token.erase(token.begin());
                token += temp;
            }
            tokens.push_back(token);
        }
    }
    return tokens;
}
