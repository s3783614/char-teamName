// #include "Node.h"
#include "LinkedList.h"
#include "TileCodes.h"

#include <iostream>

LinkedList::LinkedList() {
   // TODO
   head = nullptr;
}

LinkedList::LinkedList(LinkedList& other):
   head(other.head)
{ }

LinkedList::~LinkedList() 
{
   clear();
}

int LinkedList::size()
{
   int counter = 0;
   Node* current = head;

   while(current != head)
   {
      current = current->next;
      counter++;
   }

   return counter;
}

void LinkedList::clear()
{
   while(head != nullptr)
   {
      removeFront();
   }
}

Tile* LinkedList::get(int index)
{
   int counter = 0;
   Node* current = head;

   Tile* returnTile;

   if(index < size())
   {

      while(counter < index)
      {
         counter ++;
         current = current->next;
      }
      returnTile = current->tile;
   }
   else
   {
      throw std::out_of_range("Linked list get - Index out of range");
   }

   return returnTile;
}

void LinkedList::addFront(Tile* tile)
{
   Node* addedTile = new Node(tile, nullptr);

   if(head == nullptr)
   {
      head = addedTile;
   }
   else
   {
      addedTile->next = head;
      // reassign the head position to the added tile
      head = addedTile;
   }
}

void LinkedList::addBack(Tile* tile)
{
   Node* addedTile = new Node(tile, nullptr);
   // addedTile->tile = tile;
   // addedTile->next = nullptr;

   if(head == nullptr)
   {
      head = addedTile;
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
      //add the addedTile to the end of the list
      temp->next = addedTile;
   }
}

void LinkedList::removeFront()
{
   if(head != nullptr)
   {
      Node* secondaryElement = head->next;
      delete head;
      head = secondaryElement;
   }
}

void LinkedList::removeBack()
{
   if(head != nullptr)
   {
      Node* current = head;
      Node* previous = nullptr;

      while(current->next != nullptr)
      {
         previous = current;
         current = current->next;
      }

      previous->next = nullptr;
      delete current;
   }
}

void LinkedList::printLinkedList()
{
   
   Node* current = head;

   while(current->next != nullptr)
   {
      current->printNode();
      current = current->next;
      
   }

   
}

Tile* LinkedList::getFront(Bag* bag)
{
   Tile* returnTile =  nullptr;
   if (head != nullptr)
   {
      returnTile = head->tile;
   }

   return returnTile;
}




