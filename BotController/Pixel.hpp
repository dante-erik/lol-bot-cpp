#pragma once

#include <Windows.h>

struct Pixel
{
	LONG x;
	LONG y;
    BYTE r;
    BYTE g;
    BYTE b;
    RGBQUAD color{ b, g, r, 0 };
};

namespace GamePixel {
    //these pixels are used for their rgb color AND x and y values

    //in game
    //bgr
    constexpr Pixel redSideFogOfWar{ 1816, 908, 52, 55, 40 };
    constexpr Pixel HUD{ 1329, 1076, 87, 80, 49 };
    constexpr Pixel unattachedW{ 826, 963, 108, 82, 214 };
    constexpr Pixel shopBright{ 1283, 1063, 13, 69, 67 };
    constexpr Pixel emptyItemSlot2{ 1198, 968, 5, 13, 11 };
    constexpr Pixel emptyItemSlot3{ 1246, 967, 5, 13, 11 };
    constexpr Pixel emptyItemSlot5{ 1151, 1015, 5, 13, 11 };
    constexpr Pixel emptyItemSlot6{ 1200, 1015, 5, 13, 11 };
    constexpr Pixel emptyItemSlot7{ 1249, 1015, 5, 13, 11 };
    constexpr Pixel forbiddenIdolSlot2{ 1196, 965, 207, 76, 186 };
    constexpr Pixel forbiddenIdolSlot3{ 1245, 964, 207, 76, 186 };
    constexpr Pixel forbiddenIdolSlot5{ 1148, 1011, 247, 97, 222 };
    constexpr Pixel forbiddenIdolSlot6{ 1196, 1011, 247, 97, 222 };
    constexpr Pixel bandleglassMirrorSlot7{ 1248, 1016, 74, 205, 237 };
    constexpr Pixel shopDark{ 1289, 1063, 22, 28, 30 };
    constexpr Pixel yuumiLowHP{ 966, 1038, 1, 13, 7 };
    constexpr Pixel attachedAllyReallyLowHP{ 1878, 783, 19, 19, 19 };
    constexpr Pixel attachedW{ 827, 967, 217, 159, 194 };
    constexpr Pixel attachedAllyLowHP{ 1900, 783, 19, 19, 19 };
    constexpr Pixel canLevelUpQ{ 758, 915, 255, 241, 87 };
    constexpr Pixel canLevelUpW{ 824, 915, 251, 237, 92 };
    constexpr Pixel canLevelUpE{ 891, 915, 255, 241, 87 };
    constexpr Pixel canLevelUpR{ 957, 915, 255, 241, 87 };

    //in client
    constexpr Pixel findMatchButton{ 855, 846, 157, 191, 191 };
    constexpr Pixel acceptMatchButton{ 960, 718, 153, 187, 187 };
    constexpr Pixel highlightedAcceptMatchButton{ 960, 718, 195, 240, 241 };
    constexpr Pixel champSelect{ 1397, 847, 160, 155, 140 };
    constexpr Pixel yuumiChampSelectIcon{ 702, 325, 117, 57, 104 };
    constexpr Pixel healSS{ 1011, 838, 77, 133, 50 };
    constexpr Pixel barrierSS{ 1056, 844, 183, 172, 60 };
    constexpr Pixel editRunesIcon{ 756, 844, 205, 190, 145 };
    constexpr Pixel runesRowDisplay{ 468, 827, 66, 67, 61 };
    constexpr Pixel runePageLock{ 514, 404, 170, 170, 170 };
    constexpr Pixel mainRune1Unselected{ 491, 498, 30, 35, 40 };
    constexpr Pixel guardian{ 709, 496, 66, 147, 5 };
    constexpr Pixel runesPage{ 1488, 421, 70, 55, 20 };
    constexpr Pixel mainRune2Unselected{ 490, 594, 30, 35, 40 };
    constexpr Pixel fontOfLife{ 644, 595, 27, 191, 78 };
    constexpr Pixel mainRune3Unselected{ 490, 682, 30, 35, 40 };
    constexpr Pixel bonePlating{ 711, 677, 131, 132, 65 };
    constexpr Pixel mainRune4Unselected{ 491, 768, 30, 35, 40 };
    constexpr Pixel revitalize{ 644, 770, 229, 195, 34 };
    constexpr Pixel secondaryRune1Unselected{ 815, 497, 30, 35, 40 };
    constexpr Pixel absoluteFocus{ 1032, 547, 234, 135, 252 };
    constexpr Pixel secondaryRune2Unselected{ 814, 593, 30, 35, 40 };
    constexpr Pixel gatheringStorm{ 1034, 621, 57, 90, 255 };
    constexpr Pixel statRune1Unselected{ 815, 681, 30, 35, 40 };
    constexpr Pixel adaptiveForce1{ 903, 681, 132, 69, 255 };
    constexpr Pixel statRune2Unselected{ 815, 724, 30, 35, 40 };
    constexpr Pixel adaptiveForce2{ 903, 726, 132, 69, 255 };
    constexpr Pixel statRune3Unselected{ 815, 769, 30, 35, 40 };
    constexpr Pixel armor{ 969, 769, 247, 113, 90 };
    constexpr Pixel saveRunes{ 828, 292, 205, 190, 145 };
    //constexpr Pixel honorTeammate {};
    //constexpr Pixel playAgainButton {};
    //constexpr Pixel levelUp {};
    //constexpr Pixel dailyReward {};
    //constexpr Pixel championReward {};
    //constexpr Pixel questReward {};

    //these pixels are only used or their X and Y values
    
    //in game
    constexpr Pixel blueBaseOnMinimap{ 1660, 1062 };
    constexpr Pixel redBaseOnMinimap{ 1903, 820 };
    constexpr Pixel teammateIconAboveMinimap{ 1888, 761 };
    constexpr Pixel yuumiManaBar{ 938, 1059 };
    constexpr Pixel yuumiE{ 892, 980 };

    //in client
    constexpr Pixel champSearchBox{ 1145, 266 };
    constexpr Pixel lockInButton{ 990, 769 };
    constexpr Pixel lobbyChatBox{ 470, 843 };
    constexpr Pixel healSSInPanel{ 950, 700 };
    constexpr Pixel barrierSSInPanel{ 950, 760 };
    constexpr Pixel runesGridDisplay{ 505, 838 };
    constexpr Pixel runesDropDown{ 608, 292 };
    constexpr Pixel addNewRunePage{ 648, 337 };
    constexpr Pixel runesTopPage{ 646, 375 };
    constexpr Pixel greenRuneTree{ 684, 379 };
    constexpr Pixel blueRuneTree{ 994, 378 };
    constexpr Pixel exitRunes{ 1491, 241 };
    //constexpr Pixel selectChampionReward {};

    //other
    constexpr Pixel arbitraryNearCenter{ 873, 473 };
    constexpr Pixel mouseOffLOLClient{ 1638, 487 };
}