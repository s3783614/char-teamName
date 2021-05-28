#include <iostream>

#include "Tile.h"

// Tile Constructor takes a colour and shape input
Tile::Tile(Colour colour, Shape shape)
{
    this->colour = colour;
    this->shape = shape;
}

// Empty destructor of Tile
Tile::~Tile() {}

// Copy constructor of the tile.
Tile::Tile(Tile &otherTile) : colour(otherTile.colour),
                              shape(otherTile.shape)
{
}

void Tile::printTile()
{
    std::cout << colour << shape;
}

// Returns the colour of the tile
Colour Tile::getColour()
{
    return colour;
}

// Returns the shape of the tile
Shape Tile::getShape()
{
    
    return shape;
}

// Compares a tile to the current tile
bool Tile::compareTile(Tile *tile)
{
    bool checker = false;
    if (this->getColour() == tile->getColour() && this->getShape() == tile->getShape())
    {
        checker = true;
    }

    return checker;
}

std::string getTileWithColor(Tile* tile) {
   std::string ret;

   switch(tile->getColour()) {
     case RED:
      ret += "\e[31m";
      break;
     case ORANGE:
      ret += "\e[36m"; // we don't have a orange color
      break;
     case YELLOW:
      ret += "\e[33m";
      break;
     case GREEN:
      ret += "\e[32m";
      break;
     case BLUE:
      ret += "\e[34m";
      break;
     case PURPLE:
      ret += "\e[35m";
      break;
   }

   return ret + tile->getColour() + std::to_string(tile->getShape())  + "\e[0m";
}