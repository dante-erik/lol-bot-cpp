#include "Robot.hpp"
#include "LeaguePixels.hpp"
#include <memory>
#include <random>
#include <array>
#include <string>

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
	//there are better ways to do this function
	return rng->operator()() % (MAX - MIN + 1) + MIN;
}

void waitUntilBanPhase() {
	while (!VISIBLE(BAN_PHASE) && VISIBLE(CHAMPION_SELECT)) {
		robot->updateScreenBuffer();
	}
}

void banNone() {
	robot->updateScreenBuffer();
	if (VISIBLE(BAN_PHASE)) {
		LEFT_CLICK(NO_BAN);
		LEFT_CLICK(LOCK_IN_BAN);
	}
}

void waitUntilAbleToPickChampion() {
	while (!VISIBLE(ABLE_TO_PICK_CHAMPION) && VISIBLE(CHAMPION_SELECT)) {
		robot->updateScreenBuffer();
	}
}

void clearChampionSelectSearchBox() {
	LEFT_CLICK(CHAMPION_SELECT_SEARCH_BOX);
	robot->ctrlPlusKeyClick('a', getRandomNumber(CLICK_DURATION_MIN_MILLISECONDS, CLICK_DURATION_MAX_MILLISECONDS));
	robot->backspaceKeyClick(getRandomNumber(CLICK_DURATION_MIN_MILLISECONDS, CLICK_DURATION_MAX_MILLISECONDS));
}

void pickRandomChampion() {
	//copy this func from the other bot
}

void pickChampion() {
	//for now, it'll only be champions with a heal on W to simplify the in-game actions
	std::array<std::string, 4> playableChampions = { "soraka", "sona", "seraphine", "nami" };

	for (int index = 0; index < playableChampions.size(); index++) {
		robot->updateScreenBuffer();
		if (!VISIBLE(LOCK_IN_CHAMPION) && VISIBLE(ABLE_TO_PICK_CHAMPION)) {
			LEFT_CLICK(CHAMPION_SELECT_SEARCH_BOX);

			robot->keyClick(playableChampions.at(index).c_str(), getRandomNumber(CLICK_DURATION_MIN_MILLISECONDS, CLICK_DURATION_MAX_MILLISECONDS));

			LEFT_CLICK(TOP_LEFT_CHAMPION_ICON);

			clearChampionSelectSearchBox();
		}
		else {
			//if a champion is locked in or champ select is dodged or every playable champion is tried, end loop
			index = playableChampions.size();
		}
	}

	robot->updateScreenBuffer();

	//if every playable champ is banned, picked, or not owned, then pick a random one
	while (!VISIBLE(LOCK_IN_CHAMPION) && VISIBLE(ABLE_TO_PICK_CHAMPION)) {
		pickRandomChampion();
		robot->updateScreenBuffer();
	}
}

void setRunesAndSummonerSpells() {
	LEFT_CLICK(RIOT_RECOMMENDED_RUNES_AND_SUMMONER_SPELLS);

	robot->updateScreenBuffer();

	if (VISIBLE(ALLOW_SUMMONER_SPELL_CHANGES)) {
		LEFT_CLICK(ALLOW_SUMMONER_SPELL_CHANGES);
	}

	LEFT_CLICK(LEFT_RECOMMENDED_RUNES_AND_SUMMONER_SPELLS_OPTION);
	//check if you need to exit the recc runes page after choosing an option
}

void championSelectActions() {
	waitUntilBanPhase();
	banNone();
	waitUntilAbleToPickChampion();
	pickChampion();
	setRunesAndSummonerSpells();
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

double getADCCurrentHealth() {
	double health = 0.0;

	//linear search adc health bar above minimap

	return health;
}

double getCurrentHealth() {
	double health = 0.0;

	//binary search health bar
	
	return health;
}

double getCurrentMana() {
	double mana = 0.0;

	//binary search mana bar

	return mana;
}

void gameActions(bool& isNewGame) {
	if (isNewGame) {
		levelUpAbilities();
		//buys spellthief's shard to avoid getting extra reports from ADC for not getting cannon with the
		//gold sharing support items
		buyItem("spellthief");

		isNewGame = false;
	}

	if (VISIBLE(SKILL_POINT)) {
		levelUpAbilities();
	}

	const double health = getCurrentHealth();
	const double mana = getCurrentMana();

	if (health > 0.30 && mana > 0.10) {
		//follow ally
		//randomly heal / shield them every 20-30 seconds
		//attack enemies every 20-30 seconds
	}
	else {
		//implement a recall function, walking to base is suspicious
		while (health < .90 && VISIBLE(GAME_HUD)) {
			RIGHT_CLICK(ALLY_BASE);
			robot->updateScreenBuffer();
		}

		//can add a more complicated buy function later if bot gets banned
		//ardent censor
		buyItem("Ardent");
		//imperial mandate
		buyItem("Imperial");
	}
}

void dismissClientPopups() {
	if (VISIBLE(GENERIC_REWARD) || VISIBLE(GENERIC_REWARD_HIGHLIGHTED)) {
		//client lags when displaying rewards
		Sleep(CLIENT_LAG_MILLISECONDS);
		LEFT_CLICK(GENERIC_REWARD);
	}
	else if (VISIBLE(CHALLENGE_TIER_UP)) {
		LEFT_CLICK(CHALLENGE_TIER_UP);
	}
	else if (VISIBLE(VERIFY_EMAIL)) {
		LEFT_CLICK(VERIFY_EMAIL);
	}
}

void startNewGame() {
	if (VISIBLE(FIND_MATCH) || VISIBLE(FIND_MATCH_HIGHLIGHTED)) {
		LEFT_CLICK(FIND_MATCH);
	}
	else if (VISIBLE(ACCEPT_MATCH) || VISIBLE(ACCEPT_MATCH_HIGHLIGHTED)) {
		LEFT_CLICK(ACCEPT_MATCH);
	}
	else if (VISIBLE(PLAY_AGAIN) || VISIBLE(PLAY_AGAIN_HIGHLIGHTED)) {
		LEFT_CLICK(PLAY_AGAIN);
	}
	else if (VISIBLE(SKIP_WAITING_FOR_STATS)) {
		LEFT_CLICK(SKIP_WAITING_FOR_STATS);
	}
	else if (VISIBLE(HONOR_TEAMMATE)) {
		//client lags when displaying honor teammate
		Sleep(CLIENT_LAG_MILLISECONDS);
		LEFT_CLICK(HONOR_TEAMMATE);
	}
	else {
		dismissClientPopups();
	}
}

void clientActions(bool& isNewGame) {

	if (VISIBLE(CHAMPION_SELECT)) {
		isNewGame = true;
		championSelectActions();
	}
	else {
		startNewGame();
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

