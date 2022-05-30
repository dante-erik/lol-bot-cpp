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
	recall(steady_clock::now()),
	dragonSpawn(steady_clock::now()),
	dragonPing(steady_clock::now()),
	dragonTimerPing(steady_clock::now()),
	riftHeraldSpawn(steady_clock::now()),
	riftHeraldPing(steady_clock::now()),
	riftHeraldTimerPing(steady_clock::now()),
	baronSpawn(steady_clock::now()),
	baronPing(steady_clock::now()),
	baronTimerPing(steady_clock::now()),
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

//ACTIONS:

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
	if (isYuumiAttached() && isEUsable()) {
		robot->keyClick('e', getKeyClickDuration());
	}
}

void YuumiBot::levelUpAbilities() {
	if (isYuumiLevelUp()) {
		robot->ctrlPlusKeyClick("reqw", getKeyClickDuration());
	}
}

void YuumiBot::lockCamera() {
	if (!isCameraLocked()) {
		robot->keyClick('y', getKeyClickDuration());
	}
}

void YuumiBot::ping(const POINT location) {
	robot->keyClick('g', getKeyClickDuration());
	robot->leftClick(location, getMouseClickDuration());
}

void YuumiBot::pingBaron() {
	if (isBaronAlive()) {
		ping(BARON);
		baronPing = steady_clock::now();
	}
}

void YuumiBot::pingBaronTimer(const long long timeUntilSpawn) {
	//ping if the actual (in-game) time until spawn is less than the parameterized (requested) time until spawn
	//and if the last time it was pinged was before the parameterized (requested) time until spawn
	//this prevents the function from being called more than once before the enemy spawns
	if (duration_cast<seconds>(getTimeUntil(baronSpawn).time_since_epoch().count()) < timeUntilSpawn &&
		duration_cast<seconds>(getTimeSince(baronTimerPing).time_since_epoch().count()) > timeUntilSpawn) {
		robot->keyClick('o', getKeyClickDuration());
		robot->leftClick(BARON_TIMER, getMouseClickDuration());
		robot->keyClick('o', getKeyClickDuration());
		baronTimerPing = steady_clock::now();
	}
}

void YuumiBot::pingDragon() {
	if (isDragonAlive()) {
		ping(DRAGON);
		dragonPing = steady_clock::now();
	}
}

void YuumiBot::pingDragonTimer(const long long timeUntilSpawn) {
	//ping if the actual (in-game) time until spawn is less than the parameterized (requested) time until spawn
	//and if the last time it was pinged was before the parameterized (requested) time until spawn
	//this prevents the function from being called more than once before the enemy spawns
	if (duration_cast<seconds>(getTimeUntil(dragonSpawn).time_since_epoch().count()) < timeUntilSpawn &&
		duration_cast<seconds>(getTimeSince(dragonTimerPing).time_since_epoch().count()) > timeUntilSpawn) {
		robot->keyClick('o', getKeyClickDuration());
		robot->leftClick(DRAGON_TIMER, getMouseClickDuration());
		robot->keyClick('o', getKeyClickDuration());
		dragonTimerPing = steady_clock::now();
	}
}

void YuumiBot::pingE() {
	//if E is not usable, pinging it will show the reason it is not usable
	//might be not usable due to cooldown, mana, or other reason
	if (!isEUsable()) {
		ping(ABILITY_E);
		ePing = steady_clock::now();
	}
}

void YuumiBot::pingQ() {
	if (!isQUsable()) {
		ping(ABILITY_Q);
		qPing = steady_clock::now();
	}
}

void YuumiBot::pingR() {
	if (!isRUsable()) {
		ping(ABILITY_R);
		rPing = steady_clock::now();
	}
}

void YuumiBot::pingRecall() {
	constexpr long long timeThresholdForRecallPing = 600;
	if (getSeconds(getTimeSince(recall)) > timeThresholdForRecallPing &&
		getSeconds(getTimeSince(recallPing)) < timeThresholdForRecallPing) {
		ping(RECALL_BUTTON);
		recallPing = steady_clock::now();
	}
}

void YuumiBot::pingRiftHerald() {
	if (isRiftHeraldAlive()) {
		ping(RIFT_HERALD);
		riftHeraldPing = steady_clock::now();
	}
}

void YuumiBot::pingRiftHeraldTimer(const long long timeUntilSpawn) {
	if (duration_cast<seconds>(getTimeUntil(riftHeraldSpawn).time_since_epoch().count()) < timeUntilSpawn &&
		duration_cast<seconds>(getTimeSince(riftHeraldTimerPing).time_since_epoch().count()) > timeUntilSpawn) {
		robot->keyClick('o', getKeyClickDuration());
		robot->leftClick(BARON_TIMER, getMouseClickDuration());
		robot->keyClick('o', getKeyClickDuration());
		riftHeraldTimerPing = steady_clock::now();
	}
}

void YuumiBot::pingW() {
	if (isWUsable()) {
		ping(ABILITY_W);
		wPing = steady_clock::now();
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
	if (isCameraLocked()) {
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
	while (health[YUUMI] > 0.95f && isYuumiInBase()) {
		robot->updateScreenBuffer();
		updateHealth();
	}
}

//PIXEL CHECKING:

bool YuumiBot::didAllyAssist(int ally) {
	constexpr int pixelsPerAllyIcon = 2;
	constexpr int xOffset = -5, yOffset = -5;
	//these pixels are in the assist feed's positions
	Pixel allyIconPixels[pixelsPerAllyIcon]{};
	for (int pixelIndex = 0; pixelIndex < pixelsPerAllyIcon; pixelIndex++) {
		//x and y offset should make the x and y of the pixel placed in the assist feed
		allyIconPixels[pixelIndex] = Pixel{
			{allyIcon[ally][pixelIndex].p.x + xOffset, allyIcon[ally][pixelIndex].p.x + yOffset},
			allyIcon[ally][pixelIndex].r,
			allyIcon[ally][pixelIndex].g,
			allyIcon[ally][pixelIndex].b };
		if (!robot->isPixelSimilar(allyIconPixels[pixelIndex], tolerance)) {
			return false;
		}
	}
	return true;
}
//bool didAllyAssist(int ally);
//bool didAllyDie(int ally);
//bool didAllyKill(int ally);
//bool didBaronDie();
//bool didDragonDie();
//bool didRiftHeraldDie();
//int getItemSlotIndexForItem(const Pixel item);
//bool isAllyAlive(int ally);
//bool isBaronAlive();
//bool isCameraLocked();
////use white box on minimap
//bool isChampInBase(int ally);
////if redside changes the offsets, will need a bool for which side you're on then
//bool isChampStandingOnPoint(POINT p, int ally);
//bool isDragonAlive();
//bool isEUsable();
//bool isNewGame();
//bool isQUsable();
//bool isRiftHeraldAlive();
//bool isRUsable();
//bool isWUsable();
////specific to checking only if Yuumi is alive, not other champs
//bool isYuumiAlive();
//bool isYuumiAttached();
//bool isYuumiInBase();
//bool isYuumiLevelUp();