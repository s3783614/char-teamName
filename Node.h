
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include <iostream>

#include "Tile.h"

class Node {
public:
   Node();
   Node(Tile* tile, Node* next);
   Node(Node& other);
   
   void printNode();

   Tile*    tile;
   Node*    next;
};

#endif // ASSIGN2_NODE_H
