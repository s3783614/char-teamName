#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "Bag.h"
#include <string>

class Player{
public:
   Player(std::string name);
   ~Player();
   void setName(std::string newName);
   std::string getName();
   void addScore(int scoreToAdd);
   int getScore();
   void printHand();
   Tile* getTile();
private:
   std::string name;
   int score;
   Bag* hand;
};

# endif //PLAYER_H
