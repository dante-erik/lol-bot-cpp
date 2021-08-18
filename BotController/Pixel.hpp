#pragma once

#include <Windows.h>

struct Pixel
{
	LONG x;
	LONG y;
	RGBQUAD color;
};

namespace GamePixel {
    //these pixels are used for their color and x and y values
    //the guy who made RGBQUAD made it BGRr format instead of RGBr
    constexpr Pixel redSideFogOfWar{ 1816, 908, {40, 55, 52} };
    constexpr Pixel HUD{ 1329, 1076, {49, 80, 87} };
    constexpr Pixel unattachedW{ 826, 963, {214, 82, 108} };
    constexpr Pixel shopBright{ 1283, 1063, {67, 69, 13} };
    constexpr Pixel emptyItemSlot2{ 1198, 968, {11, 13, 5} };
    constexpr Pixel emptyItemSlot3{ 1246, 967, {11, 13, 5} };
    constexpr Pixel emptyItemSlot5{ 1151, 1015, {11, 13, 5} };
    constexpr Pixel emptyItemSlot6{ 1200, 1015, {11, 13, 5} };
    constexpr Pixel emptyItemSlot7{ 1249, 1015, {11, 13, 5} };
    constexpr Pixel forbiddenIdolSlot2{ 1196, 965, {186, 76, 207} };
    constexpr Pixel forbiddenIdolSlot3{ 1245, 964, {186, 76, 207} };
    constexpr Pixel forbiddenIdolSlot5{ 1148, 1011, {222, 97, 247} };
    constexpr Pixel forbiddenIdolSlot6{ 1196, 1011, {222, 97, 247} };
    constexpr Pixel bandleglassMirrorSlot7{ 1248, 1016, {237, 205, 74} };
    constexpr Pixel shopDark{ 1289, 1063, {30, 28, 22} };
    constexpr Pixel yuumiLowHP{ 966, 1038, {7, 13, 1} };
    constexpr Pixel attachedAllyReallyLowHP{ 1878, 783, {19, 19, 19} };
    constexpr Pixel attachedW{ 827, 967, {194, 159, 217} };
    constexpr Pixel attachedAllyLowHP{ 1900, 783, {19, 19, 19} };
    constexpr Pixel canLevelUpQ{ 758, 915, {87, 241, 255} };
    constexpr Pixel canLevelUpW{ 824, 915, {92, 237, 251} };
    constexpr Pixel canLevelUpE{ 891, 915, {87, 241, 255} };
    constexpr Pixel canLevelUpR{ 957, 915, {87, 241, 255} };
    constexpr Pixel findMatchButton{ 855, 846, {191, 191, 157} };
    constexpr Pixel acceptMatchButton{ 960, 718, {187, 187, 153} };
    constexpr Pixel highlightedAcceptMatchButton{ 960, 718, {241, 240, 195} };
    constexpr Pixel champSelect{ 1397, 847, {140, 155, 160} };
    constexpr Pixel yuumiChampSelectIcon{ 702, 325, {104, 57, 117} };
    constexpr Pixel healSS{ 1011, 838, {58, 144, 85} };
    constexpr Pixel barrierSS{ 1056, 844, {52, 166, 182} };
    constexpr Pixel editRunesIcon{ 757, 844, {145, 189, 204} };
    constexpr Pixel runesRowDisplay{ 468, 893, {55, 65, 64} };
    constexpr Pixel runePageLock{ 514, 404, {170, 170, 170} };
    constexpr Pixel mainRune1Unselected{ 491, 498, {40, 35, 30} };
    constexpr Pixel guardian{ 709, 496, {6, 146, 66} };
    constexpr Pixel runesPage{ 1488, 421, {20, 55, 70} };
    constexpr Pixel mainRune2Unselected{ 490, 594, {40, 35, 30} };
    constexpr Pixel fontOfLife{ 644, 595, {78, 191, 27} };
    constexpr Pixel mainRune3Unselected{ 490, 682, {40, 35, 30} };
    constexpr Pixel bonePlating{ 711, 677, {65, 132, 131} };
    constexpr Pixel mainRune4Unselected{ 491, 768, {40, 35, 30} };
    constexpr Pixel revitalize{ 644, 770, {26, 160, 199} };
    constexpr Pixel secondaryRune1Unselected{ 815, 497, {40, 35, 30} };
    constexpr Pixel absoluteFocus{ 1032, 547, {252, 135, 234} };
    constexpr Pixel secondaryRune2Unselected{ 814, 593, {40, 35, 30} };
    constexpr Pixel gatheringStorm{ 1034, 621, {255, 171, 92} };
    constexpr Pixel statRune1Unselected{ 815, 681, {40, 35, 30} };
    constexpr Pixel adaptiveForce1{ 903, 681, {255, 69, 132} };
    constexpr Pixel statRune2Unselected{ 815, 724, {40, 35, 30} };
    constexpr Pixel adaptiveForce2{ 903, 726, {255, 69, 132} };
    constexpr Pixel statRune3Unselected{ 815, 769, {40, 35, 30} };
    constexpr Pixel armor{ 969, 769, {89, 112, 244} };
    constexpr Pixel saveRunes{ 828, 292, {145, 190, 205} };
    //constexpr Pixel honorTeammate {};
    //constexpr Pixel playAgainButton {};
    //constexpr Pixel levelUp {};
    //constexpr Pixel dailyReward {};
    //constexpr Pixel championReward {};
    //constexpr Pixel questReward {};

    //these pixels are only used or their X and Y values
    constexpr Pixel blueBaseOnMinimap{ 1660, 1062, {0, 0, 0} };
    constexpr Pixel redBaseOnMinimap{ 1903, 820, {0, 0, 0} };
    constexpr Pixel teammateIconAboveMinimap{ 1888, 761, {0, 0, 0} };
    constexpr Pixel yuumiManaBar{ 938, 1059, {0, 0, 0} };
    constexpr Pixel yuumiE{ 892, 980, {0, 0, 0} };
    constexpr Pixel arbitraryNearCenter{ 873, 473, {0, 0, 0} };
    constexpr Pixel mouseOffLOLClient{ 1638, 487, {0, 0, 0} };
    constexpr Pixel champSearchBox{ 1145, 266, {0, 0, 0} };
    constexpr Pixel lockInButton{ 990, 769, {0, 0, 0} };
    constexpr Pixel lobbyChatBox{ 470, 843, {0, 0, 0} };
    constexpr Pixel healSSInPanel{ 950, 700, {0, 0, 0} };
    constexpr Pixel barrierSSInPanel{ 950, 760, {0, 0, 0} };
    constexpr Pixel runesGridDisplay{ 505, 838, {0, 0, 0} };
    constexpr Pixel runesDropDown{ 608, 292, {0, 0, 0} };
    constexpr Pixel addNewRunePage{ 648, 337, {0, 0, 0} };
    constexpr Pixel runesTopPage{ 646, 375, {0, 0, 0} };
    constexpr Pixel greenRuneTree{ 684, 379, {0, 0, 0} };
    constexpr Pixel blueRuneTree{ 994, 378, {0, 0, 0} };
    constexpr Pixel exitRunes{ 1491, 241, {0, 0, 0} };
    //constexpr Pixel selectChampionReward {};
}