#include "ActionNode.h"

ActionNode::ActionNode(ActionNode* next, ActionNode* prev, Action* action, PlayerNum player){
    this->action = action;
    this->playerNum = playerNum;
    this->next = next;
    this->prev = prev;
}

ActionNode::~ActionNode(){
    delete action;
}
