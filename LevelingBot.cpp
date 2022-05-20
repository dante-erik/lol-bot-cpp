#include "LevelingBot.hpp"
#include "LevelingBotPixelsAndPoints.hpp"
#include "Pixel.hpp"
#include <iostream>
#include <chrono>
#include <memory>

using namespace std::chrono;

LevelingBot::LevelingBot()
	: health(0.0),
	tolerance(0),
	keyClickDuration(70),
	keyClickDurationRandomness(20),
	mouseClickDuration(60),
	mouseClickDurationRandomness(15),
	gameStart(steady_clock::now()),
	robot(std::make_unique<Robot>())
	//outOfGameBot(std::make_unique<OutOfGameBot>())
{ }

LevelingBot::~LevelingBot() { }

void LevelingBot::runBot() {
	while (true) {
		robot->updateScreenBuffer();

		if (robot->isPixelSimilar(IN_GAME_HUD, tolerance)) {
			playGame();
		}
		else if (robot->isPixelSimilar(CLIENT_BORDER, tolerance)) {
			//outOfGameBot->clientActions();
		}
		else { }
	}
}

BOOL LevelingBot::playGame() {
	if (isNewGame()) {
		gameStart = steady_clock::now();
		buyItems();
	}

	updateHealth();

	if (health < .3) {
		backToBase();
		buyItems();
		waitForFullHealth();
	}
	else {
		attack();
		levelUpAbilities();
	}
}

BOOL LevelingBot::attack() {
	robot->keyClick('a', getKeyClickDuration());
	robot->leftClick(getSafeAttackLocation(), getMouseClickDuration());
}

BOOL LevelingBot::backToBase() {
	POINT recallLocation = getSafeRecallLocation();;
	//move to safety
	while (isChampAlive() && !isChampStandingOnPoint(recallLocation) && !isChampInBase()) {
		robot->rightClick(getSafeRecallLocation(), getMouseClickDuration());
		robot->updateScreenBuffer();
	}
	//recall if you didnt walk back to base or die
	while (isChampAlive() && !isChampInBase()) {
		robot->keyClick('b', getKeyClickDuration());
		Sleep(1000);
		robot->updateScreenBuffer();
	}

	if (isChampAlive() && isChampInBase()) {
		return 2;
	}

	return 1;
}

BOOL LevelingBot::buyItem(const char* itemName) {
	robot->keyClick('p', getKeyClickDuration());
	robot->ctrlPlusKeyClick('l', getKeyClickDuration());
	robot->keyClick(itemName, getKeyClickDuration());
	robot->enterKeyClick(getKeyClickDuration());
	robot->escapeKeyClick(getKeyClickDuration());
	return 1;
}

BOOL LevelingBot::isChampAlive() {
	return !(robot->isPixelSimilar(SHOP_BRIGHT) && health < .05);
}

BOOL LevelingBot::isChampStandingOnPoint(POINT p) {
	LONG xOffset = 0, yOffset = 0;
	//checks if the bottom left and top right corners of the minimap's champion camera white box to see if the champion is centered on the point p
	//snaps camera to champion
	return robot->isPixelSimilar(Pixel{ {p.x - xOffset, p.y - yOffset}, 255, 255, 255 }, tolerance) && robot->isPixelSimilar(Pixel{ {p.x + xOffset, p.y + yOffset}, 255, 255, 255 }, tolerance);
}

BOOL LevelingBot::isChampInBase() {
	return robot->isPixelSimilar(SHOP_BRIGHT, tolerance);
}

POINT LevelingBot::getSafeRecallLocation() {
	//if there isn't fog of war, the tower should still be standing so it's safe to recall
	if (!robot->isPixelSimilar(FOW_ALLY_MID_TOWER_1, tolerance)) {
		return SAFE_RECALL_MID_TOWER_1;
	}
	else if (!robot->isPixelSimilar(FOW_ALLY_MID_TOWER_2, tolerance)) {
		return SAFE_RECALL_MID_TOWER_2;
	}
	else if (!robot->isPixelSimilar(FOW_ALLY_MID_TOWER_3, tolerance)) {
		return SAFE_RECALL_MID_TOWER_3;
	}
	else {
		//faster to walk back to base if inhib tower is down
		return ALLY_BASE;
	}
}

BOOL LevelingBot::buyItems() {
	//if 2nd item bought, don't re-buy dorans shield after selling it after buying the 6th item
	if (robot->isPixelSimilar(EMPTY_ITEM_SLOT_1, tolerance) && robot->isPixelSimilar(EMPTY_ITEM_SLOT_2, tolerance)) {
		buyItem("dorans shield");
		return 1;
	}
	else if (robot->isPixelSimilar(EMPTY_ITEM_SLOT_2, tolerance)) {
		buyItem("immortal shieldbow");
		return 2;
	}
	else if (robot->isPixelSimilar(EMPTY_ITEM_SLOT_3, tolerance)) {
		buyItem("berserker greaves");
		return 3;
	}
	else if (robot->isPixelSimilar(EMPTY_ITEM_SLOT_4, tolerance)) {
		buyItem("phantom dancer");
		return 4;
	}
	else if (robot->isPixelSimilar(EMPTY_ITEM_SLOT_5, tolerance)) {
		buyItem("bloodthirster");
		return 5;
	}
	else if (robot->isPixelSimilar(EMPTY_ITEM_SLOT_6, tolerance)) {
		buyItem("infinity edge");
		return 6;
	}
	else if (robot->isPixelSimilar(DORANS_SHIELD_ITEM_SLOT_1, tolerance)) {
		sellItem1();
		return -1;
	}
	else if (robot->isPixelSimilar(EMPTY_ITEM_SLOT_1, tolerance)) {
		buyItem("rapidfire cannon");
		return 7;
	}
	else {
		//full build!
		return 0;
	}
}

BOOL LevelingBot::sellItem1() {
	robot->rightClick(EMPTY_ITEM_SLOT_1.p, getMouseClickDuration());
}

POINT LevelingBot::getSafeAttackLocation() {
	//try to end game if more than 29 mins passed
	if (duration_cast<minutes>(getGameTime().time_since_epoch()) > minutes(29)) {
		return SAFE_ATTACK_NEXUS;
	}
	else if (robot->isPixelSimilar(FOW_MID_TOWER_1, tolerance)) {
		//just a point not a pixel
		return SAFE_ATTACK_MID_TOWER_1;
	}
	else if (robot->isPixelSimilar(FOW_MID_TOWER_2, tolerance)) {
		return SAFE_ATTACK_MID_TOWER_2;
	}
	else if (robot->isPixelSimilar(FOW_MID_TOWER_3, tolerance)) {
		return SAFE_ATTACK_MID_TOWER_3;
	}
	else if (robot->isPixelSimilar(FOW_NEXUS_TOWER_1, tolerance) || robot->isPixelSimilar(FOW_NEXUS_TOWER_2, tolerance)) {
		return SAFE_ATTACK_NEXUS_TOWERS;
	}
	else {
		return SAFE_ATTACK_NEXUS;
	}
}

BOOL LevelingBot::levelUpAbilities() {
	if (robot->isPixelSimilar(CAN_LEVEL_UP_R, tolerance)) {
		robot->ctrlPlusKeyClick('r', getKeyClickDuration());
		return 4;
	}
	else if (robot->isPixelSimilar(CAN_LEVEL_UP_Q, tolerance)) {
		robot->ctrlPlusKeyClick('q', getKeyClickDuration());
		return 1;
	}
	else if (robot->isPixelSimilar(CAN_LEVEL_UP_E, tolerance)) {
		robot->ctrlPlusKeyClick('e', getKeyClickDuration());
		return 3;
	}
	else if (robot->isPixelSimilar(CAN_LEVEL_UP_W, tolerance)) {
		robot->ctrlPlusKeyClick('w', getKeyClickDuration());
		return 2;
	}
	return 0;
}

BOOL LevelingBot::waitForFullHealth() {
	while (health < .95 && isChampInBase()) {
		robot->updateScreenBuffer();
		updateHealth();
	}
}

BOOL LevelingBot::isNewGame() {
	return (robot->isPixelSimilar(EMPTY_ITEM_SLOT_1, tolerance) && robot->isPixelSimilar(EMPTY_ITEM_SLOT_2, tolerance));
}

steady_clock::time_point LevelingBot::getGameTime() {
	return steady_clock::time_point(steady_clock::now() - gameStart);
}

BOOL LevelingBot::updateHealth() {
	const BYTE greenThreshold = 110;
	for (int xOffset = 0; xOffset < FULL_HEALTH.p.x - ZERO_HEALTH.p.x; xOffset+=4) {
		if (robot->getGreen({ ZERO_HEALTH.p.x + xOffset, ZERO_HEALTH.p.y }) < greenThreshold) {
			health = (double)xOffset / (FULL_HEALTH.p.x - ZERO_HEALTH.p.x);
			return 2;
		}
	}
	health = 1.0;
	return 1;
}

int LevelingBot::getMouseClickDuration() {
	return mouseClickDuration + robot->getRandomNumber(mouseClickDurationRandomness);
}

int LevelingBot::getKeyClickDuration() {
	return keyClickDuration + robot->getRandomNumber(keyClickDurationRandomness);
}