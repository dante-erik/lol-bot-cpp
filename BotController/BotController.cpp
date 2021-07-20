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

    while (true) {
        //look for ingame
            //look for attached to player, if not attached, click to run home, press E
                //while not in base, click to run home, press E
                //if in base, buy items, try to attach to all teammates (click W on all prof icons bottom right above minimap), if not attached still, choose alive player to attach to
            //look for attached to player, if attached, check player's hp, if it's lower than some arbitrary value, heal with E, if still lower than value, heal with Redemption and heal with Mikaels
            //look for leveled up, upgrade E->W->R->Q
        //look for start queue
        //look for accept match
        //look for champion search box, type yuumi
        //look for yuumi, if not picked, pick it, if dont own yuumi, stop program and throw an error, if already picked, dodge and relog
        //look for lobby text box, type "support uwu" and click enter
        //look for summoner spells, if already set correctly, do nothing, if wrong, set correctly
        //look for able to edit runes icon, if true, click edit, if runes already set, close runes, if runes not set, set runes and close runes
        //look for play button, click it
        //look for gamemode select screen, click normal game blind pick, click diff play button
        //look for honor teammate, always honor arbitrary player
        //look for popups like lvl up and quests, click ok
        //look for play again button, click it
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
