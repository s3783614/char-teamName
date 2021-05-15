#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>

#include "LinkedList.h"

class Player{
public:
   Player(std::string name);
   Player(std::string name, int score, LinkedList* hand);
   ~Player();

   std::string getName();
   
   int getScore();

   void setName(std::string newName);
   void printHand();
   void addTile(Tile* newTile);
   void addScore(int scoreToAdd);

   Tile* getTile();

   LinkedList* getHand();

   std::string handToString();

   int getNumber();
   void setNumber(int playerNumber);

private:
   std::string name;
   int score;
   LinkedList* hand;

   int playerNumber;
};

# endif //PLAYER_H
