
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include "TileCodes.h"

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   Tile(Colour colour, Shape shape);
   ~Tile();
   Tile(Tile& otherTile);

   void printTile();

   Colour getColour();
   Shape getShape();

   bool compareTile(Tile* tile);
   
private:
   Colour colour;
   Shape  shape;
};

std::string getTileWithColor(Tile* tile);

#endif // ASSIGN2_TILE_H
