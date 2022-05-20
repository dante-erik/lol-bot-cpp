#pragma once
#include <Windows.h>
#include <chrono>
#include "Robot.hpp"

class LevelingBot {
private:
	double health;
	const int tolerance;
	const int keyClickDuration;
	const int keyClickDurationRandomness;
	const int mouseClickDuration;
	const int mouseClickDurationRandomness;
	std::chrono::steady_clock::time_point gameStart;
    std::unique_ptr<Robot> robot;
	//outOfGameBot = std::make_unique<OutOfGameBot>();

	BOOL playGame();
	BOOL attack();
	BOOL buyItems();
	BOOL backToBase();
	BOOL levelUpAbilities();
	POINT getSafeAttackLocation();
	BOOL updateHealth();
	BOOL buyItem(const char* itemName);
	BOOL isChampAlive();
	BOOL isChampStandingOnPoint(POINT p);
	BOOL isChampInBase();
	POINT getSafeRecallLocation();
	BOOL sellItem1();
	BOOL waitForFullHealth();
	BOOL isNewGame();
	std::chrono::steady_clock::time_point getGameTime();
	int getMouseClickDuration();
	int getKeyClickDuration();

public:
	LevelingBot();
	~LevelingBot();
	void runBot();
};