#include <iostream>
#include "robot.hpp"
#include "LeaguePointsAndPixels.hpp"
#include "LeagueStructs.hpp"
#include "OutOfGameBot.hpp"
//OutOfGameBot(const char* champName, const Role& lane, const Runes& runePage, const SummonerSpells& ss, const ChampSelectType& cst, const BYTE& tol = 0, const char* champBan = "");
		OutOfGameBot::OutOfGameBot (const char* champName,
			const Role& role,
			const Runes& runes,
			const SummonerSpells& ss,
			const ChampSelectType& champSelectType,
			const BYTE& tolerance,
			const char* champBan) : champName(champName), role(role), runes(runes), ss(ss), champSelectType(champSelectType), tolerance(tolerance), champBan(champBan)
		{
			robot = std::make_unique<Robot>();
			newChampSelect = false;
			newGame = false;
			debugDelay = 750;
		}

		OutOfGameBot::~OutOfGameBot() {
			//idk what to delete here ngl
		}
		
		BYTE OutOfGameBot::clientActions(){
			//avoids highlighting buttons on the client
			robot->setCursorPos(CURSOR_OFF_CLIENT);
			//Sleep(1000);

			//complete one of these LoL Client actions, then break from the else if chain to update the screen buffer
			//std::cout << "I'm about to do what's called a pro gamer move" << std::endl;
			robot->updateScreenBuffer();
			//std::cout << "Jk Lmao" << std::endl;
			if (findMatch()) { std::cout << "findMatch() finished\n\n"; return 1; }
			else if (acceptMatch()) { std::cout << "acceptMatch() finished\n\n"; return 2; }
			else if (champSelect()) { std::cout << "champSelect() finished\n\n"; return 3; }
			else if (honorTeammate()) { std::cout << "honorTeammate() finished\n\n"; return 4; }
			else if (playAgain()) { std::cout << "playAgain() finished\n\n"; return 5; }
			else if (dismissLevelUp()) { std::cout << "dismissLevelUp() finished\n\n"; return 6; }
			else if (dismissDailyReward()) { std::cout << "dismissDailyReward() finished\n\n"; return 7; }
			else if (acceptChampionReward()) { std::cout << "acceptChampionReward() finished\n\n"; return 8; }
			else if (dismissQuestReward()) { std::cout << "dismissQuestReward() finished\n\n"; return 9; }
			else { std::cout << "did nothing this cycle lmao\n\n"; return 0; }
		}

		BOOL OutOfGameBot::findMatch() {
			if (robot->isPixelSimilar(FIND_MATCH_BUTTON, tolerance)) {
				robot->leftClick(FIND_MATCH_BUTTON.p);
				return true;
			}
			return false;
		}

		BOOL OutOfGameBot::acceptMatch() {
			if (robot->isPixelSimilar(ACCEPT_MATCH_BUTTON)) {
				robot->leftClick(ACCEPT_MATCH_BUTTON.p);
				newChampSelect = true;
				return true;
			}
			return false;
		}

		BOOL OutOfGameBot::champSelect() {
			if (newChampSelect && robot->isPixelSimilar(CHAMP_SELECT, tolerance)) {
				champSelectActions();
				newChampSelect = false;
				newGame = true;
				return true;
			}
			return false;
		}

		BOOL OutOfGameBot::honorTeammate() {
			if (robot->isPixelSimilar(HONOR_NO_TEAMMATE_ARROW, tolerance)) {
				robot->leftClick(HONOR_NO_TEAMMATE_ARROW.p);
				return true;
			}
			return false;
		}

		BOOL OutOfGameBot::playAgain() {
			if (robot->isPixelSimilar(PLAY_AGAIN_BUTTON, tolerance)) {
				robot->leftClick(PLAY_AGAIN_BUTTON.p);
				return true;
			}
			return false;
		}

		BOOL OutOfGameBot::dismissLevelUp() {
			if (robot->isPixelSimilar(LEVELED_UP, tolerance)) {
				robot->leftClick(LEVEL_UP_OK_BUTTON);
				return true;
			}
			return false;
		}

		BOOL OutOfGameBot::dismissDailyReward() {
			if (robot->isPixelSimilar(DAILY_REWARD, tolerance)) {
				robot->leftClick(DAILY_REWARD_OK_BUTTON);
				return true;
			}
			return false;
		}

		BOOL OutOfGameBot::acceptChampionReward() {
			if (robot->isPixelSimilar(CHAMPION_REWARD, tolerance)) {
				robot->leftClick(MIDDLE_CHAMPION_SELECT_BUTTON);
				robot->leftClick(CHAMPION_REWARD_OK_BUTTON);
				return true;
			}
			return false;
		}

		BOOL OutOfGameBot::dismissQuestReward() {
			if (robot->isPixelSimilar(QUEST_REWARD, tolerance)) {
				robot->leftClick(QUEST_REWARD_OK_BUTTON);
				return true;
			}
			return false;
		}

		void OutOfGameBot::champSelectActions(){
			switch (champSelectType) {
				case ChampSelectType::INTRO_BOTS:
				case ChampSelectType::BEGINNER_BOTS:
				case ChampSelectType::INTERMEDIATE_BOTS:
				case ChampSelectType::BLIND_NORMS:
					noBansChampSelectActions();
					break;
				case ChampSelectType::DRAFT_NORMS:
				case ChampSelectType::RANKED_SOLO_DUO:
				case ChampSelectType::RANKED_FLEX:
					hasBansChampSelectActions();
					break;
			}
		}

		void OutOfGameBot::noBansChampSelectActions(){
			selectChampion();
			typeRoleInChat();
			setSummonerSpells();
			setRunes();
			lockInChampion();
		}

		void OutOfGameBot::hasBansChampSelectActions(){
			selectChampion();
			banChampion();
			setSummonerSpells();
			setRunes();
			lockInChampion();
		}

		void OutOfGameBot::selectChampion(){
			//update screen buffer while in champ select UNTIL champion search box is visible
			while(!robot->isPixelSimilar(CHAMPION_SEARCH_BOX, tolerance) && robot->isPixelSimilar(CHAMP_SELECT, tolerance)){
				robot->updateScreenBuffer();
			}
			if(robot->isPixelSimilar(CHAMPION_SEARCH_BOX, tolerance)){
				robot->leftClick(CHAMPION_SEARCH_BOX.p);
				Sleep((int)(debugDelay*0.67)); // search box doesn't register key presses for a bit after left clicking it
				robot->keyClick(champName, 30);

				//praying it clicks the searched champ before a teammate does
				for(int numberOfClicks = 3; numberOfClicks > 0; numberOfClicks--){
					robot->leftClick(SEARCHED_CHAMPION_ICON, 333);
				}
			}

			Sleep(debugDelay);

			robot->updateScreenBuffer();

			//if the champion couldnt be selected, delete it's name from search, then pick champs starting from top left
			if (robot->isPixelSimilar(CHAMPION_NOT_SELECTED, tolerance)) {
				std::cout << "my champ was stolen, picking a diff one now" << std::endl;
				robot->leftClick(CHAMPION_SEARCH_BOX.p);
				Sleep(200);
				robot->ctrlPlusKeyClick('a');
				Sleep(200);
				robot->backspaceKeyClick();
				Sleep(200);
				int xOffsetPerChampIcon = 102;
				int yOffsetPerChampicon = 97;
				//top left icon
				POINT champIcon = { 708, 324 };
				for (int y = 0; y < 5; y++) {
					for (int x = 0; x < 6; x++) {
						champIcon.x = 708 + xOffsetPerChampIcon * x;
						champIcon.y = 324 + yOffsetPerChampicon * y;
						robot->leftClick(champIcon);
						Sleep(100);
						robot->updateScreenBuffer();
						//if a champion was selected, end of loops
						if (!robot->isPixelSimilar(CHAMPION_NOT_SELECTED, tolerance)) {
							x = 6;
							y = 5;
						}
					}
				}
			}
				
		}

		void OutOfGameBot::banChampion(){
			//update screen buffer while in champ select UNTIL bans are visible
			while(!robot->isPixelSimilar(BANS, tolerance) && robot->isPixelSimilar(CHAMP_SELECT, tolerance)){
				robot->updateScreenBuffer();
			}
			if(robot->isPixelSimilar(BANS, tolerance)){
				selectChampion();
				lockInChampion();
			}
		}

		void OutOfGameBot::typeRoleInChat(){
			robot->updateScreenBuffer();
			if (robot->isPixelSimilar(CHAMP_SELECT, tolerance)) {
				robot->leftClick(CHAMP_SELECT_CHAT_BOX);

				switch (role) {
				case Role::TOP:
					robot->keyClick("top", 30);
					break;
				case Role::JUNGLE:
					robot->keyClick("jungle", 30);
					break;
				case Role::MID:
					robot->keyClick("mid", 30);
					break;
				case Role::ADC:
					robot->keyClick("adc", 30);
					break;
				case Role::SUPPORT:
					robot->keyClick("support", 30);
					break;
				}
				Sleep(debugDelay);
				robot->enterKeyClick();
				Sleep(debugDelay);
			}
		}

		void OutOfGameBot::setSummonerSpells(){
			robot->updateScreenBuffer();
			if(robot->isPixelSimilar(CHAMP_SELECT, tolerance)){
				robot->leftClick(LEFT_SUMMONER_SPELL);
				Sleep(debugDelay);
				selectSummonerSpell(ss.left);
				Sleep(debugDelay);
	
				robot->updateScreenBuffer();
				//if SS Spell Panel didn't close after clicking a summoner spell
				if(robot->isPixelSimilar(SUMMONER_SPELL_PANEL, tolerance)){
					//if the panel is still visible, you dont have access to that summoner spell yet
					//so re-clicking left summoner spell closes the panel
					robot->leftClick(LEFT_SUMMONER_SPELL);
					Sleep(debugDelay);
				}
	
				robot->leftClick(RIGHT_SUMMONER_SPELL);
				Sleep(debugDelay);
				selectSummonerSpell(ss.right);
				Sleep(debugDelay);
	
				robot->updateScreenBuffer();
				if(robot->isPixelSimilar(SUMMONER_SPELL_PANEL, tolerance)){
					robot->leftClick(RIGHT_SUMMONER_SPELL);
					Sleep(debugDelay);
				}

				//clear the screen image with potentially the SS Panel up
				robot->updateScreenBuffer();
			}
		}

		void OutOfGameBot::selectSummonerSpell(const SummonerSpell& summonerSpell){
			robot->updateScreenBuffer();
			if (robot->isPixelSimilar(CHAMP_SELECT, tolerance)) {
				switch (summonerSpell) {
				case SummonerSpell::BARRIER:
					robot->leftClick(BARRIER);
					break;
				case SummonerSpell::CLEANSE:
					robot->leftClick(CLEANSE);
					break;
				case SummonerSpell::EXHAUST:
					robot->leftClick(EXHAUST);
					break;
				case SummonerSpell::FLASH:
					robot->leftClick(FLASH);
					break;
				case SummonerSpell::GHOST:
					robot->leftClick(GHOST);
					break;
				case SummonerSpell::HEAL:
					robot->leftClick(HEAL);
					break;
				case SummonerSpell::IGNITE:
					robot->leftClick(IGNITE);
					break;
				case SummonerSpell::SMITE:
					robot->leftClick(SMITE);
					break;
				case SummonerSpell::TELEPORT:
					robot->leftClick(TELEPORT);
					break;
				}
			}
		}

		void OutOfGameBot::setRunes(){
			robot->updateScreenBuffer();
			if(robot->isPixelSimilar(CHAMP_SELECT, tolerance)){
				if(robot->isPixelSimilar(CAN_OPEN_RUNES, tolerance)){
					robot->leftClick(EDIT_RUNES_BUTTON);
				}
				//wait for runes panel to open or someone to dodge a new game to be found
				while(!robot->isPixelSimilar(RUNES_PANEL, tolerance) && !robot->isPixelSimilar(ACCEPT_MATCH_BUTTON, tolerance) && robot->isPixelSimilar(CHAMP_SELECT, tolerance)){
					robot->updateScreenBuffer();
				}
				if(robot->isPixelSimilar(RUNES_PANEL, tolerance)){
					Sleep(debugDelay * 2);
					robot->updateScreenBuffer();
					if(robot->isPixelSimilar(CAN_EDIT_RUNE_PAGE, tolerance)){
						robot->leftClick(RUNES_GRID_MODE);
						Sleep(debugDelay);

						setPrimaryTree();
						Sleep(debugDelay);
						//secondary tree icon locations depend on the primary tree, so it needs to be passed to the method
						setSecondaryTree();
						Sleep(debugDelay);

						setKeystone();
						Sleep(debugDelay);
						
						//these really should be refactored into 3 different methods each, but they should work as-is and I don't want to rewrite it right now 4/12/2021
						setPrimaryLesserRune(runes.primaryRune1);
						Sleep(debugDelay);
						setPrimaryLesserRune(runes.primaryRune2);
						Sleep(debugDelay);
						setPrimaryLesserRune(runes.primaryRune3);
						Sleep(debugDelay);
						
						setSecondaryLesserRune(runes.secondaryRune1);
						Sleep(debugDelay);
						setSecondaryLesserRune(runes.secondaryRune2);
						Sleep(debugDelay);

						setShardRune(runes.shardRune1);
						Sleep(debugDelay);
						setShardRune(runes.shardRune2);
						Sleep(debugDelay);
						setShardRune(runes.shardRune3);
						Sleep(debugDelay);

						robot->leftClick(SAVE_RUNES);
						Sleep(debugDelay);
					}
					robot->leftClick(EXIT_RUNES);
					Sleep(debugDelay);
				}
			}
		}

		void OutOfGameBot::lockInChampion(){
			robot->updateScreenBuffer();
			//wait until lock in is possible or until not in champ select anymore
			while(!robot->isPixelSimilar(LOCK_IN, tolerance) && robot->isPixelSimilar(CHAMP_SELECT, tolerance)){
				robot->updateScreenBuffer();
			}
			if (robot->isPixelSimilar(LOCK_IN, tolerance)) {
				robot->leftClick(LOCK_IN.p);
			}
		}

		void OutOfGameBot::setPrimaryTree(){
			switch(runes.primaryTree){
				case RuneTree::PRECISION:
					robot->leftClick(PRECISION_PRIMARY_TREE);
					break;
				case RuneTree::DOMINATION:
					robot->leftClick(DOMINATION_PRIMARY_TREE);
					break;
				case RuneTree::SORCERY:
					robot->leftClick(SORCERY_PRIMARY_TREE);
					break;
				case RuneTree::RESOLVE:
					robot->leftClick(RESOLVE_PRIMARY_TREE);
					break;
				case RuneTree::INSPIRATION:
					robot->leftClick(INSPIRATION_PRIMARY_TREE);
					break;
			}
		}

		void OutOfGameBot::setSecondaryTree(){
			switch(runes.secondaryTree){
				case RuneTree::PRECISION:
					robot->leftClick(SECONDARY_TREE_LOCATION_1);
					break;
				case RuneTree::DOMINATION:
					if(runes.secondaryTree < runes.primaryTree){
						robot->leftClick(SECONDARY_TREE_LOCATION_2);
					}
					else{
						robot->leftClick(SECONDARY_TREE_LOCATION_1);
					}
					break;
				case RuneTree::SORCERY:
					if(runes.secondaryTree < runes.primaryTree){
						robot->leftClick(SECONDARY_TREE_LOCATION_3);
					}
					else{
						robot->leftClick(SECONDARY_TREE_LOCATION_2);
					}
					break;
				case RuneTree::RESOLVE:
					if(runes.secondaryTree < runes.primaryTree){
						robot->leftClick(SECONDARY_TREE_LOCATION_4);
					}
					else{
						robot->leftClick(SECONDARY_TREE_LOCATION_3);
					}
					break;
				case RuneTree::INSPIRATION:
					robot->leftClick(SECONDARY_TREE_LOCATION_4);
					break;
			}
		}

		void OutOfGameBot::setKeystone(){
			switch(runes.keystone){
				case KeystoneRune::PRESS_THE_ATTACK:
				case KeystoneRune::ELECTROCUTE:
					robot->leftClick(FOUR_KEYSTONES_LOCATION_1);
					break;
				case KeystoneRune::LETHAL_TEMPO:
				case KeystoneRune::PREDATOR:
					robot->leftClick(FOUR_KEYSTONES_LOCATION_2);
					break;
				case KeystoneRune::FLEET_FOOTWORK:
				case KeystoneRune::DARK_HARVEST:
					robot->leftClick(FOUR_KEYSTONES_LOCATION_3);
					break;
				case KeystoneRune::CONQUEROR:
				case KeystoneRune::HAIL_OF_BLADES:
					robot->leftClick(FOUR_KEYSTONES_LOCATION_4);
					break;
				case KeystoneRune::SUMMON_AERY:
				case KeystoneRune::GRASP_OF_THE_UNDYING:
				case KeystoneRune::GLACIAL_AUGMENT:
					robot->leftClick(THREE_KEYSTONES_LOCATION_1);
					break;
				case KeystoneRune::ARCANE_COMET:
				case KeystoneRune::AFTERSHOCK:
				case KeystoneRune::UNSEALED_SPELLBOOK:
					robot->leftClick(THREE_KEYSTONES_LOCATION_2);
					break;
				case KeystoneRune::PHASE_RUSH:
				case KeystoneRune::GUARDIAN:
				case KeystoneRune::FIRST_STRIKE:
					robot->leftClick(THREE_KEYSTONES_LOCATION_3);
					break;
			}
		}

		void OutOfGameBot::setPrimaryLesserRune(const LesserRune& lesserRune){
			switch(lesserRune){
				case LesserRune::OVERHEAL:
				case LesserRune::CHEAP_SHOT:
				case LesserRune::NULLIFYING_ORB:
				case LesserRune::DEMOLISH:
				case LesserRune::HEXTECH_FLASH:
					robot->leftClick(PRIMARY_RUNE_SLOT_1_LOCATION_1);
					break;
				case LesserRune::TRIUMPH:
				case LesserRune::TASTE_OF_BLOOD:
				case LesserRune::MANAFLOW_BAND:
				case LesserRune::FONT_OF_LIFE:
				case LesserRune::MAGICAL_FOOTWARE:
					robot->leftClick(PRIMARY_RUNE_SLOT_1_LOCATION_2);
					break;
				case LesserRune::PRESENCE_OF_MIND:
				case LesserRune::SUDDEN_IMPACT:
				case LesserRune::NIMBUS_CLOAK:
				case LesserRune::SHIELD_BASH:
				case LesserRune::PERFECT_TIMING:
					robot->leftClick(PRIMARY_RUNE_SLOT_1_LOCATION_3);
					break;
				case LesserRune::ALACRITY:
				case LesserRune::ZOMBIE_WARD:
				case LesserRune::TRANSCENDENCE:
				case LesserRune::CONDITIONING:
				case LesserRune::FUTURES_MARKET:
					robot->leftClick(PRIMARY_RUNE_SLOT_2_LOCATION_1);
					break;
				case LesserRune::TENACITY:
				case LesserRune::GHOST_PORO:
				case LesserRune::CELERITY:
				case LesserRune::SECOND_WIND:
				case LesserRune::MINION_DEMATERIALIZER:
					robot->leftClick(PRIMARY_RUNE_SLOT_2_LOCATION_2);
					break;
				case LesserRune::BLOODLINE:
				case LesserRune::EYEBALL_COLLECTION:
				case LesserRune::ABSOLUTE_FOCUS:
				case LesserRune::BONE_PLATING:
				case LesserRune::BISCUIT_DELIVERY:
					robot->leftClick(PRIMARY_RUNE_SLOT_2_LOCATION_3);
					break;
				case LesserRune::COUP_DE_GRACE:
				case LesserRune::SORCH:
				case LesserRune::OVERGROWTH:
				case LesserRune::COSMIC_INSIGHT:
					robot->leftClick(PRIMARY_RUNE_SLOT_3_LOCATION_1);
					break;
				case LesserRune::CUT_DOWN:
				case LesserRune::WATERWALKING:
				case LesserRune::REVITALIZE:
				case LesserRune::APPROACH_VELOCITY:
					robot->leftClick(PRIMARY_RUNE_SLOT_3_LOCATION_2);
					break;
				case LesserRune::LAST_STAND:
				case LesserRune::GATHERING_STORM:
				case LesserRune::UNFLINCHING:
				case LesserRune::TIME_WARP_TONIC:
					robot->leftClick(PRIMARY_RUNE_SLOT_3_LOCATION_3);
					break;
				case LesserRune::TREASURE_HUNTER:
					robot->leftClick(PRIMARY_RUNE_SLOT_3_TREASURE_HUNTER);
					break;
				case LesserRune::INGENIUS_HUNTER:
					robot->leftClick(PRIMARY_RUNE_SLOT_3_INGENIUS_HUNTER);
					break;
				case LesserRune::RELENTLESS_HUNTER:
					robot->leftClick(PRIMARY_RUNE_SLOT_3_RELENTLESS_HUNTER);
					break;
				case LesserRune::ULTIMATE_HUNTER:
					robot->leftClick(PRIMARY_RUNE_SLOT_3_ULTIMATE_HUNTER);
					break;
			}
		}

		void OutOfGameBot::setSecondaryLesserRune(const LesserRune& lesserRune){
			switch(lesserRune){
				case LesserRune::OVERHEAL:
				case LesserRune::CHEAP_SHOT:
				case LesserRune::NULLIFYING_ORB:
				case LesserRune::DEMOLISH:
				case LesserRune::HEXTECH_FLASH:
					robot->leftClick(SECONDARY_RUNE_SLOT_1_LOCATION_1);
					break;
				case LesserRune::TRIUMPH:
				case LesserRune::TASTE_OF_BLOOD:
				case LesserRune::MANAFLOW_BAND:
				case LesserRune::FONT_OF_LIFE:
				case LesserRune::MAGICAL_FOOTWARE:
					robot->leftClick(SECONDARY_RUNE_SLOT_1_LOCATION_2);
					break;
				case LesserRune::PRESENCE_OF_MIND:
				case LesserRune::SUDDEN_IMPACT:
				case LesserRune::NIMBUS_CLOAK:
				case LesserRune::SHIELD_BASH:
				case LesserRune::PERFECT_TIMING:
					robot->leftClick(SECONDARY_RUNE_SLOT_1_LOCATION_3);
					break;
				case LesserRune::ALACRITY:
				case LesserRune::ZOMBIE_WARD:
				case LesserRune::TRANSCENDENCE:
				case LesserRune::CONDITIONING:
				case LesserRune::FUTURES_MARKET:
					robot->leftClick(SECONDARY_RUNE_SLOT_2_LOCATION_1);
					break;
				case LesserRune::TENACITY:
				case LesserRune::GHOST_PORO:
				case LesserRune::CELERITY:
				case LesserRune::SECOND_WIND:
				case LesserRune::MINION_DEMATERIALIZER:
					robot->leftClick(SECONDARY_RUNE_SLOT_2_LOCATION_2);
					break;
				case LesserRune::BLOODLINE:
				case LesserRune::EYEBALL_COLLECTION:
				case LesserRune::ABSOLUTE_FOCUS:
				case LesserRune::BONE_PLATING:
				case LesserRune::BISCUIT_DELIVERY:
					robot->leftClick(SECONDARY_RUNE_SLOT_2_LOCATION_3);
					break;
				case LesserRune::COUP_DE_GRACE:
				case LesserRune::SORCH:
				case LesserRune::OVERGROWTH:
				case LesserRune::COSMIC_INSIGHT:
					robot->leftClick(SECONDARY_RUNE_SLOT_3_LOCATION_1);
					break;
				case LesserRune::CUT_DOWN:
				case LesserRune::WATERWALKING:
				case LesserRune::REVITALIZE:
				case LesserRune::APPROACH_VELOCITY:
					robot->leftClick(SECONDARY_RUNE_SLOT_3_LOCATION_2);
					break;
				case LesserRune::LAST_STAND:
				case LesserRune::GATHERING_STORM:
				case LesserRune::UNFLINCHING:
				case LesserRune::TIME_WARP_TONIC:
					robot->leftClick(SECONDARY_RUNE_SLOT_3_LOCATION_3);
					break;
				case LesserRune::TREASURE_HUNTER:
					robot->leftClick(SECONDARY_RUNE_SLOT_3_TREASURE_HUNTER);
					break;
				case LesserRune::INGENIUS_HUNTER:
					robot->leftClick(SECONDARY_RUNE_SLOT_3_INGENIUS_HUNTER);
					break;
				case LesserRune::RELENTLESS_HUNTER:
					robot->leftClick(SECONDARY_RUNE_SLOT_3_RELENTLESS_HUNTER);
					break;
				case LesserRune::ULTIMATE_HUNTER:
					robot->leftClick(SECONDARY_RUNE_SLOT_3_ULTIMATE_HUNTER);
					break;
			}
		}

		void OutOfGameBot::setShardRune(const ShardRuneSlot1& shardRune){
			switch(shardRune){
				case ShardRuneSlot1::ADAPTIVE_FORCE:
					robot->leftClick(SLOT_1_ADAPTIVE_FORCE);
					break;
				case ShardRuneSlot1::ATTACK_SPEED:
					robot->leftClick(SLOT_1_ATTACK_SPEED);
					break;
				case ShardRuneSlot1::ABILITY_HASTE:
					robot->leftClick(SLOT_1_ABILITY_HASTE);
					break;
			}
		}

		void OutOfGameBot::setShardRune(const ShardRuneSlot2& shardRune){
			switch(shardRune){
				case ShardRuneSlot2::ADAPTIVE_FORCE:
					robot->leftClick(SLOT_2_ADAPTIVE_FORCE);
					break;
				case ShardRuneSlot2::ARMOR:
					robot->leftClick(SLOT_2_ARMOR);
					break;
				case ShardRuneSlot2::MAGIC_RESIST:
					robot->leftClick(SLOT_2_MAGIC_RESIST);
					break;
			}
		}

		void OutOfGameBot::setShardRune(const ShardRuneSlot3& shardRune){
			switch(shardRune){
				case ShardRuneSlot3::HEALTH:
					robot->leftClick(SLOT_3_HEALTH);
					break;
				case ShardRuneSlot3::ARMOR:
					robot->leftClick(SLOT_3_ARMOR);
					break;
				case ShardRuneSlot3::MAGIC_RESIST:
					robot->leftClick(SLOT_3_MAGIC_RESIST);
					break;
			}
		}