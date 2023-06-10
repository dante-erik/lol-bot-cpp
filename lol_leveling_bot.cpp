#include "Robot.hpp"
#include "LeaguePixels.hpp"
#include <memory>
#include <random>

#define VISIBLE(pixelName) robot->isPixelEqual(pixelName)
//left clicks within MOUSE_INACCURACY_PIXELS pixels of pixelName's x and y, and holds down the mouse button for between CLICK_DURATION_MIN_MILLISECONDS and CLICK_DURATION_MAX_MILLISECONDS milliseconds
#define LEFT_CLICK(pixelName) robot->leftClick(Pixel{{pixelName.p.x - MOUSE_INACCURACY_PIXELS + getRandomNumber(0, MOUSE_INACCURACY_PIXELS * 2), pixelName.p.y - 1 + getRandomNumber(0, 2)}}.p, getRandomNumber(CLICK_DURATION_MIN_MILLISECONDS, CLICK_DURATION_MAX_MILLISECONDS))
//right clicks within MOUSE_INACCURACY_PIXELS pixels of pixelName's x and y, and holds down the mouse button for between CLICK_DURATION_MIN_MILLISECONDS and CLICK_DURATION_MAX_MILLISECONDS milliseconds
#define RIGHT_CLICK(pixelName) robot->rightClick(Pixel{{pixelName.p.x - MOUSE_INACCURACY_PIXELS + getRandomNumber(0, MOUSE_INACCURACY_PIXELS * 2), pixelName.p.y - 1 + getRandomNumber(0, 2)}}.p, getRandomNumber(CLICK_DURATION_MIN_MILLISECONDS, CLICK_DURATION_MAX_MILLISECONDS))

//simulates all the input events as if a human were inputting mouse / keyboard events
std::unique_ptr<Robot> robot = std::make_unique<Robot>();

//random number generator
std::unique_ptr<std::mt19937> rng = std::make_unique<std::mt19937>();

//milliseconds for click events using mouse and keyboard
constexpr int CLICK_DURATION_MAX_MILLISECONDS = 70;
constexpr int CLICK_DURATION_MIN_MILLISECONDS = 40;

//how many pixels the LEFT_CLICK and RIGHT_CLICK macros can click away from the given pixel value x and y
constexpr int MOUSE_INACCURACY_PIXELS = 2;

//client lags after most actions. small indie company
int CLIENT_LAG_MILLISECONDS = 4000;

int getRandomNumber(const int& MIN, const int& MAX) {
	return rng->operator()() % (MAX - MIN + 1) + MIN;
}


void selectRandomChampion() {
	constexpr int X_CHAMPION_ICON_OFFSET_PIXELS = 101;
	constexpr int Y_CHAMPION_ICON_OFFSET_PIXELS = 96;
	Pixel championIcon = { {TOP_LEFT_CHAMPION_ICON.p.x + X_CHAMPION_ICON_OFFSET_PIXELS * getRandomNumber(0, 6),
							TOP_LEFT_CHAMPION_ICON.p.y + Y_CHAMPION_ICON_OFFSET_PIXELS * getRandomNumber(0, 3)} };
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
	Sleep(CLIENT_LAG_MILLISECONDS);
	LEFT_CLICK(CHAMPION_REWARD_OKAY_BUTTON);
}

void levelUpAbilities() {
	robot->ctrlPlusKeyClick("rqwe", getRandomNumber(CLICK_DURATION_MIN_MILLISECONDS, CLICK_DURATION_MAX_MILLISECONDS));
}

void buyItem(const char* ITEM_NAME) {
	//open shop
	robot->keyClick('p', getRandomNumber(CLICK_DURATION_MIN_MILLISECONDS, CLICK_DURATION_MAX_MILLISECONDS));

	//shop search bar hotkey
	robot->ctrlPlusKeyClick('l', getRandomNumber(CLICK_DURATION_MIN_MILLISECONDS, CLICK_DURATION_MAX_MILLISECONDS));

	//search for item
	robot->keyClick(ITEM_NAME, getRandomNumber(CLICK_DURATION_MIN_MILLISECONDS, CLICK_DURATION_MAX_MILLISECONDS));

	//buy item
	robot->enterKeyClick(getRandomNumber(CLICK_DURATION_MIN_MILLISECONDS, CLICK_DURATION_MAX_MILLISECONDS));

	//close shop
	robot->escapeKeyClick(getRandomNumber(CLICK_DURATION_MIN_MILLISECONDS, CLICK_DURATION_MAX_MILLISECONDS));
}

void moveRandomlyIntoMidLane() {
	constexpr int SLEEP_DURATION_AFTER_BUYING_STARTING_ITEMS_MILLISECONDS = 20000;
	Sleep(SLEEP_DURATION_AFTER_BUYING_STARTING_ITEMS_MILLISECONDS);

	constexpr int DURATION_BEFORE_MINIONS_SPAWN_MILLISECONDS = 60000;
	constexpr int DURATION_BEFORE_MOVING_MILLISECONDS = DURATION_BEFORE_MINIONS_SPAWN_MILLISECONDS - SLEEP_DURATION_AFTER_BUYING_STARTING_ITEMS_MILLISECONDS;

	constexpr int SLEEP_DURATION_BETWEEN_RIGHT_CLICKS_MILLISECONDS = 3000;
	constexpr int AVERAGE_CLICK_DURATION_MILLISECONDS = (CLICK_DURATION_MIN_MILLISECONDS + CLICK_DURATION_MAX_MILLISECONDS) / 2;
	constexpr int TOTAL_DURATION_BETWEEN_RIGHT_CLICKS_MILLISECONDS = SLEEP_DURATION_BETWEEN_RIGHT_CLICKS_MILLISECONDS + AVERAGE_CLICK_DURATION_MILLISECONDS;

	constexpr int TOTAL_RIGHT_CLICK_INPUTS = DURATION_BEFORE_MOVING_MILLISECONDS / TOTAL_DURATION_BETWEEN_RIGHT_CLICKS_MILLISECONDS;

	Pixel randomPlaceToMoveChampionTo;

	for (int rightClickInputs = 0; rightClickInputs < TOTAL_RIGHT_CLICK_INPUTS; rightClickInputs++) {
		//should be some random location near current champion camera position in a 1920x1080 screen the champion can walk to before minions spawn
		randomPlaceToMoveChampionTo = { {getRandomNumber(1920 / 2, 1920 - 1920 / 3), 1080 / 2 - 20} };

		RIGHT_CLICK(randomPlaceToMoveChampionTo);
		Sleep(SLEEP_DURATION_BETWEEN_RIGHT_CLICKS_MILLISECONDS);
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

		//wait for minions to spawn without getting AFK warnings by sitting in base
		moveRandomlyIntoMidLane();

		isNewGame = false;
	}
	levelUpAbilities();
	//health > 30%, attack enemy base
	if (VISIBLE(LOW_HEALTH)) {
		robot->keyClick('a', getRandomNumber(CLICK_DURATION_MIN_MILLISECONDS, CLICK_DURATION_MAX_MILLISECONDS));
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
		Sleep(CLIENT_LAG_MILLISECONDS);
		LEFT_CLICK(HONOR_TEAMMATE);
	}
	else if (VISIBLE(PLAY_AGAIN) || VISIBLE(PLAY_AGAIN_HIGHLIGHTED)) {
		LEFT_CLICK(PLAY_AGAIN);
	}
	else if (VISIBLE(GENERIC_REWARD) || VISIBLE(GENERIC_REWARD_HIGHLIGHTED)) {
		//client lags when displaying rewards
		Sleep(CLIENT_LAG_MILLISECONDS);
		LEFT_CLICK(GENERIC_REWARD);
	}
	else if (VISIBLE(CHAMPION_REWARD)) {
		//client lags when displaying champion reward
		Sleep(CLIENT_LAG_MILLISECONDS);
		acceptChampionReward();
	}
	else if (VISIBLE(PROBLEM_SELECTING_YOUR_CHAMPION) || VISIBLE(PROBLEM_SELECTING_YOUR_CHAMPION_HIGHLIGHTED)) {
		LEFT_CLICK(PROBLEM_SELECTING_YOUR_CHAMPION);
	}
	else if (VISIBLE(CHALLENGE_TIER_UP)) {
		LEFT_CLICK(CHALLENGE_TIER_UP);
	}
	else if (VISIBLE(KEY_FRAGMENT_REWARD)) {
		LEFT_CLICK(KEY_FRAGMENT_REWARD);
	}/*
	else {
		LEFT_CLICK(PROBLEM_SELECTING_YOUR_CHAMPION);
	}*/
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

