#pragma once
#include <iostream>
#include "Robot.hpp"
#include "LeagueStructs.hpp"
#include <memory>

class OutOfGameBot {
private:
	std::unique_ptr<Robot> robot;
	BOOL newChampSelect;
	BOOL newGame;
	const BYTE tolerance;
	const char* champName;
	const char* champBan;
	const Role role;
	const Runes runes;
	const SummonerSpells ss;
	const ChampSelectType champSelectType;

	int debugDelay;

	BOOL findMatch();

	BOOL acceptMatch();

	BOOL champSelect();

	BOOL honorTeammate();

	BOOL playAgain();

	BOOL dismissLevelUp();

	BOOL dismissDailyReward();

	BOOL acceptChampionReward();

	BOOL dismissQuestReward();

	void champSelectActions();

	void noBansChampSelectActions();

	void hasBansChampSelectActions();

	void selectChampion();

	void banChampion();

	void typeRoleInChat();

	void setSummonerSpells();

	void selectSummonerSpell(const SummonerSpell& ss);

	void setRunes();

	void setPrimaryTree();

	void setSecondaryTree();

	void setKeystone();

	void setPrimaryLesserRune(const LesserRune&);

	void setSecondaryLesserRune(const LesserRune&);

	void setShardRune(const ShardRuneSlot1&);

	void setShardRune(const ShardRuneSlot2&);

	void setShardRune(const ShardRuneSlot3&);

	void lockInChampion();

public:
	OutOfGameBot(const char* champName, const Role& role, const Runes& runes, const SummonerSpells& ss, const ChampSelectType& champSelectType, const BYTE& tolerance = 0, const char* champBan = "");

	~OutOfGameBot();

	BYTE clientActions();
};