#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "TileCodes.h"

class Menu{
    public:
    void printMenu();
    void printCredits();

    void quit();

    std::vector<std::string> takeLineInput(char charToSplit);

    std::string getName();
    int charToInt(char character);



    private:
};

#endif //MENU_H