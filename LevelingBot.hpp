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

	bool playGame();
	bool startInGameTimer();
	bool attack();
	bool buyItems();
	bool backToBase();
	bool levelUpAbilities();
	POINT getSafeAttackLocation();
	POINT pointJitter(const POINT& p, const int& distanceFromPoint);
	bool updateHealth();
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

public:
	LevelingBot();
	~LevelingBot();
	void runBot();
};