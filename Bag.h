#ifndef ASSIGN2_BAG_H
#define ASSIGN2_BAG_H

#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "Tile.h"
#include "LinkedList.h"

// #define MAX_COLOURS     6
// #define MAX_SHAPES      6
// #define MAX_TILES       (MAX_COLOURS * MAX_SHAPES)

class Bag
{
public:
   Bag();
   ~Bag();

   void initialiseTileBag();
   void shuffleTiles(std::vector<Tile *> orderedTiles);

private:
   LinkedList *tiles;

   Colour *colour;
   Shape *shape;
};

#endif //ASSIGN2_BAG_H