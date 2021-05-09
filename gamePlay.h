#ifndef GAMEPLAY
#define GAMEPLAY

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <random>

#include "Board.h"
#include "Player.h"




bool check(char *s);
void NewGame();
std::string getName();

void quit();

std::vector<std::string> takeLineInput();
std::vector<Tile *> initialiseTileBag();
bool handingTilesToPlayers(Player *player1, Player *player2, Board *theBoard);
void playingTheGame(Player *player1, Player *player2, Board *theBoard);
void playerMove(Board *theBoard, Player *player, Player* player2);
bool tileInputtedIsOkay(std::string tileString, Player *player);
bool isOnBoard(int row, int col, Board *board);
bool tileFit(Tile *tile, Board *theBoard, Location *loaction);

bool placeTile(std::vector<std::string> wordsIn, Board *theBoard, Player *player);
bool replaceTile(std::vector<std::string> wordsIn, Board *theBoard, Player *player);
bool saveGame(std::vector<std::string> wordsIn, Board *theBoard, Player *player, Player* player2);

int convertToRow(char row);
int convertToCol(char col);

//MOVE LATER
int getRow(int currentRow, int direction);
int getCol(int currentCol, int direction);

Tile *turnInputToTile(std::string tiledata);

Location *convertInputLoc(std::string inputLocation);


#endif //GAMEPLAY