#include "Player.h"
#include <iostream>

Player::Player(std::string name)
{
   this->name = name;
   this->score = 0;
   hand = new Bag();
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
   hand->printBag();
}

Tile* Player::getTile()
{
   // Need updates to bag to implement
   return nullptr;
}

void Player::addTile(Tile* newTile)
{
   hand->addToBag(newTile);
}
