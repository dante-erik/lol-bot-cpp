#include "ClientLevelingBot.hpp"
#include <iostream>

ClientLevelingBot::ClientLevelingBot():
	tolerance(0),
	keyClickDuration(140),
	keyClickDurationRandomness(60),
	mouseClickDuration(70),
	mouseClickDurationRandomness(30),
	robot(std::make_unique<Robot>())
{}

ClientLevelingBot::~ClientLevelingBot() {}

void ClientLevelingBot::clientActions() {

}