// #include "Node.h"
#include "LinkedList.h"


#include <iostream>

LinkedList::LinkedList()
{
   // TODO
   head = nullptr;
}

LinkedList::LinkedList(LinkedList &other) : head(other.head)
{
}

LinkedList::~LinkedList()
{
   clear();
}

int LinkedList::size()
{
   int counter = 0;
   Node *current = head;

   while (current != nullptr)
   {
      current = current->next;
      counter++;
   }

   return counter;
}

void LinkedList::clear()
{
   while (head != nullptr)
   {
      removeFront();
   }
}

Tile *LinkedList::get(int index)
{
   int counter = 0;
   Node *current = head;

   Tile *returnTile;

   if (index < size())
   {

      while (counter < index)
      {
         counter++;
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

void LinkedList::addFront(Tile *tile)
{
   Node *addedTile = new Node(tile, nullptr);

   if (head == nullptr)
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

void LinkedList::addBack(Tile *tile)
{
   Node *addedTile = new Node(tile, nullptr);
   // addedTile->tile = tile;
   // addedTile->next = nullptr;

   if (head == nullptr)
   {
      head = addedTile;
   }
   else
   {
      //for head is not null
      Node *temp = head;
      while (temp->next != nullptr)
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
   if (head != nullptr)
   {
      Node *secondaryElement = head->next;
      delete head;
      head = secondaryElement;
   }
}

void LinkedList::removeBack()
{
   if (head != nullptr)
   {
      Node *current = head;
      Node *previous = nullptr;

      while (current->next != nullptr)
      {
         previous = current;
         current = current->next;
      }

      previous->next = nullptr;
      delete current;
   }
}

void LinkedList::removeAt(int index)
{
   std::cout << "size: " <<size()<<std::endl;
   if (index >= 0 && index < size())
   {

      if (head != nullptr)
      {
         int counter = 0;
         Node *current = head;
         Node *previous = nullptr;

         while (counter != index)
         {
            ++counter;
            previous = current;
            current = current->next;
         }

         if (previous == nullptr)
         {
            head = current->next;
         }
         else
         {
            previous->next = current->next;
         }
         delete current->tile;
         delete current;
      }
   }

   //  if (head != nullptr) {
   //      int counter = 0;
   //      std::shared_ptr<Node> current = head;

   //      if (index >=0 && index < size()) {
   //          while (counter < index) {
   //              current = current->next;
   //              counter++;
   //          }

   //          current->prev->next = current->next;
   //          current->next->prev = current->prev;
   //      } else {
   //          throw std::out_of_range("Linked List Delete At - index out of range");
   //      }
   //  }
}

void LinkedList::printLinkedList()
{

   Node *current = head;
   if (current != nullptr)
   {
      do
      {
         current->printNode();
         std::cout << ", ";
         current = current->next;

      } while (current->next != nullptr);
   }
}

Tile *LinkedList::getFront()
{
   Tile *returnTile = nullptr;
   if (head != nullptr)
   {
      returnTile = head->tile;
   }

   return returnTile;
}

bool LinkedList::isInLinkedList(Tile *tile)
{
   bool isIn = false;
   Node *current = head;

   while (current != nullptr)
   {
      if (current->tile->compareTile(tile))
      {
         isIn = true;
      }
      current = current->next;
   }

   return isIn;
}

int LinkedList::findSpecificTile(Tile *tile)
{
   int index = -1;

   Node *current = head;

   int counter = 0;
   while (current != nullptr)
   {
      if (current->tile->compareTile(tile))
      {

         index = counter;
      }
      ++counter;
      current = current->next;
   }

   return index;
}


std::string LinkedList::llToString()
{

   std::string llTiles = "";
   for(int i = 0; i < size(); i++)
   {

      llTiles += get(i)->getColour();
      llTiles += std::to_string(get(i)->getShape());
      if(i != size()-1)
      {
         llTiles += ",";
      }

   }
   return llTiles;
}