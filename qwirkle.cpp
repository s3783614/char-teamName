#include "LinkedList.h"
#include "TileCodes.h"
#include "Tile.h"
#include "Node.h"
#include "Board.h"
#include "Player.h"

#include <iostream>

#define EXIT_SUCCESS    0

int main(void) {
   LinkedList* list = new LinkedList();
   delete list;

   std::cout << "Welcome Qwirkle!" << std::endl;
   std::cout << "----------------" << std::endl;

   return EXIT_SUCCESS;
}
