#ifndef ASSIGN2_BAG_H
#define ASSIGN2_BAG_H

#include <iostream>
#include <string>

#include "Tile.h"

#define MAX_COLOURS     6
#define MAX_SHAPES      6
#define MAX_TILES       (MAX_COLOURS * MAX_SHAPES)

class Bag{
public:
    Bag();

    void readAllTiles(std::string inputFileName, Tile* tileBag[]);
    bool readColourTile(std::ifstream& inputFile, Colour* colour, Shape* shape);
    bool readShapeTile(std::ifstream& inputFile, Colour* colour, Shape* shape);

private:
    Tile* tileBag[MAX_TILES];
    Colour* colour;
    Shape* shape;
};

#endif //ASSIGN2_BAG_H