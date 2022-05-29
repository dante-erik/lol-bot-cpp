#pragma once
#include <Windows.h>
#include <chrono>
#include "Robot.hpp"

enum ally{
	YUUMI, TOP, JG, MID, ADC
};

class YuumiBot {
private:
	//each ally's portrait over minimap, 2 pixels per ally
	Pixel allyIcon[5][2];
	//all allies HP, only YUUMI mana
	float health[5], weightedKDA[5];
	int kills[5], deaths[5], assists[5], currentAlly;
	//used for Robot
	const int tolerance;
	const int keyClickDuration, keyClickDurationRandomness;
	const int mouseClickDuration, mouseClickDurationRandomness;
	//these time_points are used to keep track of game time, item and ability cd's, and other useful timers
	std::chrono::steady_clock::time_point gameStart;
	std::chrono::steady_clock::time_point qPing;
	std::chrono::steady_clock::time_point wPing;
	std::chrono::steady_clock::time_point ePing;
	std::chrono::steady_clock::time_point rPing;
	std::chrono::steady_clock::time_point buy;
	std::chrono::steady_clock::time_point recall;
	std::chrono::steady_clock::time_point die;
	std::chrono::steady_clock::time_point dragonKill;
	std::chrono::steady_clock::time_point riftHeraldKill;
	std::chrono::steady_clock::time_point baronKill;
	std::chrono::steady_clock::time_point mikaels;
	std::chrono::steady_clock::time_point redemption;
	std::chrono::steady_clock::time_point shurelyas;
	std::chrono::steady_clock::time_point iceSupportItem;
	std::unique_ptr<Robot> robot;
	//std::unique_ptr<YuumiClientBot> clientBot;

	//ACTIONS:
	bool attachToAlly(int ally);
	bool attack();
	bool backToBase();
	bool buyItem(const char* itemName);
	int32_t buyItems();
	bool castAbilities(const char* abilities);
	bool healAttachedAlly();
	bool levelUpAbilities();
	//handles all in-game actions
	bool playGame();
	bool useItems(const char* itemNumbers, int ally);
	bool waitForFullHealth();

	//PIXEL CHECKING:
	//use white box on minimap
	bool isChampInBase(int ally);
	//if redside changes the offsets, will need a bool for which side you're on then
	bool isChampStandingOnPoint(POINT p, int ally);
	bool isNewGame();
	//specific to checking only if Yuumi is alive, not other champs
	bool isYuumiAlive();
	bool didAllyKill(int ally);
	bool didAllyDie(int ally);
	bool didAllyAssist(int ally);

	//TIME:
	//returns time since startTime
	std::chrono::steady_clock::time_point getTimeSince(std::chrono::steady_clock::time_point startTime);

	//UPDATE GLOBALS:
	bool updateHealth();
	bool updateWeightedKDA();
	bool updateAllyIcons();
	bool updateCurrentAlly();

	//RANDOMNESS:
	int getKeyClickDuration();
	int getMouseClickDuration();
	POINT pointJitter(const POINT& p, const int& distanceFromPoint);

public:
	YuumiBot();
	~YuumiBot();
	void runBot();
};