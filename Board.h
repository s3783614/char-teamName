#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H
#include <iostream>
#include <vector>


#include "Tile.h"
#include "LinkedList.h"
#include "TileCodes.h"


#define NO_OF_ROWS   26
#define NO_OF_COLS   26

class Board
{
public:
   Board();
   ~Board();
   void toString();
   void placeTile(Tile* theTile, int Row, int Column);
   LinkedList* getBag();
   bool isSpotTaken(int Row, int Column);
   
   // void setEmpty();S

   bool checkEmpty();

   bool emptyLocation(Location* location);

   Colour checkColour(Location* location);
   Shape checkShape(Location* location);

   bool lineCheck(Location* location, int direction);


private:
   std::vector <std::vector<Tile*> > theBoard;
   LinkedList* bag;
   bool empty;
};

#endif // BOARD_H
