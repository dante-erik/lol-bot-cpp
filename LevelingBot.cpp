#include "LevelingBot.hpp"
#include "LevelingBotPixelsAndPoints.hpp"
#include "Pixel.hpp"
#include <iostream>
#include <chrono>
#include <memory>

using namespace std::chrono;

LevelingBot::LevelingBot()
	: health(),
	tolerance(0),
	keyClickDuration(140),
	keyClickDurationRandomness(60),
	mouseClickDuration(70),
	mouseClickDurationRandomness(30),
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
			std::cout << "out of game stuff" << std::endl;
			//outOfGameBot->clientActions();
		}
		else {
			std::cout << "nothing visible" << std::endl;
		}
	}
}

BOOL LevelingBot::playGame() {
	if (isNewGame()) {
		startInGameTimer();
		buyItems();
	}

	updateHealth();

	if (health < .3) {
		backToBase();
		buyItems();
		return waitForFullHealth();
	}
	else {
		attack();
		return levelUpAbilities();
	}
}

BOOL LevelingBot::startInGameTimer() {
	gameStart = steady_clock::now();
	return 1;
}

BOOL LevelingBot::attack() {
	robot->keyClick('a', getKeyClickDuration());
	return robot->leftClick(pointJitter(getSafeAttackLocation(), 1), getMouseClickDuration());
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
	//shop lights up as soon as you die
	//it isn't health > .00 because there's a bug
	//you can gain hp in the health bar after you die
	return !robot->isPixelSimilar(SHOP_BRIGHT) || health > .05;
}

BOOL LevelingBot::isChampStandingOnPoint(POINT p) {
	constexpr LONG xLeftOffset = -34, yLeftOffset = -24, xRightOffset = 35, yRightOffset = 12;
	//set camera position on champion (F1 hotkey) so the offsets listed above are correct
	robot->fKeyDown(1);
	Sleep(getKeyClickDuration());
	robot->updateScreenBuffer();
	robot->fKeyUp(1);

	//checks if the top left and bottom right corners of the minimap's champion
	//camera white box to see if the champion is centered on the point p
	return robot->isPixelSimilar(Pixel{ {p.x + xLeftOffset, p.y + yLeftOffset}, 255, 255, 255 }, tolerance) &&
		   robot->isPixelSimilar(Pixel{ {p.x + xRightOffset, p.y + yRightOffset}, 255, 255, 255 }, tolerance);
}

BOOL LevelingBot::isChampInBase() {
	return robot->isPixelSimilar(SHOP_BRIGHT, tolerance);
}

POINT LevelingBot::getSafeRecallLocation() {
	//if there isn't fog of war,
	//the tower should still be standing so it's safe to recall
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
	//if 2nd item bought,
	//don't re-buy dorans shield after selling it after buying the 6th item
	if (robot->isPixelSimilar(EMPTY_ITEM_SLOT_1, tolerance) && robot->isPixelSimilar(EMPTY_ITEM_SLOT_2, tolerance)) {
		if (robot->getRandomNumber(1)) {
			buyItem("dorans shield");
		}
		else {
			buyItem("dorans blade");
		}
		return 1;
	}
	else if (robot->isPixelSimilar(EMPTY_ITEM_SLOT_2, tolerance)) {
		if (robot->getRandomNumber(1)) {
			buyItem("kraken slayer");
		}
		else {
			buyItem("immortal shieldbow");
		}
		return 2;
	}
	else if (robot->isPixelSimilar(EMPTY_ITEM_SLOT_3, tolerance)) {
		buyItem("berserker greaves");
		return 3;
	}
	else if (robot->isPixelSimilar(EMPTY_ITEM_SLOT_4, tolerance)) {
		if (robot->getRandomNumber(1)) {
			buyItem("phantom dancer");
		}
		else {
			buyItem("mortal reminder");
		}
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
	return robot->rightClick(EMPTY_ITEM_SLOT_1.p, getMouseClickDuration());
}

POINT LevelingBot::getSafeAttackLocation() {
	if (robot->isPixelSimilar(FOW_NEXUS_TOWERS, tolerance)) {
		if (robot->isPixelSimilar(FOW_MID_TOWER_3, tolerance)) {
			if (robot->isPixelSimilar(FOW_MID_TOWER_2, tolerance)) {
				if (robot->isPixelSimilar(FOW_MID_TOWER_1, tolerance)) {
					return SAFE_ATTACK_MID_TOWER_1;
				}
				return SAFE_ATTACK_MID_TOWER_2;
			}
			return SAFE_ATTACK_MID_TOWER_3;
		}
		return SAFE_ATTACK_NEXUS_TOWERS;
	}
	else {
		return SAFE_ATTACK_NEXUS;
	}
}

POINT LevelingBot::pointJitter(const POINT& p, const int& distanceFromPoint) {
	return POINT{ p.x - distanceFromPoint + static_cast<int32_t>(robot->getRandomNumber(2 * distanceFromPoint)),
				  p.y - distanceFromPoint + static_cast<int32_t>(robot->getRandomNumber(2 * distanceFromPoint)) };
}

BOOL LevelingBot::levelUpAbilities() {
	if (robot->isPixelSimilar(CAN_LEVEL_UP_ABILITY, tolerance)) {
		return robot->ctrlPlusKeyClick("rqwe", getKeyClickDuration());
	}
	return 0;
}

BOOL LevelingBot::waitForFullHealth() {
	while (health < .95 && isChampInBase()) {
		robot->updateScreenBuffer();
		updateHealth();
	}
	return 1;
}

BOOL LevelingBot::isNewGame() {
	return (robot->isPixelSimilar(EMPTY_ITEM_SLOT_1, tolerance) && robot->isPixelSimilar(EMPTY_ITEM_SLOT_2, tolerance));
}

steady_clock::time_point LevelingBot::getGameTime() {
	return steady_clock::time_point(steady_clock::now() - gameStart);
}

BOOL LevelingBot::updateHealth() {
	const BYTE greenThreshold = 50;
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