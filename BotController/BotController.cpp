// BotController.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Winuser.h>
#include "Robot.hpp"
//include "RGBQuadValues.hpp"

int main()
{
    Robot robot = Robot();

    //how exact the pixel color's RGBs need to be
    double tolerance = 0.0;

    //in milliseconds
    DWORD clickSpeed = 80;
    DWORD typeSpeed = 40;

    //checking for new champ selects to avoid repeating actions
    //set to false after finishing all champ select specific actions in a new champ select state
    //set to true after accepting a new match
    bool newChampSelect = true;

    //avoid repeating starting actions in game
    //set to false at the end of newGame if actions
    //set to true after accepting a new match
    bool newGame = true;

    //counts each iteration of the while (true) loop, used for debugging only
    unsigned long counter = 0;

    while (true) {

        //if entering a new game, do these things before normal in game actions
        //actions: wait 5 seconds, buy items, attach to ally
        if (newGame) {
            //spam laugh for 5 seconds, yuumi W is blocked for 5 seconds at the start of the game
            EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
            //there's 10 '4's being clicked, 10 * 500 = 5000 milliseconds = 5 seconds
            EventWriter::Keyboard::KeyType("4444444444", 500);
            EventWriter::Keyboard::KeyUpVK(VK_CONTROL);

            //open shop with P hotkey
            EventWriter::Keyboard::KeyType('p', typeSpeed);

            //Ctrl + L is the item search hotkey
            EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
            EventWriter::Keyboard::KeyType('l', typeSpeed);
            EventWriter::Keyboard::KeyUpVK(VK_CONTROL);

            //search for Spellthief's Edge
            EventWriter::Keyboard::KeyType("spellthief", typeSpeed);
            //buy it with enter, and Microsoft calling enter VK_RETURN instead of VK_ENTER is gonna be a no for me
            EventWriter::Keyboard::KeyTypeVK(VK_RETURN, typeSpeed);

            //search
            EventWriter::Keyboard::KeyDownVK(VK_CONTROL);
            EventWriter::Keyboard::KeyType('l', typeSpeed);
            EventWriter::Keyboard::KeyUpVK(VK_CONTROL);

            //buy oracle lens
            EventWriter::Keyboard::KeyType("oracle lens", typeSpeed);
            EventWriter::Keyboard::KeyTypeVK(VK_RETURN, typeSpeed);

            //attached to your teammate by mousing over their champ icon above minimap
            robot.leftClick(x, y, clickSpeed);

            newGame = false;
        }

        //in game state
        while (robot.getPixelDiff(x, y, inGameColor, tolerance)) {
            //always makes sure yuumi is attached or trying to attach
            if (/*not attached cuz of ally death*/) {
                //attach to different teammate
            }
            else if (/*not attached cuz of ally recall*/) {
                //buy items, re-attach to same teammate
            }

            if (/*attached and attached ally hp is REALLY low*/) {
                //summoner heal
                //redemption
                //mikaels
                //E heal ally
                //ping mana
                //ping E
            }
            else if (/*attached and attached ally hp is low*/) {
                //E heal ally
                //ping mana
                //ping E
            }

            if (/*not attached and not in base and yuumi hp is low*/) {
                //E heal yuumi
            }

            //you can check if you're in base by looking at the color of the gold thing below items, it's brighter when in base
            if (/*in base*/) {
                //buy items (forbidden idol, redemption, mikaels, moonstone, ardent, staff of flowing water)
                //re-attach to same teammate since they must've recalled
            }

            //level up abilities E->W->R->Q, R and Q never get used
            if (/*E can be leveled up*/) {
                //level up E
            }
            else if (/*W can be leveled up*/) {
                //level up W
            }
            else if (/*R can be leveled up*/) {
                //level up R
            }
            else if (/*Q can be leveled up*/) {
                //level up Q
            }
        }

        //start queue state
        while (robot.getPixelDiff(x, y, startQueueColor, tolerance)) {
            //click start queue button
            robot.leftClick(x, y, clickSpeed);
        }

        //accept match state
        while (robot.getPixelDiff(x, y, acceptMatchColor, tolerance)) {
            //click accept match button
            robot.leftClick(x, y, clickSpeed);
            //set to true to allow for actions in the current champ select
            newChampSelect = true;
            //it makes newGame actions occur on the next while (true) loop cycle when in game
            newGame = true;
        }

        

        //champ select state
        while (robot.getPixelDiff(x, y, champSelectColor, tolerance)) {
            //only do these actions once per unique champ select, otherwise just wait until the next state
            if (newChampSelect) {
                //click on champ search box
                robot.leftClick(x, y, clickSpeed);
                //search for yuumi
                EventWriter::Keyboard::KeyType("Yuumi", typeSpeed);
                //click yuumi icon
                robot.leftClick(x, y, clickSpeed);

                do {
                    //click lock in until it locks in yuumi
                    robot.leftClick(x, y, clickSpeed);
                } while (robot.getPixelDiff(x, y, yuumiColor, tolerance));

                //click the chat text box
                robot.leftClick(x, y, clickSpeed);
                //type "support" to the other players in the lobby
                EventWriter::Keyboard::KeyType("support", typeSpeed);
                EventWriter::Keyboard::KeyType('p', 100);

                //set left summoner spell if it is incorrect
                if (!robot.getPixelDiff(x, y, summonerSpellsColorLeft, tolerance) && robot.getPixelDiff(x, y, champSelectColor, tolerance)) {
                    //click the incorrect summoner spell to open the ss panel
                    robot.leftClick(x, y, clickSpeed);
                    //click the correct one to set it
                    robot.leftClick(x, y, clickSpeed);
                }

                //set right summoner spell if needed
                if (!robot.getPixelDiff(x, y, summonerSpellsColorRight, tolerance) && robot.getPixelDiff(x, y, champSelectColor, tolerance)) {
                    //click the incorrect summoner spell to open the ss panel
                    robot.leftClick(x, y, clickSpeed);
                    //click the correct one to set it
                    robot.leftClick(x, y, clickSpeed);
                }

                //if the account lvl is high enough to edit runes, edit runes
                if (robot.getPixelDiff(x, y, editRunesIconColor, tolerance)) {
                    //click on edit runes icon
                    robot.leftClick(x, y, clickSpeed);

                    //check if each rune is unset, if each rune is incorrect, then set them if theyre incorrect or unset, but only when the runes window is open
                    if ((robot.getPixelDiff(x, y, mainRune1UnselectedColor, tolerance) || !robot.getPixelDiff(x, y, guardianColor, tolerance)) && robot.getPixelDiff(x, y, runesPageColor, tolerance)) {
                        //click the Green Tree for main runes
                        robot.leftClick(x, y, clickSpeed);
                        //set Guardian
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if ((robot.getPixelDiff(x, y, mainRune2UnselectedColor, tolerance) || !robot.getPixelDiff(x, y, fontOfLifeColor, tolerance)) && robot.getPixelDiff(x, y, runesPageColor, tolerance)) {
                        //set Font Of Life
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if ((robot.getPixelDiff(x, y, mainRune3UnselectedColor, tolerance) || !robot.getPixelDiff(x, y, bonePlatingColor, tolerance)) && robot.getPixelDiff(x, y, runesPageColor, tolerance)) {
                        //set Bone Plating
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if ((robot.getPixelDiff(x, y, mainRune4UnselectedColor, tolerance) || !robot.getPixelDiff(x, y, revitalizeColor, tolerance)) && robot.getPixelDiff(x, y, runesPageColor, tolerance)) {
                        //set Revitalize
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if ((robot.getPixelDiff(x, y, secondaryRune1UnselectedColor, tolerance) || !robot.getPixelDiff(x, y, absoluteFocusColor, tolerance)) && robot.getPixelDiff(x, y, runesPageColor, tolerance)) {
                        //click the Blue Tree for secondary runes
                        robot.leftClick(x, y, clickSpeed);
                        //set Absolute Focus
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if ((robot.getPixelDiff(x, y, secondaryRune2UnselectedColor, tolerance) || !robot.getPixelDiff(x, y, gatheringStormColor, tolerance)) && robot.getPixelDiff(x, y, runesPageColor, tolerance)) {
                        //set Gathering Storm
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if ((robot.getPixelDiff(x, y, statRune1UnselectedColor, tolerance) || !robot.getPixelDiff(x, y, adaptiveForce1Color, tolerance)) && robot.getPixelDiff(x, y, runesPageColor, tolerance)) {
                        //set Adaptive Force
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if ((robot.getPixelDiff(x, y, statRune2UnselectedColor, tolerance) || !robot.getPixelDiff(x, y, adaptiveForce2Color, tolerance)) && robot.getPixelDiff(x, y, runesPageColor, tolerance)) {
                        //set Adaptive Force
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if ((robot.getPixelDiff(x, y, statRune3UnselectedColor, tolerance) || !robot.getPixelDiff(x, y, armorColor, tolerance)) && robot.getPixelDiff(x, y, runesPageColor, tolerance)) {
                        //set Armor
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if (robot.getPixelDiff(x, y, saveRunesColor, tolerance)) {
                        //click save button
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if (robot.getPixelDiff(x, y, runesPageColor, tolerance)) {
                        //click X button to exit runes
                        robot.leftClick(x, y, clickSpeed);
                    }
                }
                //dont repeat these actions until the current champ select state has ended (dodged, or game started)
                newChampSelect = false;
            }
        }

        //honor teammate state
        while (robot.getPixelDiff(x, y, honorColor, tolerance)) {
            //look for honor teammate, always honor arbitrary player
            robot.leftClick(x, y, clickSpeed);
        }

        //post game state
        while (robot.getPixelDiff(x, y, postGameColor, tolerance)) {
            //type "gg" in post game text box
            robot.leftClick(x, y, clickSpeed);
            EventWriter::Keyboard::KeyType("gg", typeSpeed);
            //click play again
            robot.leftClick(x, y, clickSpeed);
        }

        //level up state
        while (robot.getPixelDiff(x, y, levelUpColor, tolerance)) {
            //click ok button
            robot.leftClick(x, y, clickSpeed);
        }

        //champion reward state
        while (robot.getPixelDiff(x, y, championRewardColor, tolerance)) {
            //click select on arbitrary champion
            robot.leftClick(x, y, clickSpeed);
            //click okay
            robot.leftClick(x, y, clickSpeed);
        }

        //quest reward state
        while (robot.getPixelDiff(x, y, questColor, tolerance)) {
            //click ok button
            robot.leftClick(x, y, clickSpeed);
        }

        //add the rest of the states here after reviewing the old java lol bot's code

        //counts and displays how many while (true) loops have run, only used for debugging
        counter++;
        std::cout << "end of loop reached" << counter << std::endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
