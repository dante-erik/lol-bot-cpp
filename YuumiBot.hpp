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
	Pixel allyIcon[5];
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
	std::chrono::steady_clock::time_point recall;
	std::chrono::steady_clock::time_point recallPing;
	std::chrono::steady_clock::time_point dragonSpawn;
	std::chrono::steady_clock::time_point dragonPing;
	std::chrono::steady_clock::time_point dragonTimerPing;
	std::chrono::steady_clock::time_point riftHeraldSpawn;
	std::chrono::steady_clock::time_point riftHeraldPing;
	std::chrono::steady_clock::time_point riftHeraldTimerPing;
	std::chrono::steady_clock::time_point baronSpawn;
	std::chrono::steady_clock::time_point baronPing;
	std::chrono::steady_clock::time_point baronTimerPing;
	std::chrono::steady_clock::time_point topDie;
	std::chrono::steady_clock::time_point jungleDie;
	std::chrono::steady_clock::time_point midDie;
	std::chrono::steady_clock::time_point adcDie;
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
	void ping(const POINT location);
	//handles all in-game actions
	void pingBaron();
	void pingBaronTimer(const long long timeUntilSpawn);
	void pingDragon();
	void pingDragonTimer(const long long timeUntilSpawn);
	void pingE();
	void pingQ();
	void pingR();
	void pingRecall();
	void pingRiftHerald();
	void pingRiftHeraldTimer(const long long timeUntilSpawn);
	void pingW();
	void playGame();
	void unattachFromAlly();
	void unlockCamera();
	void useItem(const Pixel item, int ally);
	void waitForFullHealth();

	//PIXEL CHECKING:
	//note: there's so many of these methods because the names
	//are self-documenting and helpful when thinking about logic in other methods
	bool didAllyAssist(int ally);
	bool didAllyDie(int ally);
	bool didAllyKill(int ally);
	bool didBaronDie();
	bool didDragonDie();
	bool didRiftHeraldDie();
	int getItemSlotIndexForItem(const Pixel item);
	bool isAllyAlive(int ally);
	bool isAnyEnemyDead();
	bool isBaronAlive();
	bool isCameraLocked();
	//use white box on minimap
	bool isChampInBase(int ally);
	//if redside changes the offsets, will need a bool for which side you're on then
	bool isChampStandingOnPoint(POINT p, int ally);
	bool isDragonAlive();
	bool isEUsable();
	bool isNewGame();
	bool isQUsable();
	bool isRiftHeraldAlive();
	bool isRUsable();
	bool isWUsable();
	//specific to checking only if Yuumi is alive, not other champs
	bool isYuumiAlive();
	bool isYuumiAttached();
	bool isYuumiInBase();
	bool isYuumiLevelUp();

	//TIME:
	//returns time since startTime
	long long getSeconds(std::chrono::steady_clock::time_point time);
	std::chrono::steady_clock::time_point getTimeSince(std::chrono::steady_clock::time_point startTime);
	std::chrono::steady_clock::time_point getTimeUntil(std::chrono::steady_clock::time_point time);

	//UPDATE GLOBALS:
	void updateAllyBase();
	void updateAllyIcons();
	void updateBaronSpawn();
	void updateCurrentAlly();
	void updateDragonSpawn();
	void updateHealth();
	void updateRiftHeraldSpawn();
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