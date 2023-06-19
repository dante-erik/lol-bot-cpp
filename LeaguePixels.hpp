#pragma once

#include "Pixel.hpp"

//if only an {x, y} point is given without an RGB, the pixel is never used for comparisons

constexpr Pixel GAME_HUD{ {1331, 1060}, 138, 121, 74 };
constexpr Pixel ALLY_BASE{ {1666, 1055} };
constexpr Pixel ENEMY_NEXUS{ {1882, 844} };
constexpr Pixel FIND_MATCH{ {847, 831}, 20, 62, 85 };
constexpr Pixel FIND_MATCH_HIGHLIGHTED{ {847, 831}, 18, 89, 110 };
constexpr Pixel ACCEPT_MATCH{ {961, 706}, 30, 37, 42 };
constexpr Pixel ACCEPT_MATCH_HIGHLIGHTED{ {961, 706}, 26, 46, 56 };
constexpr Pixel CHAMPION_SELECT{ {588, 198}, 67, 52, 19 };
constexpr Pixel HONOR_TEAMMATE{ {958, 805}, 68, 72, 66 };
constexpr Pixel PLAY_AGAIN{ {846, 830}, 20, 69, 92 };
constexpr Pixel PLAY_AGAIN_HIGHLIGHTED{ {846, 830}, 18, 93, 114 };
constexpr Pixel CHAMPION_REWARD{ {961, 835 }, 57, 59, 60};
constexpr Pixel CHAMPION_LOCKED_IN{ {1156, 838}, 205, 190, 145 };
constexpr Pixel TOP_LEFT_CHAMPION_ICON{ {706, 326} };
constexpr Pixel LOCK_IN{ {959, 766} };
//selects middle of the three champion options
constexpr Pixel CHAMPION_REWARD_SELECT_BUTTON{ {943, 547} };
constexpr Pixel CHAMPION_REWARD_OKAY_BUTTON{ {959, 831} };
//this encompasses rewards from leveling up, daily bonus, missions, and quests
constexpr Pixel GENERIC_REWARD{ {961, 835}, 139, 132, 107 };
constexpr Pixel GENERIC_REWARD_HIGHLIGHTED{ {961, 835}, 141, 134, 107 };
constexpr Pixel PROBLEM_SELECTING_YOUR_CHAMPION{ {961, 549}, 157, 141, 102 };
constexpr Pixel PROBLEM_SELECTING_YOUR_CHAMPION_HIGHLIGHTED{ {961, 549}, 206, 192, 167 };
constexpr Pixel CHALLENGE_TIER_UP{ {1069, 727}, 240, 230, 210 };
constexpr Pixel VERIFY_EMAIL{ {1211, 251}, 205, 190, 145 };
constexpr Pixel SKIP_WAITING_FOR_STATS{ {840, 748}, 194, 190, 145 };
constexpr Pixel SKILL_POINT{ {} };
constexpr Pixel LEFT_SUMMONER_SPELL{ {} };
constexpr Pixel RIGHT_SUMMONER_SPELL{ {} };
constexpr Pixel FLASH_SUMMONER_SPELL{ {} };
constexpr Pixel HEAL_SUMMONER_SPELL{ {} };
constexpr Pixel BAN_PHASE{ {} };
constexpr Pixel NO_BAN{ {} };
constexpr Pixel LOCK_IN_BAN{ {} };
constexpr Pixel ABLE_TO_PICK_CHAMPION{ {} };
constexpr Pixel CHAMPION_SELECT_SEARCH_BOX{ {} };
constexpr Pixel LOCK_IN_CHAMPION{ {} };
constexpr Pixel RIOT_RECOMMENDED_RUNES_AND_SUMMONER_SPELLS{ {} };
constexpr Pixel ALLOW_SUMMONER_SPELL_CHANGES{ {} };
constexpr Pixel LEFT_RECOMMENDED_RUNES_AND_SUMMONER_SPELLS_OPTION{ {} };