#ifndef ASSIGN1_TILECODES_H
#define ASSIGN1_TILECODES_H
#include "Action.h"
#typedef int PlayerNum;

class ActionNode{
    public;
    ActionNode(ActionNode* next,ActionNode* prev, Action* action, PlayerNum playerNum);
    ~ActionNode();

    ActionNode* next;
    ActionNode* prev;
    Action* action;
    PlayerNum playerNum;
};
    endif // ASSIGN2_ACTIONNNODE_H
