#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>

#include "Bag.h"
#include "LinkedList.h"

class Player{
public:
   Player(std::string name);
   ~Player();

   std::string getName();
   
   int getScore();

   void setName(std::string newName);
   void printHand();
   void addTile(Tile* newTile);
   void addScore(int scoreToAdd);

   Tile* getTile();

   LinkedList* getHand();

private:
   std::string name;
   int score;
   LinkedList* hand;
};

# endif //PLAYER_H
