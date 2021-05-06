#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H
#include <iostream>
#include <vector>
#include "Tile.h"
#include "LinkedList.h"

class Board
{
public:
   Board();
   ~Board();
   void toString();
   void placeTile(Tile* theTile, int row, int column);
   LinkedList* getBag();
   bool isSpotTaken(int row, int col);
   
private:
   std::vector <std::vector<Tile*> > theBoard;
   LinkedList* bag;
};

#endif // BOARD_H
