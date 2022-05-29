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
	POINT allyBase;
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
	std::unique_ptr<Robot> robot;
	//std::unique_ptr<YuumiClientBot> clientBot;

	//ACTIONS:
	void attachToAlly(int ally);
	void attack();
	void backToBase();
	void buyItem(const char* itemName);
	void buyItems();
	void healAttachedAlly();
	void levelUpAbilities();
	void lockCamera();
	//handles all in-game actions
	void pingBaron();
	void pingDragon();
	void pingE();
	void pingQ();
	void pingR();
	void pingRecall();
	void pingRiftHerald();
	void pingW();
	void playGame();
	void unattachFromAlly();
	void unlockCamera();
	void useItem(const Pixel item, int ally);
	void waitForFullHealth();

	//PIXEL CHECKING:
	bool didAllyAssist(int ally);
	bool didAllyDie(int ally);
	bool didAllyKill(int ally);
	int getItemSlotIndexForItem(const Pixel item);
	bool isAllyAlive(int ally);
	//use white box on minimap
	bool isChampInBase(int ally);
	//if redside changes the offsets, will need a bool for which side you're on then
	bool isChampStandingOnPoint(POINT p, int ally);
	bool isNewGame();
	//specific to checking only if Yuumi is alive, not other champs
	bool isYuumiAlive();
	bool isYuumiAttached();
	bool isYuumiInBase();

	//TIME:
	//returns time since startTime
	std::chrono::steady_clock::time_point getTimeSince(std::chrono::steady_clock::time_point startTime);

	//UPDATE GLOBALS:
	void updateAllyBase();
	void updateAllyIcons();
	void updateCurrentAlly();
	void updateHealth();
	void updateWeightedKDA();

	//RANDOMNESS:
	int getKeyClickDuration();
	int getMouseClickDuration();
	POINT pointJitter(const POINT& p, const int& distanceFromPoint);

public:
	YuumiBot();
	~YuumiBot();
	void runBot();
};