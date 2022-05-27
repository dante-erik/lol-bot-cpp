#include "LevelingBot.hpp"
#include "LevelingBotPixelsAndPoints.hpp"
#include "Pixel.hpp"
#include <iostream>
#include <chrono>
#include <memory>

using namespace std::chrono;

LevelingBot::LevelingBot()
	: health(1.0),
	mana(1.0),
	tolerance(0),
	keyClickDuration(140),
	keyClickDurationRandomness(60),
	mouseClickDuration(70),
	mouseClickDurationRandomness(30),
	gameStart(steady_clock::now()),
	robot(std::make_unique<Robot>())
	//clientBot(std::make_unique<LevelingClientBot>())
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

bool LevelingBot::playGame() {
	if (isNewGame()) {
		startInGameTimer();
		buyItems();
	}

	updateHealth();

	if (health < .42) {
		backToBase();
		buyItems();
		waitForFullHealth();
	}
	else {
		attack();
		levelUpAbilities();
	}
	return true;
}

bool LevelingBot::startInGameTimer() {
	gameStart = steady_clock::now();
	return true;
}

bool LevelingBot::attack() {
	//ability casting section
	//health < 0.95 (in combat)
	//q or w usable, otherwise updating mana is a waste of time
	if (health < 0.95 &&
	   (robot->isPixelSimilar(Q_USABLE, tolerance) ||
		robot->isPixelSimilar(W_USABLE, tolerance))) {
		updateMana();
		if (mana > 0.2) {
			if (robot->isPixelSimilar(Q_USABLE, tolerance)) {
				castAbilities("q");
			}
			if (robot->isPixelSimilar(W_USABLE, tolerance)) {
				castAbilities("w");
			}
		}
	}
	//basic attacking section
	robot->keyClick('a', getKeyClickDuration());
	return static_cast<bool>(robot->leftClick(pointJitter(getSafeAttackLocation(), 1), getMouseClickDuration()));
}

//if in base at end of function return true, else false
bool LevelingBot::backToBase() {
	POINT recallLocation = getSafeRecallLocation();
	//move to safety
	while (isChampAlive() && !isChampStandingOnPoint(recallLocation)) {
		robot->rightClick(getSafeRecallLocation(), getMouseClickDuration());

		robot->updateScreenBuffer();
		updateHealth();
	}

	//recall if you didnt die and you are not in base
	while (isChampAlive() && !isChampInBase()) {
		robot->keyClick('b', getKeyClickDuration());

		Sleep(1000 + getKeyClickDuration());
		robot->updateScreenBuffer();
		updateHealth();
	}

	robot->updateScreenBuffer();
	if (isChampInBase()) {
		return true;
	}
	else {
		return false;
	}
}

bool LevelingBot::buyItem(const char* itemName) {
	robot->keyClick('p', getKeyClickDuration());
	robot->ctrlPlusKeyClick('l', getKeyClickDuration());
	robot->keyClick(itemName, getKeyClickDuration());
	robot->enterKeyClick(getKeyClickDuration());
	return static_cast<bool>(robot->escapeKeyClick(getKeyClickDuration()));
}

bool LevelingBot::isChampAlive() {
	//health > .00 is unreliable because there's a bug
	//in-game where you can gain hp in the health bar after you die
	return !isChampInBase() || health > .03;
}

bool LevelingBot::isChampStandingOnPoint(POINT p) {
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

bool LevelingBot::isChampInBase() {
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

//returns positive if item bought, negative if item sold, number is the item slot from 1 to 6 inclusive
//full build returns 0, no items bought or sold
int32_t LevelingBot::buyItems() {
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
		return 1;
	}
	else {
		//full build!
		return 0;
	}
}

bool LevelingBot::sellItem1() {
	return static_cast<bool>(robot->rightClick(EMPTY_ITEM_SLOT_1.p, getMouseClickDuration()));
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
	return POINT{ p.x - distanceFromPoint +
		          static_cast<int32_t>(robot->getRandomNumber(2 * distanceFromPoint)),
				  p.y - distanceFromPoint +
		          static_cast<int32_t>(robot->getRandomNumber(2 * distanceFromPoint)) };
}

bool LevelingBot::levelUpAbilities() {
	if (robot->isPixelSimilar(CAN_LEVEL_UP_ABILITY, tolerance)) {
		return static_cast<bool>(robot->ctrlPlusKeyClick("rqwe", getKeyClickDuration()));
	}
	return false;
}

bool LevelingBot::waitForFullHealth() {
	while (health < .95 && isChampInBase()) {
		robot->updateScreenBuffer();
		updateHealth();
	}
	return true;
}

bool LevelingBot::isNewGame() {
	return (robot->isPixelSimilar(EMPTY_ITEM_SLOT_1, tolerance) &&
		    robot->isPixelSimilar(EMPTY_ITEM_SLOT_2, tolerance));
}

steady_clock::time_point LevelingBot::getGameTime() {
	return steady_clock::time_point(steady_clock::now() - gameStart);
}

bool LevelingBot::updateHealth() {
	//minimum green value in the health bar for it be considered health vs empty
	constexpr BYTE greenThreshold = 50;
	//higher value, faster performance, lower accuracy on returned health value
	int offsetIterator = 4;
	for (int xOffset = 0; xOffset < FULL_HEALTH.p.x - ZERO_HEALTH.p.x; xOffset += offsetIterator) {
		if (robot->getGreen({ ZERO_HEALTH.p.x + xOffset, ZERO_HEALTH.p.y }) < greenThreshold) {
			health = static_cast<double>(xOffset) / (FULL_HEALTH.p.x - ZERO_HEALTH.p.x);
			return true;
		}
	}
	health = 1.0;
	return true;
}

bool LevelingBot::updateMana() {
	//minimum blue value in the mana bar for it to be considered mana vs empty
	constexpr BYTE blueThreshold = 80;
	//higher value, faster performance, lower accuracy on returned mana value
	int offsetIterator = 20;
	for (int xOffset = 0; xOffset < FULL_MANA.p.x - ZERO_MANA.p.x; xOffset += offsetIterator) {
		if (robot->getBlue({ ZERO_MANA.p.x + xOffset, ZERO_MANA.p.y }) < blueThreshold) {
			mana = static_cast<double>(xOffset) / (FULL_MANA.p.x - ZERO_MANA.p.x);
			return true;
		}
	}
	mana = 1.0;
	return true;
}

bool LevelingBot::castAbilities(const char* abilities) {
	//center screen on champ
	robot->fKeyDown(1);
	//move mouse to generic attack location for most abilities
	robot->setCursorPos(ABILITY_ATTACK_LOCATION);
	robot->keyClick(abilities, getKeyClickDuration());
	return static_cast<bool>(robot->fKeyUp(1));
}

int LevelingBot::getMouseClickDuration() {
	return mouseClickDuration + robot->getRandomNumber(mouseClickDurationRandomness);
}

int LevelingBot::getKeyClickDuration() {
	return keyClickDuration + robot->getRandomNumber(keyClickDurationRandomness);
}