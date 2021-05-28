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

   void setMenu(Menu* menu);
   Menu* getMenu();
    void setPlayer(Player* player);
    void setBoard(Board* theBoard);
    Board* getBoard();

    bool check(char *s);
    void NewGame();
    
    bool playerMove(int playerTurn);
    bool tileInputtedIsOkay(std::string tileString, Player *player);
    bool legalMove(Player* player);
    
    bool tileFit(Tile *tile, Location location);
    bool checkBothSides(int direction1, int direction2, Location location, Tile* tile);

    bool compareTiles(std::vector<Tile*>* tileInLine);
    void checkDirection(int direction1, Location location, std::vector<Tile*>* tileInLine);
    bool checkIfNextToTiles(Location location);

    //bool placeTile(std::vector<std::string> wordsIn, Player *player);
    bool placeTile(const std::string&, const std::string&, Player*);
    bool replaceTile(std::vector<std::string> wordsIn, Player *player);
    bool saveGame(std::vector<std::string> wordsIn, Player *player, Player* player2);

    int convertToRow(char row);
    int convertToCol(char col);

    Tile *turnInputToTile(std::string tiledata);

    Location convertInputLoc(std::string inputLocation);

    int score(Location location);

    void HandPlayerTile(Player* player);

    int scoreDirection(int direction, Location location);
    void handOutBonusPoints();

    private:
    Menu* menu ;
    Board* theBoard;
    Player* player1;
    Player* player2;

};

// tool func for splitting strings
// Splits a string by a character inputted, returns a vector
std::vector<std::string> splitString(const std::string&, const std::string&);


#endif //GAMEPLAY