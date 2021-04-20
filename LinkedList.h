
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();

   ~LinkedList();

   void addNode(Tile* tile);
   void addBack(Tile* tile);

   int size() const;


private:
   Node* head;
};

#endif // ASSIGN2_LINKEDLIST_H
