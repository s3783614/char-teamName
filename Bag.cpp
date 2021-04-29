#include <fstream>
#include <iostream>
#include <algorithm> //for std::shuffle

#include "Bag.h"
#include "Tile.h"
#include "TileCodes.h"


Bag::Bag()
{
   tiles = new LinkedList();
}


Bag::~Bag()
{
   delete tiles;
}


Bag::Bag(Bag& other)
{
   tiles = new LinkedList(*other.tiles);
}


void Bag::addToBag(Tile* tile)
{
   tiles->addBack(tile);
}


void Bag::printBag()
{
   tiles->printLinkedList();
}
