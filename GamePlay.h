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
    
    bool playerMove(Menu* menu, int playerTurn);
    bool tileInputtedIsOkay(std::string tileString, Player *player);
    
    bool tileFit(Tile *tile, Location location);
    bool checkBothSides(int direction1, int direction2, Location location, Tile* tile);

    bool compareTiles(std::vector<Tile*>* tileInLine);
    void checkDirection(int direction1, Location location, std::vector<Tile*>* tileInLine);
    bool checkIfNextToTiles(Location location);

    bool placeTile(std::vector<std::string> wordsIn, Player *player);
    bool replaceTile(std::vector<std::string> wordsIn, Player *player);
    bool saveGame(std::vector<std::string> wordsIn, Player *player, Player* player2);

    int convertToRow(char row);
    int convertToCol(char col);

    // int getRow(int currentRow, int direction);
    // int getCol(int currentCol, int direction);

    Tile *turnInputToTile(std::string tiledata);

    Location convertInputLoc(std::string inputLocation);

    int score(Location location);

    void HandPlayerTile(Player* player);
    void setPlayer(Player* player);

    void setBoard(Board* theBoard);
    int scoreDirection(int direction, Location location);

    private:
    Menu* menu ;
    Board* theBoard;
    Player* player1;
    Player* player2;

};




#endif //GAMEPLAY