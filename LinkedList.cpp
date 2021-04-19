// #include "Node.h"
#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {
   // TODO
   // head = nullptr;

   head = NULL;

   // Node* node = new Node();
   
   // this->head = node;

}

LinkedList::~LinkedList() {
}

void LinkedList::addNode(Tile* tile){

   Node* newNode = new Node();
   newNode->tile = tile;
   newNode->next = NULL;

   if(head == NULL)
   {
      head = newNode;
   }
   else
   {
      //for head is not null
      Node* temp = head;
      while(temp->next != NULL)
      {
         //traverses to the end of the list
         temp = temp->next;
      }
      //add the newNode to the end of the list
      temp->next = newNode;
   }


}

//IGNORE FOR NOW 
/*void LinkedList::addBack(Tile* tile){
   Node* newNode = new Node(tile, nullptr);

   Node* cur = this->head;

   bool isEmpty = false;
   //if the list is empty
   if(this->head == nullptr)
   {
      head = newNode;
      isEmpty = true;
   }

   
   while()

}*/

