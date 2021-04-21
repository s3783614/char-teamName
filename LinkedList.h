
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   LinkedList(LinkedList& other);
   ~LinkedList();

   int size();
   void clear();
   Tile* get(int index);

   void addFront(Tile* tile);
   void addBack(Tile* tile);
   void removeFront();
   void removeBack();


private:
   Node* head;
};

#endif // ASSIGN2_LINKEDLIST_H
