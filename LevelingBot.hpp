#pragma once
#include <Windows.h>
#include <chrono>
#include "Robot.hpp"
#include "ClientLevelingBot.hpp"

class LevelingBot {
public:
	LevelingBot();
	~LevelingBot();
	void runBot();

private:
	double health, mana;
	const int tolerance;
	const int keyClickDuration;
	const int keyClickDurationRandomness;
	const int mouseClickDuration;
	const int mouseClickDurationRandomness;
	std::chrono::steady_clock::time_point gameStart;
    std::unique_ptr<Robot> robot;
	std::unique_ptr<ClientLevelingBot> clientBot;

	bool playGame();
	bool startInGameTimer();
	bool attack();
	int32_t buyItems();
	bool backToBase();
	bool levelUpAbilities();
	POINT getSafeAttackLocation();
	POINT pointJitter(const POINT& p, const int& distanceFromPoint);
	bool updateHealth();
	bool updateMana();
	bool castAbilities(const char* abilities);
	bool buyItem(const char* itemName);
	bool isChampAlive();
	bool isChampStandingOnPoint(POINT p);
	bool isChampInBase();
	POINT getSafeRecallLocation();
	bool sellItem1();
	bool waitForFullHealth();
	bool isNewGame();
	std::chrono::steady_clock::time_point getGameTime();
	int getMouseClickDuration();
	int getKeyClickDuration();
};