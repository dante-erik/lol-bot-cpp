#pragma once
enum class SummonerSpell {
	HEAL, GHOST, FLASH, TELEPORT, BARRIER, EXHAUST, SMITE, IGNITE, CLEANSE
};

struct SummonerSpells {
	SummonerSpell left;
	SummonerSpell right;
};

enum class Role {
	TOP, JUNGLE, MID, ADC, SUPPORT
};

enum class ChampSelectType {
	INTRO_BOTS, BEGINNER_BOTS, INTERMEDIATE_BOTS, BLIND_NORMS, DRAFT_NORMS, RANKED_SOLO_DUO, RANKED_FLEX
};

enum class RuneTree {
	PRECISION, DOMINATION, SORCERY, RESOLVE, INSPIRATION
};

enum class KeystoneRune {
	//Precision tree
	PRESS_THE_ATTACK, LETHAL_TEMPO, FLEET_FOOTWORK, CONQUEROR,
	//Domination tree
	ELECTROCUTE, PREDATOR, DARK_HARVEST, HAIL_OF_BLADES,
	//Sorcery tree
	SUMMON_AERY, ARCANE_COMET, PHASE_RUSH,
	//Resolve tree
	GRASP_OF_THE_UNDYING, AFTERSHOCK, GUARDIAN,
	//Inspiration tree
	GLACIAL_AUGMENT, UNSEALED_SPELLBOOK, FIRST_STRIKE
};

enum class LesserRune {
	//slot 1

	//Precision tree
	OVERHEAL, TRIUMPH, PRESENCE_OF_MIND,
	//Domination tree
	CHEAP_SHOT, TASTE_OF_BLOOD, SUDDEN_IMPACT,
	//Sorcery tree
	NULLIFYING_ORB, MANAFLOW_BAND, NIMBUS_CLOAK,
	//Resolve tree
	DEMOLISH, FONT_OF_LIFE, SHIELD_BASH,
	//Inspiration tree
	HEXTECH_FLASH, MAGICAL_FOOTWARE, PERFECT_TIMING,

	//slot 2

	//Precision tree
	ALACRITY, TENACITY, BLOODLINE,
	//Domination tree
	ZOMBIE_WARD, GHOST_PORO, EYEBALL_COLLECTION,
	//Sorcery tree
	TRANSCENDENCE, CELERITY, ABSOLUTE_FOCUS,
	//Resolve tree
	CONDITIONING, SECOND_WIND, BONE_PLATING,
	//Inspiration tree
	FUTURES_MARKET, MINION_DEMATERIALIZER, BISCUIT_DELIVERY,

	//slot 3

	//Precision tree
	COUP_DE_GRACE, CUT_DOWN, LAST_STAND,
	//Domination tree
	TREASURE_HUNTER, INGENIUS_HUNTER, RELENTLESS_HUNTER, ULTIMATE_HUNTER,
	//Sorcery tree
	SORCH, WATERWALKING, GATHERING_STORM,
	//Resolve tree
	OVERGROWTH, REVITALIZE, UNFLINCHING,
	//Inspiration tree
	COSMIC_INSIGHT, APPROACH_VELOCITY, TIME_WARP_TONIC
};

enum class ShardRuneSlot1 {
	ADAPTIVE_FORCE, ATTACK_SPEED, ABILITY_HASTE
};

enum class ShardRuneSlot2 {
	ADAPTIVE_FORCE, ARMOR, MAGIC_RESIST
};

enum class ShardRuneSlot3 {
	HEALTH, ARMOR, MAGIC_RESIST
};

struct Runes {
	//Trees
	RuneTree primaryTree, secondaryTree;
	//Primary tree keystone
	KeystoneRune keystone;
	//Primary tree runes
	LesserRune primaryRune1, primaryRune2, primaryRune3;
	//Secondary tree runes
	LesserRune secondaryRune1, secondaryRune2;
	//Stat shard runes
	ShardRuneSlot1 shardRune1;
	ShardRuneSlot2 shardRune2;
	ShardRuneSlot3 shardRune3;
};