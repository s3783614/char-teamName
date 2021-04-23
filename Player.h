#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

class Player{
public:
   Player(std::string name);
   void setName(std::string newName);
   std::string getName();
   void addScore(int scoreToAdd);
   int getScore();
private:
   std::string name;
   int score;
   // Bag pointer for hand(when bag implemented)
};

# endif //PLAYER_H
