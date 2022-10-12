#pragma once
#include <Windows.h>
#include "Robot.hpp"

class ClientLevelingBot {
public:
	ClientLevelingBot();
	~ClientLevelingBot();
	void clientActions();

private:
	const int tolerance;
	const int keyClickDuration;
	const int keyClickDurationRandomness;
	const int mouseClickDuration;
	const int mouseClickDurationRandomness;
	std::unique_ptr<Robot> robot;
};