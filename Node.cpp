
#include "Node.h"
#include <iostream>

Node::Node(){
   this->tile = nullptr;
   this->next = nullptr;
}


Node::Node(Tile* tile, Node* next)
{
   // TODO
   this->tile = tile;
   this->next = next;
}

//Returns shallow copy for now
Node::Node(Node& other):
   tile(other.tile),
   next(other.next)
{
   // TODO - deep copy(i think)
   // tile = other.tile;
   // next = other.next;
}

void Node::printNode()
{
   tile->printTile();
}
