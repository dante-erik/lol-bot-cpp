#include "../headers/champion_bot.hpp"

champion_bot::champion_bot(std::string const& champion_name) : bot{}, _champion_name{champion_name} {}
champion_bot::~champion_bot() = default;

void champion_bot::chat(const char* msg) {
    keyboard::KeyType(VK_RETURN);
    keyboard::KeyType(msg);
    keyboard::KeyType(VK_RETURN);
}

std::string const& champion_bot::champion_name() const { return _champion_name; }
