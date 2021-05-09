
#include <fstream>
// #include <ofstream>

#include "GamePlay.h"

GamePlay::GamePlay()
{
   
}


bool GamePlay::playerMove(Board *theBoard, Player *player, Player* player2,Menu* menu)
{
   bool tilePlaced = false;
   bool tileReplaced = false;
   bool gameSaved = false;
   bool triedToSaveGame = false;

   bool gameQuit = false;

   std::cout << player->getName() << " it is your turn" << std::endl;
   std::cout << player->getName() << ". Your hand is: " << std::endl;
   player->printHand();
   std::cout << std::endl;
   std::cout << "What would you like to play and where?" << std::endl;

   while (!tileReplaced && !tilePlaced && !gameQuit )
   {
      
      std::vector<std::string> wordsIn = menu->takeLineInput();
      triedToSaveGame = false;
      // std::cout << wordsIn.size() << wordsIn[0] << std::endl;

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
         gameSaved = saveGame(wordsIn, theBoard, player, player2);
         std::cout << "Game successfully saved" <<std::endl;
         triedToSaveGame = true;
      }
      else if(wordsIn.size() == 1 && wordsIn[0] == "Quit" )
      {
         gameQuit = true;
      }
      
      if(triedToSaveGame && !gameSaved && !gameQuit)
      {
         std::cout << "Failed to save!" << std::endl;
      }
      else if(tilePlaced == false && tileReplaced == false && !triedToSaveGame && !gameQuit)
      {
         std::cout << std::endl;
         std::cout << "That is not a legal move" << std::endl;
         std::cout << "Please input a different move in the form:" << std::endl;
         std::cout << "> Place 'Tile' at 'location'" << std::endl;
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

bool GamePlay::tileFit(Tile* tile, Board* theBoard, Location* location)
{
   bool check = true;
   bool doesFit = false;

   Location *checkLocation = new Location(location->row, location->col);

   if (!theBoard->checkEmpty())
   {
    
      for (int direction = UP; direction <= LEFT; direction++)
      {
         
         checkLocation->row = location->getNextRow(location->row, direction);
   
         checkLocation->col = location->getNextCol(location->col, direction);
         if (checkLocation->row >=0 && checkLocation-> row < NO_OF_ROWS &&
         checkLocation->col >=0 && checkLocation->col < NO_OF_COLS)
         {
            if (!(theBoard->emptyLocation(checkLocation)))
            {
               if (!(tile->getColour() == theBoard->checkColour(checkLocation) || tile->getShape() == theBoard->checkShape(checkLocation)))
               {
                  check = false; 
               }
               // Get to here is colour or shape matches
               else if (!theBoard->lineCheck(location, direction, tile))
               {
                  check = false;
               }
               else if(tile->getColour() == theBoard->checkColour(checkLocation) || tile->getShape() == theBoard->checkShape(checkLocation))
               {
                  doesFit = true;
               }

            }
         }
      }

      if(doesFit == false)
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
   Location *toPlace = convertInputLoc(wordsIn[3]);
   locExists = isOnBoard(toPlace->row, toPlace->col, theBoard);
   // takes correct location and looks for empty position on the Board
   if (locExists)
   {
      isSpotTaken = theBoard->isSpotTaken(toPlace->row, toPlace->col);
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
   return moveMade;
}

bool GamePlay::replaceTile(std::vector<std::string> wordsIn, Board *theBoard, Player *player)
{
   bool rtnReplaced = false;
   // std::cout << "in Loop" << std::endl;
   bool tileInputInHand = tileInputtedIsOkay(wordsIn[1], player);

   if (tileInputInHand)
   {
      // std::cout << "in Loop" << std::endl;
      Tile *checkTile = turnInputToTile(wordsIn[1]);
      int tileIndex = player->getHand()->findSpecificTile(checkTile);
      Tile *playersTile = player->getHand()->get(tileIndex);
      player->getHand()->removeAt(tileIndex);
      theBoard->getBag()->addBack(playersTile);

      HandPlayerTile(player, theBoard);

      rtnReplaced = true;
   }

   return rtnReplaced;
}

void GamePlay::HandPlayerTile(Player* player, Board* theBoard)
{
   if (theBoard->getBag()->size() != 0)
   {
      Tile *tmpTile = theBoard->getBag()->getFront();
      theBoard->getBag()->removeFront();
      player->getHand()->addBack(tmpTile);
   }
}

bool GamePlay::saveGame(std::vector<std::string> wordsIn, Board *theBoard, Player *player, Player* player2)
{

bool saveCheck = false;
   std::string fileExtension = ".txt";
   std::string fileName = wordsIn[1];
   // std::ofstream outfile;
   fileName = fileName.append(fileExtension);
   std::cout << fileName <<std::endl;
   
   std::ofstream MyFile(fileName);
   if(!MyFile.fail())
   {
      MyFile << player->getName() << std::endl;
      MyFile << player->getScore() << std::endl;
      MyFile << player->getHand()->llToString() << std::endl;
      MyFile << player2->getName() << std::endl;
      MyFile << player2->getScore() << std::endl;
      MyFile << player2->getHand()->llToString() << std::endl;

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
   int score  = 1;
   Location* nextLocation = new Location();
   bool Empty = false;
   std::cout << "spot 1" <<std::endl;
   for (int direction = UP; direction <= LEFT; direction++)
   {
      nextLocation->row = location->row;
      nextLocation->col = location->col;
      int counter = 0;
      std::cout << "spot 2" <<std::endl;
      Empty = false;
      while(!Empty) 
         // theBoard->emptyLocation([nextLocation->getNextCol(nextLocation->col,direction)][nextLocation->getNextRow(nextLocation->row,direction)]) != nullptr )
      {

         nextLocation->col = nextLocation->getNextCol(nextLocation->col, direction);
         nextLocation->row = nextLocation->getNextRow(nextLocation->row, direction);
         Empty = theBoard->emptyLocation(nextLocation);
         if (!Empty)
         {
            counter++;
            score++;
         }
         
      }
      if(counter == 6)
      {
         std::cout << std::endl;
         std::cout << "QWIRKLE!!!" <<std::endl;
      }
      

   }
   return score;
}