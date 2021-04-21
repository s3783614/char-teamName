
#include "Tile.h"

// Tile Constructor takes a colour and shape input
Tile::Tile(Colour colour, Shape shape)
{
    this->colour = colour;
    this->shape = shape;
}

// Empty destructor of Tile
Tile::~Tile(){}

// Copy constructor of the tile. 
Tile::Tile(Tile& otherTile):
   colour(otherTile.colour),
   shape(otherTile.shape)
{
    this->colour = colour;
    this->shape = shape;
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
