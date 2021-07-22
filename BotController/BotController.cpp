// BotController.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Winuser.h>
#include "Robot.hpp"
//include "RGBQuadValues.hpp"

int main()
{
    std::cout << "Hello World!\n";

    //collect pixel data beforehand to be used for getPixelDiff() bool
    //create humanrobot for yuumi
    //loop 1, while true
    //get screen
    //check state
    //if true, action
    //else, check state
    //end loop 1

    Robot robot = Robot();

    //how exact the pixel color's RGBs need to be
    double tolerance = 0.0;

    //in milliseconds
    DWORD clickSpeed = 80;
    DWORD typeSpeed = 40;

    //checking for new champ selects to avoid repeating actions
    bool newChampSelect = true;

    //counts each iteration of the while (true) loop, used for debugging only
    unsigned long counter = 0;

    while (true) {

        //in game state
        while (robot.getPixelDiff(x, y, inGameColor, tolerance)) {
            //look for attached to player, if not attached, click to run home, press E
                //while not in base, click to run home, press E
                //if in base, buy items, try to attach to all teammates (click W on all prof icons bottom right above minimap), if not attached still, choose alive player to attach to
            //look for attached to player, if attached, check player's hp, if it's lower than some arbitrary value, heal with E, if still lower than value, heal with Redemption and heal with Mikaels
            //look for leveled up, upgrade E->W->R->Q
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
        }

        //set to true to allow for actions in the champ select
        newChampSelect = true;
        //champ select state
        while (robot.getPixelDiff(x, y, champSelectColor, tolerance)) {
            if (newChampSelect) {
                //click on champ search box
                robot.leftClick(x, y, clickSpeed);
                //search for yuumi
                robot.keyType("Yuumi", typeSpeed);
                //click yuumi icon
                robot.leftClick(x, y, clickSpeed);

                do {
                    //click lock in until it locks in yuumi
                    robot.leftClick(x, y, clickSpeed);
                } while (robot.getPixelDiff(x, y, yuumiColor, tolerance));

                //click the chat text box
                robot.leftClick(x, y, clickSpeed);
                //type "support" to the other players in the lobby
                robot.keyType("support", typeSpeed);

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

                    //check each rune and set them if theyre incorrect
                    if (!robot.getPixelDiff(x, y, guardianColor, tolerance) && robot.getPixelDiff(x, y, champSelectColor, tolerance)) {
                        //click the Green Tree for main runes
                        robot.leftClick(x, y, clickSpeed);
                        //set Guardian
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if (!robot.getPixelDiff(x, y, fontOfLifeColor, tolerance) && robot.getPixelDiff(x, y, champSelectColor, tolerance)) {
                        //set Font Of Life
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if (!robot.getPixelDiff(x, y, bonePlatingColor, tolerance) && robot.getPixelDiff(x, y, champSelectColor, tolerance)) {
                        //set Bone Plating
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if (!robot.getPixelDiff(x, y, revitalizeColor, tolerance) && robot.getPixelDiff(x, y, champSelectColor, tolerance)) {
                        //set Revitalize
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if (!robot.getPixelDiff(x, y, absoluteFocusColor, tolerance) && robot.getPixelDiff(x, y, champSelectColor, tolerance)) {
                        //click the Blue Tree for secondary runes
                        robot.leftClick(x, y, clickSpeed);
                        //set Absolute Focus
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if (!robot.getPixelDiff(x, y, gatheringStormColor, tolerance) && robot.getPixelDiff(x, y, champSelectColor, tolerance)) {
                        //set Gathering Storm
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if (!robot.getPixelDiff(x, y, adaptiveForce1Color, tolerance) && robot.getPixelDiff(x, y, champSelectColor, tolerance)) {
                        //set Adaptive Force
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if (!robot.getPixelDiff(x, y, adaptiveForce2Color, tolerance) && robot.getPixelDiff(x, y, champSelectColor, tolerance)) {
                        //set Adaptive Force
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if (!robot.getPixelDiff(x, y, armorColor, tolerance) && robot.getPixelDiff(x, y, champSelectColor, tolerance)) {
                        //set Armor
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if (!robot.getPixelDiff(x, y, saveColor, tolerance) && robot.getPixelDiff(x, y, champSelectColor, tolerance)) {
                        //click save button
                        robot.leftClick(x, y, clickSpeed);
                    }

                    if (robot.getPixelDiff(x, y, champSelectColor, tolerance)) {
                        //click X button
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

        //post-game state
        while (robot.getPixelDiff(x, y, postGameColor, tolerance)) {
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
            //click select on middle champion
            robot.leftClick(x, y, clickSpeed);
            //click okay
            robot.leftClick(x, y, clickSpeed);
        }

        //quest reward state
        while (robot.getPixelDiff(x, y, questColor, tolerance)) {
            //click ok button
            robot.leftClick(x, y, clickSpeed);
        }

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
