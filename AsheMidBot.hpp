//#pragma once
//#include <iostream>
//#include "InGameBot.cpp"
//#include "OutOfGameBot.cpp"
//#include "LeaguePointsAndPixels.hpp"
//
//class AsheMidBot : public InGameBot, OutOfGameBot {
//private:
//	//Ashe Pixel objects
//	Pixel ASHE_ALIVE{ {} };
//	Pixel ASHE_DEAD{ {} };
//	Pixel ASHE_Q_USABLE{ {} };
//	Pixel ASHE_W_USABLE{ {} };
//	Pixel ASHE_R_USABLE{ {} };
//
//	//Ashe POINT objects
//	POINT ASHE_W_CAST_LOCATION{ };
//	POINT ASHE_R_CAST_LOCATION{ };
//
//	Robot robot;
//	unsigned short tolerance = 0;
//	ChampSelectType champSelectType{ ChampSelectType::INTRO_BOTS};
//	std::string championName = "Ashe";
//	std::string championToBan = "";
//	Role role{ Role::MID };
//	Runes runes{
//		RuneTree::PRECISION,
//		RuneTree::INSPIRATION,
//
//		KeystoneRune::LETHAL_TEMPO,
//
//		LesserRune::PRESENCE_OF_MIND,
//		LesserRune::BLOODLINE,
//		LesserRune::COUP_DE_GRACE,
//		
//		LesserRune::FUTURES_MARKET,
//		LesserRune::APPROACH_VELOCITY,
//
//		ShardRuneSlot1::ATTACK_SPEED,
//		ShardRuneSlot2::ADAPTIVE_FORCE,
//		ShardRuneSlot3::ARMOR
//	};
//	SummonerSpells summonerSpells{
//		SummonerSpell::TELEPORT,
//		SummonerSpell::HEAL
//	};
//	unsigned char championLevel = 1;
//	std::string abilityMaxingOrder = "qwqwqrqwqwrweeeree";
//
//public:
//	AsheMidBot() {}
//	AsheMidBot(unsigned short tolerance) : tolerance{ tolerance } {}
//
//	void run() {
//		while(true){
//			robot.updateScreenBuffer();
//			//if in game, inGameActions() else outOfGameActions()
//			if (robot.isPixelSimilar(IN_GAME_HUD), tolerance) {
//				inGameActions();
//			}
//			else {
//				outOfGameActions(champSelectType, championName, championToBan, role, runes, summonerSpells);
//			}
//		}
//	}
//
//	void inGameActions() {
//		if (newGame) {
//			startOfNewGameActions();
//			newGame = false;
//		}
//
//		setHealth();
//		if (health < 15.0 && robot.isPixelSimilar(ASHE_ALIVE, tolerance)) {
//			useHealIfUsable();
//			returnToBase();
//			buyItems();
//			waitInBaseForMaxHealth();
//			useTeleportIfUsable();
//		}
//		else if (robot.isPixelSimilar(ASHE_DEAD, tolerance)) {
//			buyItems();
//			waitUntilAlive();
//			useTeleportIfUsable();
//		}
//		else {
//			attack();
//		}
//
//		levelUpAbility(abilityMaxingOrder);
//	}
//
//	void startOfNewGameActions() {
//		championLevel = 1;
//	}
//
//	void returnToBase() {
//		//if the blue val there is less than 100, tower is still up, if its greater, tower is gone
//		//its a point instead of pixel cuz of tower plating changing the pixel :(
//		if(robot.getBlue(ALLY_MID_TOWER_1) < 100) {
//			//run to recall spot
//			while(!robot.isPixelSimilar(RECALL_MID_LOCATION_1, tolerance) && robot.isPixelSimilar(ASHE_ALIVE, tolerance)){
//				robot.rightClick(RECALL_MID_LOCATION_1.p);
//				robot.updateScreenBuffer();
//				Sleep(100);
//			}
//			//once youve made it to recall spot, recall until the shop is available
//			while(robot.isPixelSimilar(SHOP_DARK, tolerance)){
//				recall();
//				robot.updateScreenBuffer();
//				Sleep(100);
//			}
//		}
//		else if(robot.isPixelSimilar(ALLY_MID_TOWER_2, tolerance)){
//			while(!robot.isPixelSimilar(RECALL_MID_LOCATION_2, tolerance) && robot.isPixelSimilar(ASHE_ALIVE, tolerance)){
//				robot.rightClick(RECALL_MID_LOCATION_2.p);
//				robot.updateScreenBuffer();
//			}
//			while(robot.isPixelSimilar(SHOP_DARK, tolerance)){
//				recall();
//				robot.updateScreenBuffer();
//			}
//		}
//		else{
//			while(robot.isPixelSimilar(SHOP_DARK, tolerance)){
//				robot.rightClick(BLUE_BASE);
//				robot.updateScreenBuffer();
//			}
//		}
//	}
//
//	void attack() {
//		castAbilities();
//		if(isTowerAlive(MID1)){
//			attackClick(ENEMY_MID_TOWER_1_ATTACK_LOCATION);
//		}
//		else if(isTowerAlive(MID2)){
//			attackClick(ENEMY_MID_TOWER_2_ATTACK_LOCATION);
//		}
//		else if(isTowerAlive(MID3)){
//			attackClick(ENEMY_MID_TOWER_3_ATTACK_LOCATION);
//		}
//		else if(robot.isPixelSimilar(ENEMY_NEXUS_TOWER_LEFT, tolerance) || robot.isPixelSimilar(ENEMY_NEXUS_TOWER_RIGHT, tolerance) {
//			attackClick(ENEMY_NEXUS_TOWER_ATTACK_LOCATION);
//		}
//		else {
//			attackClick(ENEMY_NEXUS);
//		}
//	}
//
//	void castAbilities(){
//		//if Q is fully stacked, its guarenteed you're in combat, so you should use other abilities
//		//use W and R first because they cancel auto attacks so Q time would be wasted if it's cast first
//		if(robot.isPixelSimilar(ASHE_Q_USABLE, tolerance) && health < 98.0){
//			setMana();
//			if(mana > 10.0 && robot.isPixelSimilar(ASHE_W_USABLE, tolerance)){
//				castAbility('w', ASHE_W_CAST_LOCATION);
//				//250 ms cast time
//				//wait for cast time to end before moving cursor
//				Sleep(248);
//				//this operation probably takes at least 2 ms
//				robot.updateScreenBuffer();
//				setMana();
//			}
//			if(mana > 10.0 && robot.isPixelSimilar(ASHE_R_USABLE, tolerance)){
//				castAbility('r', ASHE_R_CAST_LOCATION);
//				//250 ms cast time
//				Sleep(248);
//				robot.updateScreenBuffer();
//				setMana();
//			}
//			if(mana > 10.0){
//				//no cast time or location on Q, self-buff ability
//				robot.keyClick('q');
//			}
//		}
//	}
//
//	void castAbility(std::string& ability, POINT location) {
//		setCursorPos(location.x, location.y);
//		robot.keyClick(ability);
//	}
//
//	void useHealIfUsable() {
//		if (robot.isPixelSimilar(HEAL_RIGHT_USABLE, tolerance)) {
//			robot.keyClick('f');
//		}
//	}
//
//	void useTeleportIfUsable(){
//		if(robot.isPixelSimilar(TELEPORT_LEFT_USABLE, tolerance){
//			if(robot.isPixelSimilar(ALLY_MID_TOWER_1, tolerance)){
//				useTeleport(ALLY_MID_TOWER_1);
//				//tp takes 4 secs to channel
//				Sleep(4050);
//			}
//			else if(robot.isPixelSimilar(ALLY_MID_TOWER_2, tolerance)){
//				useTeleport(ALLY_MID_TOWER_2.p);
//				Sleep(4050);
//			}
//			else if(robot.isPixelSimilar(ALLY_MID_TOWER_3, tolerance)){
//				useTeleport(ALLY_MID_TOWER_3.p);
//				Sleep(4050);
//			}
//		}
//	}
//
//	void useTeleport(POINT p);
//
//	void levelUpAbility(const std::string& abilityMaxingOrder);
//};