#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "TileCodes.h"

class Menu{
    public:

    Menu();

    bool getQuit();
    void setQuit(bool quitBool);
    void printMenu();
    void printCredits();

    std::vector<std::string> takeLineInput(char charToSplit);

    std::string getName();
    int charToInt(char character);



    private:
    bool quit;

    void printHelp();

};

#endif //MENU_H