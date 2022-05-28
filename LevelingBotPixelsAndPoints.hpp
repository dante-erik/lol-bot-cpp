#pragma once
#include "LeaguePixelsAndPoints.hpp"

//Pixels
constexpr Pixel CLIENT_BORDER{ {320, 160}, 30, 40, 45 };
constexpr Pixel FOW_ALLY_MID_TOWER_1{ {1762, 958}, 52, 55, 40 };
constexpr Pixel FOW_ALLY_MID_TOWER_2{ {1739, 980}, 52, 55, 40 };
constexpr Pixel FOW_ALLY_MID_TOWER_3{ {1729, 991}, 52, 55, 40 };
constexpr Pixel DORANS_SHIELD_ITEM_SLOT_1{ {1152, 954}, 106, 66, 36 };
constexpr Pixel FOW_MID_TOWER_1_A{ {1813, 907}, 52, 55, 40 };
constexpr Pixel FOW_MID_TOWER_1_B{ {1828, 901}, 52, 55, 40 };
constexpr Pixel FOW_MID_TOWER_2{ {1854, 880}, 36, 49, 52 };
constexpr Pixel FOW_MID_TOWER_3{ {1869, 854}, 41, 54, 57 };
constexpr Pixel FOW_NEXUS_TOWERS{ {1902, 834},	 41, 54, 56 };
//POINTs
constexpr POINT SAFE_RECALL_MID_TOWER_1{1748, 973};
constexpr POINT SAFE_RECALL_MID_TOWER_2{1725, 997};
constexpr POINT SAFE_RECALL_MID_TOWER_3{1709, 1022};
constexpr POINT SAFE_ATTACK_NEXUS{1876, 845};
constexpr POINT SAFE_ATTACK_MID_TOWER_1_A{1777, 948};
constexpr POINT SAFE_ATTACK_MID_TOWER_1_B{1790, 936};
constexpr POINT SAFE_ATTACK_MID_TOWER_2{1813, 915};
constexpr POINT SAFE_ATTACK_MID_TOWER_3{1830, 895};
constexpr POINT SAFE_ATTACK_NEXUS_TOWERS{1843, 871};
constexpr POINT ABILITY_ATTACK_LOCATION{1010, 366};
//ally base will always be blue side in intro-bots
constexpr POINT ALLY_BASE{ 1668, 1053 };