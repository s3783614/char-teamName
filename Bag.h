#ifndef ASSIGN2_BAG_H
#define ASSIGN2_BAG_H

#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "Tile.h"
#include "LinkedList.h"

class Bag /*: public LinkedList*/
{
public:
   Bag();
   Bag(Bag& other);
   ~Bag();

   void addToBag(Tile* tile);
   void printBag();
   Tile* getFront();
   void removeFront();
   bool isInBag(Tile* tile);
   LinkedList getBag();

private:
   LinkedList* tiles;
};

#endif //ASSIGN2_BAG_H