#include <fstream>
#include <iostream>
#include <algorithm> //for std::shuffle

#include "Bag.h"
#include "Tile.h"
#include "TileCodes.h"

Bag::Bag()
{
   this->tiles = new LinkedList();
}

Bag::~Bag()
{
   delete tiles;
}

void Bag::initialiseTileBag()
{

   Colour tileColours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
   Shape tileShapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

   std::vector<Tile *> orderedTiles;

   for (int i = 0; i < 2; i++)
   {
      for (Colour colour : tileColours)
      {
         for (Shape shape : tileShapes)
         {
            Tile *tile = new Tile(colour, shape);
            orderedTiles.push_back(tile);
         }
      }
   }

   shuffleTiles(orderedTiles);
}

void Bag::shuffleTiles(std::vector<Tile *> orderedTiles)
{

   std::shuffle(std::begin(orderedTiles), std::end(orderedTiles), std::default_random_engine());

for (unsigned int i = 0; i < orderedTiles.size(); i++)
{
   Tile *tempTile;
   tempTile = orderedTiles[i];
   tiles->addBack(tempTile);
   delete tempTile;
}
}
