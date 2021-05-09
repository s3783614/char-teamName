#include "Player.h"
#include "Board.h"
#include "Tile.h"
#include "GameHistory.h"
#include "ReplaceTileAction.h"
#include "PlaceTileAction.h"
#include <iostream>
#include <fstream>
#define DOWNRIGHT 1
#define DOWNLEFT 2
#define UPRIGHT 3
#define UPLEFT 4


class Controller {
public:

   Controller(Player* one, Player* two, Bag* bag);
   Controller(Player* one, Player* two, Bag* bag, Board* board, GameHistory* history);
   ~Controller();

   bool validPlaceTile(Tile* playedTile, std::string boardLocation, bool firstTile);

   int calcScore(Tile* playedTile, std::string boardLocation);

   bool validReplaceTile(Tile* replacedTile, int playerNum);

   void gameplay(int playerNextTurn);

   void save(std::string filename,int playersTurn);

private:
    GameHistory* gameHistory;

    Player* playerOne;
    Player* playerTwo;
    Board* board;
    Bag* bag;

    void placeTile(PlayerNum playerNum, Tile* playedTile, std::string boardLocation, int score);
    void replaceTile(PlayerNum playerNum, Tile* replacedTile);
    bool tileInHand(PlayerNum playerNum, std::string tileName);
    void displayScoreAndBoard();

    bool bagEmpty();
};