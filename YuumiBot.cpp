#include "YuumiBot.hpp"
#include "YuumiBotPixelsAndPoints.hpp"
#include <iostream>

using namespace std::chrono;

YuumiBot::YuumiBot()
	: allyIcon{ {Pixel{{0,0},0,0,0}, Pixel{{0,0},0,0,0}},
				{ Pixel{{0,0},0,0,0}, Pixel{{0,0},0,0,0} },
				{ Pixel{{0,0},0,0,0}, Pixel{{0,0},0,0,0} },
				{ Pixel{{0,0},0,0,0}, Pixel{{0,0},0,0,0} },
				{ Pixel{{0,0},0,0,0}, Pixel{{0,0},0,0,0} }, },
	health{ 1.0, 1.0, 1.0, 1.0, 1.0 },
	weightedKDA{ 0.0, 0.0, 0.0, 0.0, 0.0 },
	kills{ 0, 0, 0, 0, 0 },
	deaths{ 0, 0, 0, 0, 0 },
	assists{ 0, 0, 0, 0, 0 },
	currentAlly(ADC),
	tolerance(0),
	keyClickDuration(50),
	keyClickDurationRandomness(20),
	mouseClickDuration(40),
	mouseClickDurationRandomness(20),
	allyBase({0,0}),
	gameStart(steady_clock::now()),
	qPing(steady_clock::now()),
	wPing(steady_clock::now()),
	ePing(steady_clock::now()),
	rPing(steady_clock::now()),
	buy(steady_clock::now()),
	recall(steady_clock::now()),
	die(steady_clock::now()),
	dragonKill(steady_clock::now()),
	riftHeraldKill(steady_clock::now()),
	baronKill(steady_clock::now()),
	mikaels(steady_clock::now()),
	redemption(steady_clock::now()),
	shurelyas(steady_clock::now()),
	iceSupportItem(steady_clock::now()),
	robot(std::make_unique<Robot>())
{ }

YuumiBot::~YuumiBot() { }

void YuumiBot::runBot() {
	while (true) {
		robot->updateScreenBuffer();

		if (robot->isPixelSimilar(IN_GAME_HUD, tolerance)) {
			playGame();
		}
		else if (robot->isPixelSimilar(CLIENT_BORDER, tolerance)) {
			std::cout << "out of game stuff\n";
		}
		else {
			std::cout << "nothing visible\n";
		}
	}
}

//returns true if able to attach to ally
void YuumiBot::attachToAlly(int ally) {
	while (isYuumiAlive() && isAllyAlive(ally)) {
		//right clicks on ally location in case W is on cooldown
		robot->fKeyDown(ally + 1);
		robot->rightClick(CENTER_OF_SCREEN, getMouseClickDuration());
		//tries casting W on ally icon above minimap
		robot->setCursorPos(allyIcon[ally][0].p);
		robot->keyClick('w', getKeyClickDuration());

		robot->updateScreenBuffer();
	}
}

void YuumiBot::attack() {
	
}

void YuumiBot::backToBase() {
	if (isYuumiAttached()) {
		unattachFromAlly();
	}

	while (isYuumiAlive() && !isYuumiInBase()) {
		robot->setCursorPos(allyBase);
		robot->rightClick(getMouseClickDuration());

		robot->updateScreenBuffer();
	}
}

void YuumiBot::buyItem(const char* itemName) {
	robot->keyClick('p', getKeyClickDuration());
	robot->ctrlPlusKeyClick('l', getKeyClickDuration());
	robot->keyClick(itemName, getKeyClickDuration());
	robot->enterKeyClick(getKeyClickDuration());
	robot->escapeKeyClick(getKeyClickDuration());
}

void YuumiBot::buyItems() {

}

void YuumiBot::healAttachedAlly() {
	if (isYuumiAttached() && robot->isPixelSimilar(E_USABLE, tolerance)) {
		robot->keyClick('e', getKeyClickDuration());
	}
}

void YuumiBot::levelUpAbilities() {
	if (robot->isPixelSimilar(CAN_LEVEL_UP_ABILITY, tolerance)) {
		robot->ctrlPlusKeyClick("reqw", getKeyClickDuration());
	}
}

void YuumiBot::lockCamera() {
	if (!robot->isPixelSimilar(CAMERA_LOCKED, tolerance)) {
		robot->keyClick('y', getKeyClickDuration());
	}
}

void YuumiBot::playGame() {

}

void YuumiBot::unattachFromAlly() {
	if (isYuumiAttached() && isYuumiAlive()) {
		unlockCamera();
		robot->leftClick(allyBase, getMouseClickDuration());
		robot->setCursorPos(CENTER_OF_SCREEN);
		robot->keyClick('w', getKeyClickDuration());
		lockCamera();
	}
}

void YuumiBot::unlockCamera() {
	if (robot->isPixelSimilar(CAMERA_LOCKED, tolerance)) {
		robot->keyClick('y', getKeyClickDuration());
	}
}

void YuumiBot::useItem(const Pixel item, int ally) {
	int itemIndex = getItemSlotIndexForItem(item);
	//if item was found
	if (itemIndex > 0) {
		robot->setCursorPos(allyIcon[ally][0].p);
		robot->keyClick(std::to_string(itemIndex).c_str(), getKeyClickDuration());
	}
}

void YuumiBot::waitForFullHealth() {
	//wait for the right-most health pixel to turn green
	while (robot->getGreen(FULL_HEALTH.p) < 80) {
		robot->updateScreenBuffer();
	}
}