#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>

#include "Bag.h"
#include "LinkedList.h"

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
   void addTile(Tile* newTile);
   LinkedList* getHand();

private:
   std::string name;
   int score;
   LinkedList* hand;
};

# endif //PLAYER_H
