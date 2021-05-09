#ifndef GAMEPLAY
#define GAMEPLAY

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <random>

#include "Board.h"
#include "Player.h"
#include "Menu.h"


class GamePlay
{
    public:

    GamePlay();
    ~GamePlay();


    bool check(char *s);
    void NewGame();




    std::vector<Tile *> initialiseTileBag();
    
    bool playerMove(Board *theBoard, Player *player, Player* player2, Menu* menu);
    bool tileInputtedIsOkay(std::string tileString, Player *player);
    bool isOnBoard(int row, int col, Board *board);
    bool tileFit(Tile *tile, Board *theBoard, Location *loaction);

    bool placeTile(std::vector<std::string> wordsIn, Board *theBoard, Player *player);
    bool replaceTile(std::vector<std::string> wordsIn, Board *theBoard, Player *player);
    bool saveGame(std::vector<std::string> wordsIn, Board *theBoard, Player *player, Player* player2);

    int convertToRow(char row);
    int convertToCol(char col);

    //MOVE LATER
    int getRow(int currentRow, int direction);
    int getCol(int currentCol, int direction);

    Tile *turnInputToTile(std::string tiledata);

    Location *convertInputLoc(std::string inputLocation);

    int score(Location* location, Board* theBoard);

    void HandPlayerTile(Player* player, Board* theBoard);

    // Board* theBoard;
    // Player* player1;
    // Player* player2;
    private:
    Menu* menu ;


};




#endif //GAMEPLAY