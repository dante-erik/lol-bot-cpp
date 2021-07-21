// BotController.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Robot.hpp"

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

    Robot robot = new Robot();

    //how exact the pixel color's RGBs need to be
    double tolerance = 0.0;

    //in milliseconds
    DWORD clickSpeed = 80;
    DWORD keyTypeSpeed = 40;

    while (true) {
        //look for ingame
        if (robot.GetPixelDiff(x, y, inGameColor, tolerance)) {
            //look for attached to player, if not attached, click to run home, press E
                //while not in base, click to run home, press E
                //if in base, buy items, try to attach to all teammates (click W on all prof icons bottom right above minimap), if not attached still, choose alive player to attach to
            //look for attached to player, if attached, check player's hp, if it's lower than some arbitrary value, heal with E, if still lower than value, heal with Redemption and heal with Mikaels
            //look for leveled up, upgrade E->W->R->Q
        }
        else if (robot.getPixelDiff(x, y, startQueueColor, tolerance)) {
            //look for start queue
            robot.LeftClick(x, y, clickSpeed);
        }
        else if (robot.getPixelDiff(x, y, acceptMatchColor, tolerance)) {
            //look for accept match
            robot.LeftClick(x, y, clickSpeed);
        }
        else if (robot.getPixelDiff(x, y, champSearchColor, tolerance)) {
            //look for champion search box, type yuumi
            robot.LeftClick(x, y, clickSpeed);
            robot.KeyType("Yuumi", keyTypeSpeed);
        }
        else if (robot.GetPixelDiff(x, y, yuumiColor, tolerance)) {
            //look for yuumi, if not picked, pick it, if dont own yuumi, stop program and throw an error, if already picked, dodge and relog
            robot.LeftClick(x, y, clickSpeed);
            //click lock in
            robot.LeftClick(x, y, clickSpeed);
        }
        else if (robot.GetPixelDiff(x, y, lobbyTextBoxColor, tolerance)) {
            //look for lobby text box, type "support" and click enter
            robot.LeftClick(x, y, clickSpeed);
            robot.KeyType("support", keyTypeSpeed);
            //click enter
            robot.KeyType(13, keyTypeSpeed);
        }
        else if (robot.GetPixelDiff(x, y, runesEditIconColor, tolerance)) {
            //check each rune and set them if theyre incorrect
            if (!robot.GetPixelDiff(x, y, guardianColor, tolerance)) {
                //click the Green Tree for main runes
                robot.LeftClick(x, y, clickSpeed);
                //set Guardian
                robot.LeftClick(x, y, clickSpeed);
            }
            if (!robot.GetPixelDiff(x, y, fontOfLifeColor, tolerance)) {
                //set Font Of Life
                robot.LeftClick(x, y, clickSpeed);
            }
            if (!robot.GetPixelDiff(x, y, bonePlatingColor, tolerance)) {
                //set Bone Plating
                robot.LeftClick(x, y, clickSpeed);
            }
            if (!robot.GetPixelDiff(x, y, revitalizeColor, tolerance)) {
                //set Revitalize
                robot.LeftClick(x, y, clickSpeed);
            }
            if (!robot.GetPixelDiff(x, y, absoluteFocusColor, tolerance)) {
                //set Absolute Focus
                robot.LeftClick(x, y, clickSpeed);
            }
            if (!robot.GetPixelDiff(x, y, gatheringStormColor, tolerance)) {
                //set Gathering Storm
                robot.LeftClick(x, y, clickSpeed);
            }
            if (!robot.GetPixelDiff(x, y, adaptiveForce1Color, tolerance)) {
                //set Adaptive Force
                robot.LeftClick(x, y, clickSpeed);
            }
            if (!robot.GetPixelDiff(x, y, adaptiveForce2Color, tolerance)) {
                //set Adaptive Force
                robot.LeftClick(x, y, clickSpeed);
            }
            if (!robot.GetPixelDiff(x, y, armorColor, tolerance)) {
                //set Armor
                robot.LeftClick(x, y, clickSpeed);
            }
            if (!robot.GetPixelDiff(x, y, saveColor, tolerance)) {
                //click save button
                robot.LeftClick(x, y, clickSpeed);
            }
            //click X button
            robot.LeftClick(x, y, clickSpeed);
        }
        //if they left or right ss isnt set correctly, check left, set, check right, set
        else if (!robot.GetPixelDiff(x, y, summonerSpellsColorLeft, tolerance) || !robot.GetPixelDiff(x, y, summonerSpellsColorRight, tolerance)) {
            if (!robot.GetPixelDiff(x, y, summonerSpellsColorLeft, tolerance)) {
                robot.LeftClick(x, y, clickSpeed);
                robot.LeftClick(x, y, clickSpeed);
            }
            if (!robot.GetPixelDiff(x, y, summonerSpellsColorRight, tolerance)) {
                robot.LeftClick(x, y, clickSpeed);
                robot.LeftClick(x, y, clickSpeed);
            }
        }
        else if (robot.GetPixelDiff(x, y, honorColor, tolerance)) {
            //look for honor teammate, always honor arbitrary player
            robot.LeftClick(x, y, clickSpeed);
        }
        else if (robot.GetPixelDiff(x, y, playAgainColor, tolerance)) {
            //click play again
            robot.LeftClick(x, y, clickSpeed);
        }
        else if (robot.GetPixelDiff(x, y, levelUpColor, tolerance)) {
            //click ok button
            robot.LeftClick(x, y, clickSpeed);
        }
        else if (robot.GetPixelDiff(x, y, questColor, tolerance)) {
            //click ok button
            robot.LeftClick(x, y, clickSpeed);
        }
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
