#include "Robot.hpp"
#include "LeaguePixels.hpp"
#include <memory>
#include <random>

#define VISIBLE(pixelName) robot->isPixelEqual(pixelName)
//left clicks within mouseInaccuracy pixels of pixelName's x and y, and holds down the mouse button for between clickDurationMin and clickDurationMax milliseconds
#define LEFT_CLICK(pixelName) robot->leftClick(Pixel{{pixelName.p.x - mouseInaccuracy + getRandomNumber(0, mouseInaccuracy * 2), pixelName.p.y - 1 + getRandomNumber(0, 2)}}.p, getRandomNumber(clickDurationMin, clickDurationMax))
//right clicks within mouseInaccuracy pixels of pixelName's x and y, and holds down the mouse button for between clickDurationMin and clickDurationMax milliseconds
#define RIGHT_CLICK(pixelName) robot->rightClick(Pixel{{pixelName.p.x - mouseInaccuracy + getRandomNumber(0, mouseInaccuracy * 2), pixelName.p.y - 1 + getRandomNumber(0, 2)}}.p, getRandomNumber(clickDurationMin, clickDurationMax))

//simulates all the input events as if a human were inputting mouse / keyboard events
std::unique_ptr<Robot> robot = std::make_unique<Robot>();

//random number generator
std::unique_ptr<std::mt19937> rng = std::make_unique<std::mt19937>();

//milliseconds for click events using mouse and keyboard
constexpr int clickDurationMax = 70;
constexpr int clickDurationMin = 40;

//how many pixels the LEFT_CLICK and RIGHT_CLICK macros can click away from the given pixel value x and y
constexpr int mouseInaccuracy = 2;

int getRandomNumber(const int& min, const int& max) {
	return rng->operator()() % (max - min + 1) + min;
}


void selectRandomChampion() {
	//in pixel coor units
	constexpr int X_CHAMPION_ICON_OFFSET = 101;
	constexpr int Y_CHAMPION_ICON_OFFSET = 96;
	Pixel championIcon = { {TOP_LEFT_CHAMPION_ICON.p.x + X_CHAMPION_ICON_OFFSET * getRandomNumber(0, 6),
							TOP_LEFT_CHAMPION_ICON.p.y + Y_CHAMPION_ICON_OFFSET * getRandomNumber(0, 3)} };
	LEFT_CLICK(championIcon);
}

void championSelectActions() {
	//loop until champion is locked in & still in champion select
	while (!VISIBLE(CHAMPION_LOCKED_IN) && VISIBLE(CHAMPION_SELECT)) {

		selectRandomChampion();
		LEFT_CLICK(LOCK_IN);

		robot->updateScreenBuffer();
	}
}


void acceptChampionReward() {
	LEFT_CLICK(CHAMPION_REWARD_SELECT_BUTTON);
	//client lags after selecting the champion
	Sleep(4000);
	LEFT_CLICK(CHAMPION_REWARD_OKAY_BUTTON);
}

void levelUpAbilities() {
	robot->ctrlPlusKeyClick("rqwe", getRandomNumber(clickDurationMin, clickDurationMax));
}

void buyItem(const char* itemName) {
	//open shop
	robot->keyClick('p', getRandomNumber(clickDurationMin, clickDurationMax));

	//shop search bar hotkey
	robot->ctrlPlusKeyClick('l', getRandomNumber(clickDurationMin, clickDurationMax));

	//search for item
	robot->keyClick(itemName, getRandomNumber(clickDurationMin, clickDurationMax));

	//buy item
	robot->enterKeyClick(getRandomNumber(clickDurationMin, clickDurationMax));

	//close shop
	robot->escapeKeyClick(getRandomNumber(clickDurationMin, clickDurationMax));
}

void moveRandomlyIntoMidLane() {
	constexpr int sleepDurationBetweenRightClicks = 1000;

	constexpr int millisecondsBeforeMinionsSpawn = 60000;

	constexpr int durationBetweenRightClicks = sleepDurationBetweenRightClicks + (clickDurationMin + clickDurationMax) / 2;

	int totalRightClickInputs = millisecondsBeforeMinionsSpawn / durationBetweenRightClicks;

	Pixel randomPlaceToMoveChampionTo;

	for (int rightClickInputs = 0; rightClickInputs < totalRightClickInputs; rightClickInputs++) {
		//should be some random location in the top right quadrant of a 1920x1080 screen the champion can walk to before minions spawn
		randomPlaceToMoveChampionTo = { {getRandomNumber(1920 / 2, 1920 - 1920 / 4), getRandomNumber(0 + 1080 / 4, 1080 / 2)} };

		RIGHT_CLICK(randomPlaceToMoveChampionTo);
		Sleep(sleepDurationBetweenRightClicks);
	}
}

void gameActions(bool& isNewGame) {
	if (isNewGame) {
		levelUpAbilities();
		//buys steel shoulderguards or relic shield support item for easier minion killing / faster pushing
		if (getRandomNumber(0, 1) == 1) {
			buyItem("shoulderguards");
		}
		else {
			buyItem("relic");
		}

		constexpr int waitTimeAfterBuyingStartingItem = 20000;
		Sleep(waitTimeAfterBuyingStartingItem);

		//wait for minions to spawn without getting AFK warnings by sitting in base
		moveRandomlyIntoMidLane();

		isNewGame = false;
	}
	levelUpAbilities();
	//health > 30%, attack enemy base
	if (VISIBLE(LOW_HEALTH)) {
		robot->keyClick('a', getRandomNumber(clickDurationMin, clickDurationMax));
		LEFT_CLICK(ENEMY_NEXUS);
	}
	//health < 30%, walk to ally base and wait until full health is reached
	else {
		while (!VISIBLE(FULL_HEALTH) && VISIBLE(GAME_HUD)) {
			RIGHT_CLICK(ALLY_BASE);
			robot->updateScreenBuffer();
		}
	}
}

void clientActions(bool& isNewGame) {
	//client bug: find match randomly highlights after games regardless of cursor position
	//fix: add highlighted pixel value for find match
	if (VISIBLE(FIND_MATCH) || VISIBLE(FIND_MATCH_HIGHLIGHTED)) {
		isNewGame = true;
		LEFT_CLICK(FIND_MATCH);
	}
	else if (VISIBLE(ACCEPT_MATCH) || VISIBLE(ACCEPT_MATCH_HIGHLIGHTED)) {
		LEFT_CLICK(ACCEPT_MATCH);
	}
	else if (VISIBLE(CHAMPION_SELECT)) {
		championSelectActions();
	}
	else if (VISIBLE(HONOR_TEAMMATE)) {
		//client lags when displaying honor teammate
		Sleep(4000);
		LEFT_CLICK(HONOR_TEAMMATE);
	}
	else if (VISIBLE(PLAY_AGAIN) || VISIBLE(PLAY_AGAIN_HIGHLIGHTED)) {
		LEFT_CLICK(PLAY_AGAIN);
	}
	else if (VISIBLE(GENERIC_REWARD) || VISIBLE(GENERIC_REWARD_HIGHLIGHTED)) {
		//client lags when displaying rewards
		Sleep(4000);
		LEFT_CLICK(GENERIC_REWARD);
	}
	else if (VISIBLE(CHAMPION_REWARD)) {
		//client lags when displaying champion reward
		Sleep(4000);
		acceptChampionReward();
	}
	else if (VISIBLE(PROBLEM_SELECTING_YOUR_CHAMPION) || VISIBLE(PROBLEM_SELECTING_YOUR_CHAMPION_HIGHLIGHTED)) {
		LEFT_CLICK(PROBLEM_SELECTING_YOUR_CHAMPION);
	}
	else if (VISIBLE(CHALLENGE_TIER_UP)) {
		LEFT_CLICK(CHALLENGE_TIER_UP);
	}
}



int main()
{

	bool isNewGame = false;

	while (true) {
		robot->updateScreenBuffer();

		//in game
		if (VISIBLE(GAME_HUD)) {
			gameActions(isNewGame);
		}
		//in client or nothing visible
		else {
			clientActions(isNewGame);
		}
	}

	return 0;
}

