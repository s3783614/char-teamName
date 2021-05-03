#ifndef ASSIGN2_BAG_H
#define ASSIGN2_BAG_H

#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "Tile.h"
#include "LinkedList.h"

class Bag
{
public:
   Bag();
   Bag(Bag& other);
   ~Bag();

   void addToBag(Tile* tile);
   void printBag();
   Tile* getFront();
   void removeFront();

private:
   LinkedList* tiles;

};

#endif //ASSIGN2_BAG_H