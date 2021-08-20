#include <iostream>
#include <windows.h>
#include "Robot.hpp"
#include "Pixel.hpp"

int main()
{
	//performs pixel checks and mouse actions
	Robot robot = Robot();

	//how exact the pixel color's RGBs need to be
	BYTE tolerance = 0;

	//in milliseconds
	DWORD clickSpeed = 70;
	DWORD typeSpeed = 20;

	//checking for new champ selects to avoid repeating actions
	//set to false after finishing all champ select specific actions in a new champ select state
	//set to true after accepting a new match
	BOOL newChampSelect = true;

	//avoid repeating starting actions in game
	//set to false at the end of newGame if actions
	//set to true after accepting a new match
	BOOL newGame = true;

	//avoid repeating the buy action until the base is left and re-entered
	BOOL ableToBuyItems = true;

	//coordinates for ally base set each game in newGame section
	LONG baseX, baseY;

	//while (true) {
		//std::cout << (int)robot.getRed(GamePixel::findMatchButton.x, GamePixel::findMatchButton.y) << std::endl;
		//std::cout << (int)robot.getGreen(GamePixel::findMatchButton.x, GamePixel::findMatchButton.y) << std::endl;
		//std::cout << (int)robot.getBlue(GamePixel::findMatchButton.x, GamePixel::findMatchButton.y) << std::endl;
		//std::cout << std::endl;
		//std::cout << robot.getPixelDiff(GamePixel::findMatchButton.x, GamePixel::findMatchButton.y, GamePixel::findMatchButton.color, (BYTE)0);
		//robot.updatePixels();
	//}

	//while (true) {
	//	std::cout << "test msg" << std::endl;
	//	Sleep(10);
	//}

	/*while (true) {
		std::cout << "r: " << (int)GamePixel::redSideFogOfWar.r << std::endl;
		std::cout << "g: " << (int)GamePixel::redSideFogOfWar.g << std::endl;
		std::cout << "b: " << (int)GamePixel::redSideFogOfWar.b << std::endl;
		std::cout << "color r: " << (int)GamePixel::redSideFogOfWar.color.rgbRed << std::endl;
		std::cout << "color g: " << (int)GamePixel::redSideFogOfWar.color.rgbGreen << std::endl;
		std::cout << "color b: " << (int)GamePixel::redSideFogOfWar.color.rgbBlue << std::endl;
		Sleep(10000);
	}*/

	//bot running loop
	while (true) {

		//grab the screen buffer before checking which state the bot is in
		robot.updatePixels();

		//in game state
		if (robot.getPixelDiff(GamePixel::HUD.x, GamePixel::HUD.y, GamePixel::HUD.color, tolerance)) {

			std::cout << "newGame: " << newGame << std::endl << std::endl;

			//if entering a new game, do these things before normal in game actions
			//actions: wait 5 seconds, buy items, attach to ally
			if (newGame) {
				//fixes weird issue where the game needs to be leftclicked once to allow the in game hotkeys to work
				robot.leftClick(GamePixel::arbitraryNearCenter.x, GamePixel::arbitraryNearCenter.y, clickSpeed);
				
				//spam taunt for 5 seconds, yuumi W is blocked for 5 seconds at the start of the game
				EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
				//there's 10 '4's being clicked, 20 * 250 = 5000 milliseconds = 5 seconds
				EventWriter::Keyboard::KeyType("11111111111111111111", 250);
				EventWriter::Keyboard::KeyUpVK(VK_CONTROL);

				//if blue side, set blue base coors
				if (robot.getPixelDiff(GamePixel::redSideFogOfWar.x, GamePixel::redSideFogOfWar.y, GamePixel::redSideFogOfWar.color, tolerance)) {
					baseX = GamePixel::blueBaseOnMinimap.x;
					baseY = GamePixel::blueBaseOnMinimap.y;
				}
				//if red side, set red base coors
				else {
					baseX = GamePixel::redBaseOnMinimap.x;
					baseY = GamePixel::redBaseOnMinimap.y;
				}

				//open shop with P hotkey
				EventWriter::Keyboard::KeyType('p', typeSpeed);

				//Ctrl + L is the item search hotkey
				EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
				EventWriter::Keyboard::KeyType('l', typeSpeed);
				EventWriter::Keyboard::KeyUpVK(VK_CONTROL);

				//search for Spellthief's Edge
				EventWriter::Keyboard::KeyType("spellthief", typeSpeed);
				//buy it with enter, and Microsoft calling enter VK_RETURN instead of VK_ENTER makes me unhappy >:(
				EventWriter::Keyboard::KeyTypeVK(VK_RETURN, typeSpeed);

				//search
				EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
				EventWriter::Keyboard::KeyType('l', typeSpeed);
				EventWriter::Keyboard::KeyUpVK(VK_CONTROL);

				//buy oracle lens
				EventWriter::Keyboard::KeyType("oracle lens", typeSpeed);
				EventWriter::Keyboard::KeyTypeVK(VK_RETURN, typeSpeed);

				//close shop with P hotkey
				EventWriter::Keyboard::KeyType('p', typeSpeed);

				//attach to your teammate by mousing over their champ icon above minimap farthest right
				robot.setCursorPos(GamePixel::teammateIconAboveMinimap.x, GamePixel::teammateIconAboveMinimap.y);
				EventWriter::Keyboard::KeyType('w', typeSpeed);

				//dont repeat these actions until accepting a new match
				newGame = false;

				robot.updatePixels();
			}

			//if not attached to ally
			if (robot.getPixelDiff(GamePixel::unattachedW.x, GamePixel::unattachedW.y, GamePixel::unattachedW.color, tolerance)) {

				//if teammate recalled, it re-attaches to them after buying item
				//if teammate died, it makes you run to the base

				//you can check if you're in base by looking at the color of the gold thing below items, it's brighter when in base
				//if in base (and not attached)
				if (robot.getPixelDiff(GamePixel::shopBright.x, GamePixel::shopBright.y, GamePixel::shopBright.color, tolerance)) {

					if (ableToBuyItems) {
						//buy items in this order (redemption, mikael's, ardent, staff of flowing water, shurelya's)

						//look item item slot N, if there's an empty slot or there's item component
							//try to buy item N
							//look at item slot N, if there's an empty slot (couldnt afford item N)
								//try to buy item component of item N

						if (robot.getPixelDiff(GamePixel::emptyItemSlot2.x, GamePixel::emptyItemSlot2.y, GamePixel::emptyItemSlot2.color, tolerance) || robot.getPixelDiff(GamePixel::forbiddenIdolSlot2.x, GamePixel::forbiddenIdolSlot2.y, GamePixel::forbiddenIdolSlot2.color, tolerance)) {
							//open shop with P hotkey
							EventWriter::Keyboard::KeyType('p', typeSpeed);

							//Ctrl + L is the item search hotkey
							EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
							EventWriter::Keyboard::KeyType('l', typeSpeed);
							EventWriter::Keyboard::KeyUpVK(VK_CONTROL);

							//search for redemption
							EventWriter::Keyboard::KeyType("redemption", typeSpeed);
							//buy it with enter
							EventWriter::Keyboard::KeyTypeVK(VK_RETURN, typeSpeed);

							//close shop with P hotkey
							EventWriter::Keyboard::KeyType('p', typeSpeed);

							robot.updatePixels();

							if (robot.getPixelDiff(GamePixel::emptyItemSlot2.x, GamePixel::emptyItemSlot2.y, GamePixel::emptyItemSlot2.color, tolerance)) {
								//open shop with P hotkey
								EventWriter::Keyboard::KeyType('p', typeSpeed);

								//Ctrl + L is the item search hotkey
								EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
								EventWriter::Keyboard::KeyType('l', typeSpeed);
								EventWriter::Keyboard::KeyUpVK(VK_CONTROL);

								//search for forbidden idol
								EventWriter::Keyboard::KeyType("forbidden idol", typeSpeed);
								//buy it with enter
								EventWriter::Keyboard::KeyTypeVK(VK_RETURN, typeSpeed);

								//close shop with P hotkey
								EventWriter::Keyboard::KeyType('p', typeSpeed);
							}
						}
						else if (robot.getPixelDiff(GamePixel::emptyItemSlot3.x, GamePixel::emptyItemSlot3.y, GamePixel::emptyItemSlot3.color, tolerance) || robot.getPixelDiff(GamePixel::forbiddenIdolSlot3.x, GamePixel::forbiddenIdolSlot3.y, GamePixel::forbiddenIdolSlot3.color, tolerance)) {
							//open shop with P hotkey
							EventWriter::Keyboard::KeyType('p', typeSpeed);

							//Ctrl + L is the item search hotkey
							EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
							EventWriter::Keyboard::KeyType('l', typeSpeed);
							EventWriter::Keyboard::KeyUpVK(VK_CONTROL);

							//search for mikael's blessing
							EventWriter::Keyboard::KeyType("mikael's blessing", typeSpeed);
							//buy it with enter
							EventWriter::Keyboard::KeyTypeVK(VK_RETURN, typeSpeed);

							//close shop with P hotkey
							EventWriter::Keyboard::KeyType('p', typeSpeed);

							robot.updatePixels();

							if (robot.getPixelDiff(GamePixel::emptyItemSlot3.x, GamePixel::emptyItemSlot3.y, GamePixel::emptyItemSlot3.color, tolerance)) {
								//open shop with P hotkey
								EventWriter::Keyboard::KeyType('p', typeSpeed);

								//Ctrl + L is the item search hotkey
								EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
								EventWriter::Keyboard::KeyType('l', typeSpeed);
								EventWriter::Keyboard::KeyUpVK(VK_CONTROL);

								//search for forbidden idol
								EventWriter::Keyboard::KeyType("forbidden idol", typeSpeed);
								//buy it with enter
								EventWriter::Keyboard::KeyTypeVK(VK_RETURN, typeSpeed);

								//close shop with P hotkey
								EventWriter::Keyboard::KeyType('p', typeSpeed);
							}
						}
						else if (robot.getPixelDiff(GamePixel::emptyItemSlot5.x, GamePixel::emptyItemSlot5.y, GamePixel::emptyItemSlot5.color, tolerance) || robot.getPixelDiff(GamePixel::forbiddenIdolSlot5.x, GamePixel::forbiddenIdolSlot5.y, GamePixel::forbiddenIdolSlot5.color, tolerance)) {
							//open shop with P hotkey
							EventWriter::Keyboard::KeyType('p', typeSpeed);

							//Ctrl + L is the item search hotkey
							EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
							EventWriter::Keyboard::KeyType('l', typeSpeed);
							EventWriter::Keyboard::KeyUpVK(VK_CONTROL);

							//search for ardent censor
							EventWriter::Keyboard::KeyType("ardent censor", typeSpeed);
							//buy it with enter
							EventWriter::Keyboard::KeyTypeVK(VK_RETURN, typeSpeed);

							//close shop with P hotkey
							EventWriter::Keyboard::KeyType('p', typeSpeed);

							robot.updatePixels();

							if (robot.getPixelDiff(GamePixel::emptyItemSlot5.x, GamePixel::emptyItemSlot5.y, GamePixel::emptyItemSlot5.color, tolerance)) {
								//open shop with P hotkey
								EventWriter::Keyboard::KeyType('p', typeSpeed);

								//Ctrl + L is the item search hotkey
								EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
								EventWriter::Keyboard::KeyType('l', typeSpeed);
								EventWriter::Keyboard::KeyUpVK(VK_CONTROL);

								//search for forbidden idol
								EventWriter::Keyboard::KeyType("forbidden idol", typeSpeed);
								//buy it with enter
								EventWriter::Keyboard::KeyTypeVK(VK_RETURN, typeSpeed);

								//close shop with P hotkey
								EventWriter::Keyboard::KeyType('p', typeSpeed);
							}
						}
						else if (robot.getPixelDiff(GamePixel::emptyItemSlot6.x, GamePixel::emptyItemSlot6.y, GamePixel::emptyItemSlot6.color, tolerance) || robot.getPixelDiff(GamePixel::forbiddenIdolSlot6.x, GamePixel::forbiddenIdolSlot6.y, GamePixel::forbiddenIdolSlot6.color, tolerance)) {
							//open shop with P hotkey
							EventWriter::Keyboard::KeyType('p', typeSpeed);

							//Ctrl + L is the item search hotkey
							EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
							EventWriter::Keyboard::KeyType('l', typeSpeed);
							EventWriter::Keyboard::KeyUpVK(VK_CONTROL);

							//search for staff of flowing water
							EventWriter::Keyboard::KeyType("staff of flowing water", typeSpeed);
							//buy it with enter
							EventWriter::Keyboard::KeyTypeVK(VK_RETURN, typeSpeed);

							//close shop with P hotkey
							EventWriter::Keyboard::KeyType('p', typeSpeed);

							robot.updatePixels();

							if (robot.getPixelDiff(GamePixel::emptyItemSlot6.x, GamePixel::emptyItemSlot6.y, GamePixel::emptyItemSlot6.color, tolerance)) {
								//open shop with P hotkey
								EventWriter::Keyboard::KeyType('p', typeSpeed);

								//Ctrl + L is the item search hotkey
								EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
								EventWriter::Keyboard::KeyType('l', typeSpeed);
								EventWriter::Keyboard::KeyUpVK(VK_CONTROL);

								//search for forbidden idol
								EventWriter::Keyboard::KeyType("forbidden idol", typeSpeed);
								//buy it with enter
								EventWriter::Keyboard::KeyTypeVK(VK_RETURN, typeSpeed);

								//close shop with P hotkey
								EventWriter::Keyboard::KeyType('p', typeSpeed);
							}
						}
						else if (robot.getPixelDiff(GamePixel::emptyItemSlot7.x, GamePixel::emptyItemSlot7.y, GamePixel::emptyItemSlot7.color, tolerance) || robot.getPixelDiff(GamePixel::bandleglassMirrorSlot7.x, GamePixel::bandleglassMirrorSlot7.y, GamePixel::bandleglassMirrorSlot7.color, tolerance)) {
							//open shop with P hotkey
							EventWriter::Keyboard::KeyType('p', typeSpeed);

							//Ctrl + L is the item search hotkey
							EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
							EventWriter::Keyboard::KeyType('l', typeSpeed);
							EventWriter::Keyboard::KeyUpVK(VK_CONTROL);

							//search for shurelya's battlesong
							EventWriter::Keyboard::KeyType("shurelya's battlesong", typeSpeed);
							//buy it with enter
							EventWriter::Keyboard::KeyTypeVK(VK_RETURN, typeSpeed);

							//close shop with P hotkey
							EventWriter::Keyboard::KeyType('p', typeSpeed);

							robot.updatePixels();

							if (robot.getPixelDiff(GamePixel::emptyItemSlot7.x, GamePixel::emptyItemSlot7.y, GamePixel::emptyItemSlot7.color, tolerance)) {
								//open shop with P hotkey
								EventWriter::Keyboard::KeyType('p', typeSpeed);

								//Ctrl + L is the item search hotkey
								EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
								EventWriter::Keyboard::KeyType('l', typeSpeed);
								EventWriter::Keyboard::KeyUpVK(VK_CONTROL);

								//search for bandleglass mirror
								EventWriter::Keyboard::KeyType("bandleglass mirror", typeSpeed);
								//buy it with enter
								EventWriter::Keyboard::KeyTypeVK(VK_RETURN, typeSpeed);

								//close shop with P hotkey
								EventWriter::Keyboard::KeyType('p', typeSpeed);
							}
						}

						//after leaving the base, the bot now buys items the next time it enters the base
						ableToBuyItems = false;
					}

					//while unattached after buying items in base, try attach to teammate until attached
					while (robot.getPixelDiff(GamePixel::unattachedW.x, GamePixel::unattachedW.y, GamePixel::unattachedW.color, tolerance)) {
						robot.setCursorPos(GamePixel::teammateIconAboveMinimap.x, GamePixel::teammateIconAboveMinimap.y);
						EventWriter::Keyboard::KeyType('w', typeSpeed);

						robot.updatePixels();
					}
				}
				//if unattached and out of base
				else if (robot.getPixelDiff(GamePixel::shopDark.x, GamePixel::shopDark.y, GamePixel::shopDark.color, tolerance)) {
					//able to buy items next time in base
					ableToBuyItems = true;

					//run to ally base set earlier in newGame
					robot.rightClick(baseX, baseY, clickSpeed);

					//if yuumi is low hp, heal with E
					if (robot.getPixelDiff(GamePixel::yuumiLowHP.x, GamePixel::yuumiLowHP.y, GamePixel::yuumiLowHP.color, tolerance)) {
						//E heal self
						EventWriter::Keyboard::KeyType('e', typeSpeed);
					}
				}
			}
			//if attached teammate's hp is REALLY low and attached to them
			else if (robot.getPixelDiff(GamePixel::attachedAllyReallyLowHP.x, GamePixel::attachedAllyReallyLowHP.y, GamePixel::attachedAllyReallyLowHP.color, tolerance) && robot.getPixelDiff(GamePixel::attachedW.x, GamePixel::attachedW.y, GamePixel::attachedW.color, tolerance)) {
				//summoner heal
				EventWriter::Keyboard::KeyType('d', typeSpeed);

				//redemption, on attached ally
				//mouse over ally icon above minimap, active items work using that icon
				robot.setCursorPos(GamePixel::teammateIconAboveMinimap.x, GamePixel::teammateIconAboveMinimap.y);
				EventWriter::Keyboard::KeyType('2', typeSpeed);
				robot.leftClick(GamePixel::teammateIconAboveMinimap.x, GamePixel::teammateIconAboveMinimap.y, clickSpeed);

				//mikaels, on attached ally
				EventWriter::Keyboard::KeyType('3', typeSpeed);
				robot.leftClick(GamePixel::teammateIconAboveMinimap.x, GamePixel::teammateIconAboveMinimap.y, clickSpeed);

				//E heal ally
				EventWriter::Keyboard::KeyType('e', typeSpeed);

				//shurelya's ally
				EventWriter::Keyboard::KeyType('7', typeSpeed);

				//ping mana
				EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
				robot.leftClick(GamePixel::yuumiManaBar.x, GamePixel::yuumiManaBar.y, clickSpeed);
				//ping E
				robot.leftClick(GamePixel::yuumiE.x, GamePixel::yuumiE.y, clickSpeed);
				EventWriter::Keyboard::KeyUpVK(VK_CONTROL);
			}
			//if attached teammate's hp is low and attached to them
			else if (robot.getPixelDiff(GamePixel::attachedAllyLowHP.x, GamePixel::attachedAllyLowHP.y, GamePixel::attachedAllyLowHP.color, tolerance) && robot.getPixelDiff(GamePixel::attachedW.x, GamePixel::attachedW.y, GamePixel::attachedW.color, tolerance)) {
				//E heal ally
				EventWriter::Keyboard::KeyType('e', typeSpeed);

				//ping mana
				EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
				robot.leftClick(GamePixel::yuumiManaBar.x, GamePixel::yuumiManaBar.y, clickSpeed);
				//ping E
				robot.leftClick(GamePixel::yuumiE.x, GamePixel::yuumiE.y, clickSpeed);
				EventWriter::Keyboard::KeyUpVK(VK_CONTROL);
			}

			//if any ability can be lvled up
			if (robot.getPixelDiff(GamePixel::canLevelUpQ.x, GamePixel::canLevelUpQ.y, GamePixel::canLevelUpQ.color, tolerance) ||
				robot.getPixelDiff(GamePixel::canLevelUpW.x, GamePixel::canLevelUpW.y, GamePixel::canLevelUpW.color, tolerance) ||
				robot.getPixelDiff(GamePixel::canLevelUpE.x, GamePixel::canLevelUpE.y, GamePixel::canLevelUpE.color, tolerance) ||
				robot.getPixelDiff(GamePixel::canLevelUpR.x, GamePixel::canLevelUpR.y, GamePixel::canLevelUpR.color, tolerance)) {
				//level up abilities E->W->R->Q, R and Q never get used tho
				std::cout << "lvling up e w r q now" << std::endl << std::endl;
				EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
				EventWriter::Keyboard::KeyType("ewrq", typeSpeed);
				EventWriter::Keyboard::KeyUpVK(VK_CONTROL);
			}
		}
		else
			//start queue state
			if (robot.getPixelDiff(GamePixel::findMatchButton.x, GamePixel::findMatchButton.y, GamePixel::findMatchButton.color, tolerance)) {
				//click start queue button
				robot.leftClick(GamePixel::findMatchButton.x, GamePixel::findMatchButton.y, clickSpeed);
			}
			else
				//accept match state, check for both unhighlighted and highlighted button, if someone doesnt accept a queue, the cursor remains on the button highlighting it for the next queue pop
				if (robot.getPixelDiff(GamePixel::acceptMatchButton.x, GamePixel::acceptMatchButton.y, GamePixel::acceptMatchButton.color, tolerance)
					|| robot.getPixelDiff(GamePixel::highlightedAcceptMatchButton.x, GamePixel::highlightedAcceptMatchButton.y, GamePixel::highlightedAcceptMatchButton.color, tolerance)) {
					//click accept match button
					robot.leftClick(GamePixel::acceptMatchButton.x, GamePixel::acceptMatchButton.y, clickSpeed);
					//set to true to allow for actions in the current champ select
					newChampSelect = true;
					//it makes newGame actions occur on the next while (true) loop cycle when in game
					newGame = true;

					std::cout << "newChampSelect and newGame now true" << '\n' << std::endl;
				}
				else
					//champ select state
					//only do these actions once per unique champ select, otherwise just wait until the next state
					//if (newChampSelect && robot.getPixelDiff(GamePixel::champSelect.x, GamePixel::champSelect.y, GamePixel::champSelect.color, tolerance)) {
						if (newChampSelect) {

						std::cout << "now in champ select state" << '\n' << std::endl;

						Sleep(250);

						//click on champ search box
						robot.leftClick(GamePixel::champSearchBox.x, GamePixel::champSearchBox.y, clickSpeed);
						//Sleep(100);

						//search for yuumi, yu only brings up yuumi as of lol patch 11.16
						EventWriter::Keyboard::KeyType("yu", typeSpeed);
						Sleep(450);

						//click yuumi icon
						robot.leftClick(GamePixel::yuumiChampSelectIcon.x, GamePixel::yuumiChampSelectIcon.y, clickSpeed);
						Sleep(200);

						//click the chat text box
						robot.leftClick(GamePixel::lobbyChatBox.x, GamePixel::lobbyChatBox.y, clickSpeed);
						//type "supp" or "im a parasite" to the other players in the lobby
						EventWriter::Keyboard::KeyType("im a parasite", typeSpeed);
						EventWriter::Keyboard::KeyTypeVK(VK_RETURN, typeSpeed);

						robot.updatePixels();

						//set left summoner spell if it is incorrect
						if (!robot.getPixelDiff(GamePixel::healSS.x, GamePixel::healSS.y, GamePixel::healSS.color, tolerance)) {
							std::cout << "left ss isnt right, fixing it" << std::endl << std::endl;
							//click the incorrect summoner spell where heal should be to open the ss panel
							robot.leftClick(GamePixel::healSS.x, GamePixel::healSS.y, clickSpeed);
							Sleep(500);

							//click the correct one to set it
							robot.leftClick(GamePixel::healSSInPanel.x, GamePixel::healSSInPanel.y, clickSpeed);
							Sleep(500);

							robot.updatePixels();
						}

						//set right summoner spell if needed
						if (!robot.getPixelDiff(GamePixel::barrierSS.x, GamePixel::barrierSS.y, GamePixel::barrierSS.color, tolerance)) {
							std::cout << "right ss isnt right, fixing it" << std::endl << std::endl;
							//click the incorrect summoner spell to open the ss panel
							robot.leftClick(GamePixel::barrierSS.x, GamePixel::barrierSS.y, clickSpeed);
							Sleep(500);

							//click the correct one to set it
							robot.leftClick(GamePixel::barrierSSInPanel.x, GamePixel::barrierSSInPanel.y, clickSpeed);
							Sleep(500);
						}

						//if the account lvl is high enough to edit runes, edit runes
						if (robot.getPixelDiff(GamePixel::editRunesIcon.x, GamePixel::editRunesIcon.y, GamePixel::editRunesIcon.color, tolerance)) {
							std::cout << "acc can edit runes" << std::endl << std::endl;
							//click on edit runes icon
							robot.leftClick(GamePixel::editRunesIcon.x, GamePixel::editRunesIcon.y, clickSpeed);
							Sleep(1000);

							robot.updatePixels();

							//if runes are set on row display, switch to grid
							//if (robot.getPixelDiff(GamePixel::runesRowDisplay.x, GamePixel::runesRowDisplay.y, GamePixel::runesRowDisplay.color, tolerance)) {
								//click on the grid style rune page display
								robot.leftClick(GamePixel::runesGridDisplay.x, GamePixel::runesGridDisplay.y, clickSpeed);
								Sleep(700);

								robot.updatePixels();
							//}

							//if the rune page is a preset (has a lock icon), change to the highest up rune page
							if (robot.getPixelDiff(GamePixel::runePageLock.x, GamePixel::runePageLock.y, GamePixel::runePageLock.color, tolerance)) {
								std::cout << "runepage is preset, selecting highest rune page" << std::endl << std::endl;
								//click on rune page drop-down bar
								robot.leftClick(GamePixel::runesDropDown.x, GamePixel::runesDropDown.y, clickSpeed);
								Sleep(300);

								//click on highest rune page
								robot.leftClick(GamePixel::runesTopPage.x, GamePixel::runesTopPage.y, clickSpeed);
								Sleep(700);

								robot.updatePixels();

								//if the rune page is still a preset, add a new rune page
								if (robot.getPixelDiff(GamePixel::runePageLock.x, GamePixel::runePageLock.y, GamePixel::runePageLock.color, tolerance)) {
									std::cout << "runepage is STILL preset, selecting add a new rune page" << std::endl << std::endl;
									//click on rune page drop-down bar
									robot.leftClick(GamePixel::runesDropDown.x, GamePixel::runesDropDown.y, clickSpeed);
									Sleep(300);

									//click on add new rune page
									robot.leftClick(GamePixel::addNewRunePage.x, GamePixel::addNewRunePage.y, clickSpeed);
									Sleep(700);
								}
							}

							robot.updatePixels();

							//check if each rune is unset, if each rune is incorrect, then set them if theyre incorrect or unset, but only when the runes window is open
							if (robot.getPixelDiff(GamePixel::mainRune1Unselected.x, GamePixel::mainRune1Unselected.y, GamePixel::mainRune1Unselected.color, tolerance) || !robot.getPixelDiff(GamePixel::guardian.x, GamePixel::guardian.y, GamePixel::guardian.color, tolerance)) {
								//click the Green Tree for main runes
								robot.leftClick(GamePixel::greenRuneTree.x, GamePixel::greenRuneTree.y, clickSpeed);
								Sleep(100);
								//set Guardian
								robot.leftClick(GamePixel::guardian.x, GamePixel::guardian.y, clickSpeed);
								Sleep(100);
							}

							if (robot.getPixelDiff(GamePixel::mainRune2Unselected.x, GamePixel::mainRune2Unselected.y, GamePixel::mainRune2Unselected.color, tolerance) || !robot.getPixelDiff(GamePixel::fontOfLife.x, GamePixel::fontOfLife.y, GamePixel::fontOfLife.color, tolerance)) {
								//set Font Of Life
								robot.leftClick(GamePixel::fontOfLife.x, GamePixel::fontOfLife.y, clickSpeed);
								Sleep(100);
							}

							if (robot.getPixelDiff(GamePixel::mainRune3Unselected.x, GamePixel::mainRune3Unselected.y, GamePixel::mainRune3Unselected.color, tolerance) || !robot.getPixelDiff(GamePixel::bonePlating.x, GamePixel::bonePlating.y, GamePixel::bonePlating.color, tolerance)) {
								//set Bone Plating
								robot.leftClick(GamePixel::bonePlating.x, GamePixel::bonePlating.y, clickSpeed);
								Sleep(100);
							}

							if (robot.getPixelDiff(GamePixel::mainRune4Unselected.x, GamePixel::mainRune4Unselected.y, GamePixel::mainRune4Unselected.color, tolerance) || !robot.getPixelDiff(GamePixel::revitalize.x, GamePixel::revitalize.y, GamePixel::revitalize.color, tolerance)) {
								//set Revitalize
								robot.leftClick(GamePixel::revitalize.x, GamePixel::revitalize.y, clickSpeed);
								Sleep(100);
							}

							if (robot.getPixelDiff(GamePixel::secondaryRune1Unselected.x, GamePixel::secondaryRune1Unselected.y, GamePixel::secondaryRune1Unselected.color, tolerance) || !robot.getPixelDiff(GamePixel::absoluteFocus.x, GamePixel::absoluteFocus.y, GamePixel::absoluteFocus.color, tolerance)) {
								//click the Blue Tree for secondary runes
								robot.leftClick(GamePixel::blueRuneTree.x, GamePixel::blueRuneTree.y, clickSpeed);
								Sleep(100);
								//set Absolute Focus
								robot.leftClick(GamePixel::absoluteFocus.x, GamePixel::absoluteFocus.y, clickSpeed);
								Sleep(100);
							}

							if (robot.getPixelDiff(GamePixel::secondaryRune2Unselected.x, GamePixel::secondaryRune2Unselected.y, GamePixel::secondaryRune2Unselected.color, tolerance) || !robot.getPixelDiff(GamePixel::gatheringStorm.x, GamePixel::gatheringStorm.y, GamePixel::gatheringStorm.color, tolerance)) {
								//set Gathering Storm
								robot.leftClick(GamePixel::gatheringStorm.x, GamePixel::gatheringStorm.y, clickSpeed);
								Sleep(100);
							}

							if (robot.getPixelDiff(GamePixel::statRune1Unselected.x, GamePixel::statRune1Unselected.y, GamePixel::statRune1Unselected.color, tolerance) || !robot.getPixelDiff(GamePixel::adaptiveForce1.x, GamePixel::adaptiveForce1.y, GamePixel::adaptiveForce1.color, tolerance)) {
								//set Adaptive Force 1
								robot.leftClick(GamePixel::adaptiveForce1.x, GamePixel::adaptiveForce1.y, clickSpeed);
								Sleep(100);
							}

							if (robot.getPixelDiff(GamePixel::statRune2Unselected.x, GamePixel::statRune2Unselected.y, GamePixel::statRune2Unselected.color, tolerance) || !robot.getPixelDiff(GamePixel::adaptiveForce2.x, GamePixel::adaptiveForce2.y, GamePixel::adaptiveForce2.color, tolerance)) {
								//set Adaptive Force 2
								robot.leftClick(GamePixel::adaptiveForce2.x, GamePixel::adaptiveForce2.y, clickSpeed);
								Sleep(100);
							}

							if (robot.getPixelDiff(GamePixel::statRune3Unselected.x, GamePixel::statRune3Unselected.y, GamePixel::statRune3Unselected.color, tolerance) || !robot.getPixelDiff(GamePixel::armor.x, GamePixel::armor.y, GamePixel::armor.color, tolerance)) {
								//set Armor
								robot.leftClick(GamePixel::armor.x, GamePixel::armor.y, clickSpeed);
								Sleep(100);
							}

							robot.updatePixels();

							if (robot.getPixelDiff(GamePixel::saveRunes.x, GamePixel::saveRunes.y, GamePixel::saveRunes.color, tolerance)) {
								//click save button
								robot.leftClick(GamePixel::saveRunes.x, GamePixel::saveRunes.y, clickSpeed);
								Sleep(100);
							}

							//if (robot.getPixelDiff(x, y, runesPageColor, tolerance)) {
								//click X button to exit runes
							robot.leftClick(GamePixel::exitRunes.x, GamePixel::exitRunes.y, clickSpeed);
							Sleep(100);
							//}
						}

						//click lock in
						robot.leftClick(GamePixel::lockInButton.x, GamePixel::lockInButton.y, clickSpeed);
						Sleep(200);

						//dont repeat these actions until the current champ select state has ended (dodged, or game started)
						newChampSelect = false;
					}
		//else
		////honor teammate state
		//if (robot.getPixelDiff(honorTeammate.x, honorTeammate.y, honorTeammate.color, tolerance)) {
		//    //look for honor teammate, always honor arbitrary player
		//    robot.leftClick(honorTeammate.x, honorTeammate.y, clickSpeed);
		//}
		//else
		////post game state
		//if (robot.getPixelDiff(playAgainButton.x, playAgainButton.y, playAgainButton.color, tolerance)) {
		//    //type "gg" in post game text box
		//    robot.leftClick(lobbyChatBox.x, lobbyChatBox.y, clickSpeed);
		//    EventWriter::Keyboard::KeyType("gg", typeSpeed);
		//    //click play again
		//    robot.leftClick(playAgainButton.x, playAgainButton.y, clickSpeed);
		//}
		//else
		////level up state
		//if (robot.getPixelDiff(levelUp.x, levelUp.y, levelUp.color, tolerance)) {
		//    //click ok button
		//    robot.leftClick(levelUp.x, levelUp.y, clickSpeed);
		//}
		//else
		////daily reward state
		//if (robot.getPixelDiff(dailyReward.x, dailyReward.y, dailyReward.color, tolerance)) {
		//    //click ok button
		//    robot.leftClick(dailyReward.x, dailyReward.y, clickSpeed);
		//}
		//else
		////champion reward state
		//if (robot.getPixelDiff(championReward.x, championReward.y, championReward.color, tolerance)) {
		//    //click select on arbitrary champion
		//    robot.leftClick(selectChampionReward.x, selectChampionReward.y, clickSpeed);
		//    //click okay
		//    robot.leftClick(championReward.x, championReward.y, clickSpeed);
		//}
		//else
		////quest reward state
		//if (robot.getPixelDiff(questReward.x, questReward.y, questReward.color, tolerance)) {
		//    //click ok button
		//    robot.leftClick(questReward.x, questReward.y, clickSpeed);
		//}
		//else
		//{

		//move cursor off the lol client to avoid hovering over any icons which would change their RGBs and mess up the bot
		//also moves cursor off the higlightable parts of the in game HUD to avoid messing up their pixels too
		//robot.setCursorPos(GamePixel::mouseOffLOLClient.x, GamePixel::mouseOffLOLClient.y);
		//}

		//std::cout << "end of main while loop" << std::endl;
	}
}