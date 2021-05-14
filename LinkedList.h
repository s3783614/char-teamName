
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include <string>

#include "Node.h"


class LinkedList {
public:

   LinkedList();
   LinkedList(LinkedList& other);
   ~LinkedList();

   int getSize();
   int findSpecificTile(Tile* tile);

   Tile* getFront();
   Tile* get(int index);

   void clear();
   void addFront(Tile* tile);
   void addBack(Tile* tile);
   void removeFront();
   void removeBack();
   void removeAt(int index);
   
   bool isInLinkedList(Tile* tile);

   std::string llToString();
   void printLL();



private:
   int size;
   Node* head;
};

#endif // ASSIGN2_LINKEDLIST_H
