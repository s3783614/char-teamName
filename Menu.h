#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "GamePlay.h"

class Menu{
    public:
    void printMenu();
    void printCredits();

    void quit();

    std::vector<std::string> takeLineInput(char charToSplit, GamePlay* theGame);

    std::string getName(GamePlay* theGame);


    private:
};

#endif //MENU_H