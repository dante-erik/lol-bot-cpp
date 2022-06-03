#include "YuumiBot.hpp"
#include "YuumiBotPixelsAndPoints.hpp"
#include <iostream>

using namespace std::chrono;

YuumiBot::YuumiBot()
	: allyIcon{ Pixel{{0,0},0,0,0},
				Pixel{{0,0},0,0,0},
				Pixel{{0,0},0,0,0},
				Pixel{{0,0},0,0,0},
				Pixel{{0,0},0,0,0} },
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
		robot->setCursorPos(allyIcon[ally].p);
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

//this function will return true if ally is shown in the assist section
//of the kill feed. this includes assisting enemies on epic monster kills
bool YuumiBot::didAllyAssist(int ally) {
	//im 90% sure there can only be 4 assists in the killfeed, maybe im wrong tho
	constexpr int MAX_NUMBER_OF_ASSISTS_IN_KILL_FEED = 4;
	//minimap offsets move the pixel x,y to the 1st assist position on kill feed
	//killfeed offset move the pixel left from the 1st ... 4th posistions on kill feed

	//SET THE REAL VALUES MAY 30 2022
	constexpr int X_OFFSET_MINIMAP = -5, Y_OFFSET_MINIMAP = -5, X_OFFSET_KILL_FEED = -10;
	//these pixels are in the assist feed's positions
	Pixel allyIconPixelInKillFeed;
	for (int offsetMultiplier = 0; offsetMultiplier < MAX_NUMBER_OF_ASSISTS_IN_KILL_FEED; offsetMultiplier++) {
		//x and y offset should make the x and y of the pixel placed in the assist feed
		//the assist feed's icon is smaller, you possibly need to scale the x,y and colors
		//after scaling, then the use xyoffset translation, and then loop thru that
		allyIconPixelInKillFeed = Pixel{
			POINT{allyIcon[ally].p.x + X_OFFSET_MINIMAP + X_OFFSET_KILL_FEED * offsetMultiplier,
			allyIcon[ally].p.x + Y_OFFSET_MINIMAP},
			allyIcon[ally].r,
			allyIcon[ally].g,
			allyIcon[ally].b };
		//isAnyEnemyDead() protects against random assists being added when an assist
		//would not have been possible due to no enemy deaths
		if (robot->isPixelSimilar(allyIconPixelInKillFeed, tolerance) && isAnyEnemyDead()) {
			constexpr int DURATION_OF_KILL_FEED = 6;
			switch (ally) {
			case TOP:
				if (getSeconds(getTimeSince(topAssist)) > DURATION_OF_KILL_FEED) {
					topAssist = steady_clock::now();
					return true;
				}
				break;
			case JG:
				if (getSeconds(getTimeSince(jungleAssist)) > DURATION_OF_KILL_FEED) {
					jungleAssist = steady_clock::now();
					return true;
				}
				break;
			case MID:
				if (getSeconds(getTimeSince(midAssist)) > DURATION_OF_KILL_FEED) {
					midAssist = steady_clock::now();
					return true;
				}
				break;
			case ADC:
				if (getSeconds(getTimeSince(adcAssist)) > DURATION_OF_KILL_FEED) {
					adcAssist = steady_clock::now();
					return true;
				}
				break;
			default:
				break;
			}
		}
	}
	return false;
}

bool YuumiBot::didAllyDie(int ally) {
	if (!isAllyAlive(ally)) {
		//the real max death timer as of patch 12.10 is 78.75 seconds,
		//but 78.75 is practically never reached and setting MAX_DEATH_TIMER
		//higher risks an ally dying twice within the timer duration
		constexpr int MAX_DEATH_TIMER = 55;
		switch (ally) {
		case TOP:
			if (getSeconds(getTimeSince(topDie)) > MAX_DEATH_TIMER) {
				topDie = steady_clock::now();
				return true;
			}
			break;
		case JG:
			if (getSeconds(getTimeSince(jungleDie)) > MAX_DEATH_TIMER) {
				jungleDie = steady_clock::now();
				return true;
			}
			break;
		case MID:
			if (getSeconds(getTimeSince(midDie)) > MAX_DEATH_TIMER) {
				midDie = steady_clock::now();
				return true;
			}
			break; 
		case ADC:
			if (getSeconds(getTimeSince(adcDie)) > MAX_DEATH_TIMER) {
				adcDie = steady_clock::now();
				return true;
			}
			break;
		default:
			break;
		}
	}
	return false;
}

bool YuumiBot::didAllyKill(int ally) {
	//these translate the minimap ally icon pixel to the kill feed kill pixel location
	//ACTUALLY SET REAL VALUES JUNE 2
	constexpr int X_OFFSET_MINIMAP = -5, Y_OFFSET_MINIMAP = -6;

	//allyIcon pixel translated x,y
	const Pixel allyIconPixelInKillFeed = Pixel{
			POINT{allyIcon[ally].p.x + X_OFFSET_MINIMAP,
			allyIcon[ally].p.x + Y_OFFSET_MINIMAP},
			allyIcon[ally].r,
			allyIcon[ally].g,
			allyIcon[ally].b };

	//isAnyEnemyDead() protects against random assists being added when an assist
		//would not have been possible due to no enemy deaths
	if (robot->isPixelSimilar(allyIconPixelInKillFeed, tolerance) && isAnyEnemyDead()) {
		constexpr int DURATION_OF_KILL_FEED = 6;
		switch (ally) {
		case TOP:
			if (getSeconds(getTimeSince(topKill)) > DURATION_OF_KILL_FEED) {
				topKill = steady_clock::now();
				return true;
			}
			break;
		case JG:
			if (getSeconds(getTimeSince(jungleKill)) > DURATION_OF_KILL_FEED) {
				jungleKill = steady_clock::now();
				return true;
			}
			break;
		case MID:
			if (getSeconds(getTimeSince(midKill)) > DURATION_OF_KILL_FEED) {
				midKill = steady_clock::now();
				return true;
			}
			break;
		case ADC:
			if (getSeconds(getTimeSince(adcKill)) > DURATION_OF_KILL_FEED) {
				adcKill = steady_clock::now();
				return true;
			}
			break;
		default:
			break;
		}
	}
	return false;
}

bool YuumiBot::didBaronDie() {
	if (robot->isPixelSimilar(BARON_IN_KILL_FEED, tolerance) && !isBaronAlive()) {
		//set baronSpawn to be 5 minutes into the future from now
		//baronSpawn = 
		return true;
	}
	return false;
}

bool YuumiBot::didDragonDie() {
	if (robot->isPixelSimilar(DRAGON_IN_KILL_FEED, tolerance) && !isDragonAlive()) {
		//same as baron
		return true;
	}
	return false;
}

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