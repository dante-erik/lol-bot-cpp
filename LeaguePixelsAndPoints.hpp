#pragma once
#include "Pixel.hpp"

//Pixels
constexpr Pixel CLIENT_BORDER{ {320, 160}, 30, 40, 45 };
constexpr Pixel IN_GAME_HUD{ {1641, 1030}, 129, 106, 72 };
constexpr Pixel SHOP_BRIGHT{ {1141, 1070}, 177, 157, 85 };
constexpr Pixel EMPTY_ITEM_SLOT_1{ {1130, 946}, 0, 0, 0 };
constexpr Pixel EMPTY_ITEM_SLOT_2{ {1179, 946}, 0, 0, 0 };
constexpr Pixel EMPTY_ITEM_SLOT_3{ {1228, 946}, 0, 0, 0 };
constexpr Pixel EMPTY_ITEM_SLOT_4{ {1130, 993}, 0, 0, 0 };
constexpr Pixel EMPTY_ITEM_SLOT_5{ {1179, 993}, 0, 0, 0 };
constexpr Pixel EMPTY_ITEM_SLOT_6{ {1228, 993}, 0, 0, 0 };
constexpr Pixel CAN_LEVEL_UP_ABILITY{ {794, 876}, 255, 247, 153 };
constexpr Pixel FULL_HEALTH{ {1094, 1030}, 51, 210, 58 };
constexpr Pixel ZERO_HEALTH{ {682, 1030}, 16, 89, 24 };
constexpr Pixel FULL_MANA{ {1094, 1064}, 88, 171, 250 };
constexpr Pixel ZERO_MANA{ {682, 1064}, 0, 70, 150 };
constexpr Pixel Q_USABLE{ {730, 974}, 198, 162, 99 };
constexpr Pixel W_USABLE{ {797, 973}, 198, 162, 99 };
constexpr Pixel E_USABLE{ {} };
constexpr Pixel R_USABLE{ {} };
//POINTs
//only on 1920x1080 screens, but the rest of the bot only runs when
//the screen is 1920x1080 so it'll be fine
constexpr POINT CENTER_OF_SCREEN{ 960, 540 };