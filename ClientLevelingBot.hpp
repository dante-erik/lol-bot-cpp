#pragma once
#include <Windows.h>
#include "Robot.hpp"

class ClientLevelingBot {
public:
	ClientLevelingBot();
	~ClientLevelingBot();
	void clientActions();

private:
	const int tolerance;
	const int keyClickDuration;
	const int keyClickDurationRandomness;
	const int mouseClickDuration;
	const int mouseClickDurationRandomness;
	std::unique_ptr<Robot> robot;

	bool findMatch();
	bool acceptMatch();
	bool champSelect();
	bool honorTeammate();
	bool playAgain();
	bool dismissLevelUp();
	bool dismissDailyReward();
	bool acceptChampionReward();
	bool dismissQuestReward();
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
};