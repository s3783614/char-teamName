#include "Player.h"
#include <iostream>

Player::Player(std::string name)
{
   this->name = name;
   this->score = 0;
   hand = new LinkedList();
}

Player::Player(std::string name, int score, LinkedList* hand)
{
   this->name = name;
   this->score = score;
   this->hand = hand;
}

Player::~Player()
{
   delete hand;
}

// Update the name of a player with a string input
void Player::setName(std::string newName)
{
   this->name = newName;
}

// Return a string of the players name
std::string Player::getName()
{
   return this->name;
}

// Increase the players score by an int input
void Player::addScore(int scoreToAdd)
{
   this->score += scoreToAdd;
}

// Return the score of the player as an int
int Player::getScore()
{
   return this->score;
}

// Print out the players hand
void Player::printHand()
{
   hand->printLinkedList();
}

Tile* Player::getTile()
{
   
   // Need updates to bag to implement
   return nullptr;
}

// void Player::addTile(Tile* newTile)
// {
//    hand->addToBag(newTile);
// }

LinkedList* Player::getHand()
{
   return hand;
}

std::string Player::handToString()
{

   std::string handTiles = "";
   for(int i = 0; i < hand->size(); i++)
   {

      handTiles += hand->get(i)->getColour();
      handTiles += std::to_string(hand->get(i)->getShape());
      if(i != hand->size()-1)
      {
         handTiles += ",";
      }

   }
   return handTiles;
}