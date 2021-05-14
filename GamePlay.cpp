
#include <fstream>
// #include <ofstream>

#include "GamePlay.h"

GamePlay::GamePlay()
{
   
}

GamePlay::~GamePlay()
{

}

bool GamePlay::playerMove(Menu* menu, int playerTurn)
{
   bool tilePlaced = false;
   bool tileReplaced = false;
   bool gameSaved = false;
   bool triedToSaveGame = false;

   bool gameQuit = false;

   Player* player;
   Player* playerTwo;

   if(player1->getNumber() == playerTurn)
   {
      player = player1;
      playerTwo = player2;
   }
   else
   {
      player = player2;
      playerTwo = player1;
   }
   std::cout << player->getName() << " it is your turn" << std::endl;
   std::cout << player->getName() << ". Your hand is: " << std::endl;
   player->getHand()->printLL();
   std::cout << std::endl;
   std::cout << "What would you like to play and where?" << std::endl;

   while (!tileReplaced && !tilePlaced && !gameQuit)
   {
      
      std::vector<std::string> wordsIn = menu->takeLineInput(' ');
      triedToSaveGame = false;

      if (wordsIn.size() == 4 && wordsIn[0] == "Place" && wordsIn[2] == "at")
      {
         tilePlaced = placeTile(wordsIn, theBoard, player);
      }
      else if (wordsIn.size() == 2 && wordsIn[0] == "Replace")
      {
         tileReplaced = replaceTile(wordsIn, theBoard, player);
      }
      else if(wordsIn.size() == 2 && wordsIn[0] == "Save")
      {
         gameSaved = saveGame(wordsIn, theBoard, player, playerTwo);
         std::cout << "Game successfully saved" <<std::endl;
         triedToSaveGame = true;
      }
      else if(wordsIn.size() == 1 && wordsIn[0] == std::to_string(EOF) )
      {
         gameQuit = true;
      }
      
      if(triedToSaveGame && !gameSaved && !gameQuit)
      {
         std::cout << "Failed to save!" << std::endl;
      }

   }

  return gameQuit;
}


// Takes the tile inputted and determines if it is a real tile
// And if the tile is in the players hand
bool GamePlay::tileInputtedIsOkay(std::string tileString, Player *player)
{
   bool isOkay = false;
   char colour = tileString[0];
   int shape = (int)(tileString[1] - 48);

   if (tileString.size() == 2 && shape >= CIRCLE && shape <= CLOVER)
   {
      if (colour == ORANGE || RED || YELLOW || GREEN || BLUE || PURPLE)
      {

         Tile *tile = new Tile(colour, shape);
         if (player->getHand()->isInLinkedList(tile))
         {
            isOkay = true;
         }
         delete tile;
      }
   }
   return isOkay;
}

Tile* GamePlay::turnInputToTile(std::string tiledata)
{
   char colour = tiledata[0];
   int shape = (int)(tiledata[1] - 48);
   Tile *tile = new Tile(colour, shape);
   return tile;
}

//CHANGE LATER --ASCII MAGIC
// check letter is shape and number is Colour
//CHANGE LATER --ASCII MAGIC
Location* GamePlay::convertInputLoc(std::string inputLocation)
{
   Location *location = new Location();
   location->row = (int)inputLocation[0] - 65;

   if (inputLocation.size() == 3)
   {
      int tens = (int)inputLocation[1] - 48;
      int ones = (int)inputLocation[2] - 48 - 1;
      location->col = (10 * tens) + (ones);
   }
   else
   {
      location->col = (int)inputLocation[1] - 48 - 1;
   }
   return location;
}

// Method necessary?
bool GamePlay::isOnBoard(int row, int col, Board *board)
{
   bool onBoard = false;
   if (row < NO_OF_ROWS && row >= 0)
   {
      if (col < NO_OF_COLS && col >= 0)
      {
         onBoard = true;
      }
   }
   return onBoard;
}

bool GamePlay::tileFit(Tile* tile, Board* theBoard, Location location)
{
   bool check = true;

   if (!theBoard->checkEmpty())
   {

      if(checkBothSides(UP, DOWN, location, tile))
      {
         check = false;
      }

      if(checkBothSides(RIGHT, LEFT, location, tile))
      {
         check = false;
      }

   }

   return check;
}

//TODO CHECKLOC
bool GamePlay::placeTile(std::vector<std::string> wordsIn, Board *theBoard, Player *player)
{
   Tile *checkTile = nullptr;

   bool isSpotTaken = true;
   bool acceptableTile = false;
   bool moveMade = false;
   bool locExists = false;
   bool acceptableLoc = false;

   // Check if inputted tile is real and in players hand
   acceptableTile = tileInputtedIsOkay(wordsIn[1], player);
   checkTile = new Tile(wordsIn[1][0], (int)wordsIn[1][1] - 48);

   // Converts inputted location from char to ints of board location
   Location toPlace = convertInputLoc(wordsIn[3]);
   locExists = isOnBoard(toPlace, theBoard);
   // takes correct location and looks for empty position on the Board
   if (locExists)
   {
      isSpotTaken = theBoard->isSpotTaken(toPlace);
      acceptableLoc = tileFit(checkTile, theBoard, toPlace);
   }


   // if player input were correct place the tile, put new tile in players hand
   if (!isSpotTaken && acceptableTile && locExists && acceptableLoc)
   {
      int tileIndex = player->getHand()->findSpecificTile(checkTile);
      player->getHand()->removeAt(tileIndex);
      theBoard->placeTile(checkTile, toPlace->row, toPlace->col);

      // Hand new tile to the player SHOULD BE A METHOD
      HandPlayerTile(player, theBoard);
      player->addScore(score(toPlace, theBoard));
      moveMade = true;
      delete toPlace;
      
   }
   else
   {
      std::cout << std::endl;
      std::cout << "Tile cannot be placed there!" << std::endl;
   }
   return moveMade;
}

bool GamePlay::replaceTile(std::vector<std::string> wordsIn, Board *theBoard, Player *player)
{
   bool rtnReplaced = false;

   bool tileInputInHand = tileInputtedIsOkay(wordsIn[1], player);

   if (tileInputInHand && theBoard->getBag()->getSize() != 0)
   {

      Tile *checkTile = turnInputToTile(wordsIn[1]);
      int tileIndex = player->getHand()->findSpecificTile(checkTile);
      Tile *playersTile = player->getHand()->get(tileIndex);
      player->getHand()->removeAt(tileIndex);
      theBoard->getBag()->addBack(playersTile);

      HandPlayerTile(player, theBoard);

      rtnReplaced = true;
   }
   else
   {
      std::cout << "The bag is empty!" <<std::endl;
   }

   return rtnReplaced;
}

bool GamePlay::checkBothSides(int direction1, int direction2, Location location, Tile* tile)
{
   Location checkLocation;
   bool check = false;
   checkLocation.row = location.getNextRow(location.row, direction1);
   checkLocation.col = location.getNextCol(location.col, direction1);

   std::vector<Tile*>* tileInLine = new std::vector<Tile*>();
   tileInLine->push_back(tile);
   checkDirection(direction1, location, tileInLine);
   checkDirection(direction2, location, tileInLine);
   check = compareTiles(tileInLine);

   for (long unsigned int i = 0; i< tileInLine->size(); i++)
   {
      tileInLine->pop_back();
   }
   delete tileInLine;

   return check;
}

void GamePlay::checkDirection(int direction1, Location location, std::vector<Tile*>* tileInLine)
{
   Location checkLocation;
   checkLocation.row = location.getNextRow(location.row, direction1);
   checkLocation.col = location.getNextCol(location.col, direction1);

   bool empty = false;
   while(!empty)
   {
      if (checkLocation.row >=0 && checkLocation.row < NO_OF_ROWS &&
            checkLocation.col >=0 && checkLocation.col < NO_OF_COLS)
      {
         if(!theBoard->emptyLocation(checkLocation))
         {
            theBoard->getTile(checkLocation->row,checkLocation->col);
            tileInLine->push_back(theBoard->getTile(checkLocation->row,checkLocation->col));

            checkLocation->row = checkLocation->getNextRow(checkLocation->row, direction1);
            checkLocation->col = checkLocation->getNextCol(checkLocation->col, direction1);
         }
         else 
         {
            empty = true;
         }
      }
   }
}

bool GamePlay::compareTiles(std::vector<Tile*>* tileInLine)
{
   bool match = false;
   for(long unsigned int i = 0; i < tileInLine->size(); i++)
   {
      for(long unsigned int j = i + 1; j < tileInLine->size(); j++)
      {
         if(tileInLine->at(i)->compareTile(tileInLine->at(j)))
         {
            match = true;
         }
      }
   }

   return match;
}



void GamePlay::HandPlayerTile(Player* player, Board* theBoard)
{
   if (theBoard->getBag()->getSize() != 0)
   {
      Tile *tmpTile = theBoard->getBag()->getFront();
      theBoard->getBag()->removeFront();
      player->getHand()->addBack(tmpTile);
   }
}

bool GamePlay::saveGame(std::vector<std::string> wordsIn, Board *theBoard, Player *player, Player* player2)
{

bool saveCheck = false;
   std::string fileExtension = ".save";
   std::string fileName = wordsIn[1];

   fileName = fileName.append(fileExtension);
   // std::cout << fileName <<std::endl;
   
   std::ofstream MyFile(fileName);
   if(!MyFile.fail())
   {
      if(player->getNumber() == 1)
      {
         MyFile << player->getName() << std::endl;
         MyFile << player->getScore() << std::endl;
         MyFile << player->getHand()->llToString() << std::endl;
         MyFile << player2->getName() << std::endl;
         MyFile << player2->getScore() << std::endl;
         MyFile << player2->getHand()->llToString() << std::endl;
      }
      else
      {
         MyFile << player2->getName() << std::endl;
         MyFile << player2->getScore() << std::endl;
         MyFile << player2->getHand()->llToString() << std::endl;
         MyFile << player->getName() << std::endl;
         MyFile << player->getScore() << std::endl;
         MyFile << player->getHand()->llToString() << std::endl;

      }

      MyFile << NO_OF_ROWS << ",";
      MyFile << NO_OF_COLS <<std::endl;

      MyFile << theBoard->saveBoard() <<std::endl;
      MyFile << theBoard->getBag()->llToString() <<std::endl;
      MyFile << player->getName() << std::endl;

      saveCheck = true;
      
   }
   MyFile.close();

   
   return saveCheck;
}

int GamePlay::score(Location* location, Board* theBoard)
{
   int score  = 0;
   Location* nextLocation = new Location();

   
   for (int direction = UP; direction <= RIGHT; direction++)
   {
      
      nextLocation->row = location->row;
      nextLocation->col = location->col;
      
      int counter = 0;
      counter += scoreDirection(direction, nextLocation);
      nextLocation->row = location->row;
      nextLocation->col = location->col;
      if (direction == UP)
      {
         counter +=scoreDirection(DOWN, nextLocation);
      }
      nextLocation->row = location->row;
      nextLocation->col = location->col;
      if (direction == RIGHT)
      {
         counter += scoreDirection(LEFT, nextLocation);
      }
      if (counter != 0)
      {
         counter ++;
      }
      if(counter == 6)
      {
         std::cout << std::endl;
         std::cout << "QWIRKLE!!!" <<std::endl;

         counter += 6;
      }

      score += counter;

   }

   if (score == 0)
   {
      score ++;
   }
   
   return score;
}

int GamePlay::scoreDirection(int direction, Location* location)
{
   bool Empty = false;
   int score = 0;
   while(!Empty)
   {
      location->col = location->getNextCol(location->col, direction);
      location->row = location->getNextRow(location->row, direction);
      if((location->col > 0) && (location->row > 0) && (location->col < theBoard->getCols()) && (location->row < theBoard->getRows()))
      {
         Empty = theBoard->emptyLocation(location);
         if (!Empty)
         {
            score++;
         }
      }
      else
      {
         Empty = true;
      }
   }

   return score;
}

void GamePlay::setPlayer(Player* player)
{
   if(player->getNumber() == 1)
   {
      this->player1 = player;
   }
   else
   {
      this->player2 = player;
   }
}

void GamePlay::setBoard(Board* board)
{
   theBoard = board;
}
