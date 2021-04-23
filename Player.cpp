#include "player.h"
#include <iostream>

Player::Player(std::string name)
{
   this->name = name;
   this->score = 0;
}

Player::~Player()
{

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

// Needs to have play tile etc after bag implemented