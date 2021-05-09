#ifndef ASSIGN1_TILECODES_H
#define ASSIGN1_TILECODES_H
#include "Bag.h"
#include "Board.h"
#include "Player.h"

class Action{
Public:
 virtual ~ Action() = default;
 virtual void doAction(Bag* bag, Board* board, Player* player)=0;
 virtual void undoAction(Bag* bag, board* board, Player* player)=0;

 virtual std::string toString() = 0;
};

#endif //