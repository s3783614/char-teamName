#include "LinkedList.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <random>

#include "Board.h"
#include "Player.h"



#define EXIT_SUCCESS 0

//Possibly move to a header file

bool check(char *s);
void NewGame();
std::string getName();

void menu();
void quit();
void credits();

std::vector<std::string> takeLineInput();
std::vector<Tile *> initialiseTileBag();
bool handingTilesToPlayers(Player *player1, Player *player2, Board *theBoard);
void playingTheGame(Player *player1, Player *player2, Board *theBoard);
void playerMove(Board *theBoard, Player *player);
bool tileInputtedIsOkay(std::string tileString, Player *player);
bool isOnBoard(int row, int col, Board *board);
bool tileFit(Tile *tile, Board *theBoard, Location *loaction);

bool placeTile(std::vector<std::string> wordsIn, Board *theBoard, Player *player);
bool replaceTile(std::vector<std::string> wordsIn, Board *theBoard, Player *player);

int convertToRow(char row);
int convertToCol(char col);


//MOVE LATER
int getRow(int currentRow, int direction);
int getCol(int currentCol, int direction);

Tile *turnInputToTile(std::string tiledata);

Location *convertInputLoc(std::string inputLocation);

int main(void)
{
   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;

   std::vector<std::string> userString;
   std::string userInput = "";

   while (true)
   {
      menu();

      userString = takeLineInput();

      // Check only one word was inputted,
      if (userString.size() == 1)
      {
         // set the one word to the menu choice
         userInput = userString[0];
      }

      if (userInput == "1")
      {
         NewGame();
      }
      else if (userInput == "2")
      {
      }
      else if (userInput == "3")
      {
         credits();
      }
      else if (userInput == "4")
      {
         quit();
      }
      else
      {
         std::cout << "Invalid Input!" << std::endl;
      }
   }
   return EXIT_SUCCESS;
}

void menu()
{
   std::cout << std::endl;
   std::cout << "Menu" << std::endl;
   std::cout << "----" << std::endl;
   std::cout << "1. New Game" << std::endl;
   std::cout << "2. Load Game" << std::endl;
   std::cout << "3. Credits (Show student information)" << std::endl;
   std::cout << "4. Quit" << std::endl;
   std::cout << std::endl;
}

void credits()
{
   std::cout << "CREDITS" << std::endl;
   std::cout << "-------" << std::endl;
}

// Quits the program
// NEED TO CHECK IF THIS IS OKAY OR WHETHER WE NEED TO GO BACK TO MAIN SOME HOW
void quit()
{
   std::cout << "Goodbye" << std::endl;
   exit(EXIT_SUCCESS);
}

void NewGame()
{
   std::string name1 = "";
   std::string name2 = "";

   std::cout << std::endl;
   std::cout << "Starting a New Game" << std::endl
             << std::endl;
   std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
   name1 = getName();
   Player *player1 = new Player(name1);

   std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
   std::cout << ">";
   name2 = getName();
   Player *player2 = new Player(name2);

   Board *board = new Board();

   std::vector<Tile *> tPtrs = initialiseTileBag();
   for (Tile *tile : tPtrs)
   {
      board->getBag()->addFront(tile);
   }

   handingTilesToPlayers(player1, player2, board);

   playingTheGame(player1, player2, board);

}

void playingTheGame(Player *player1, Player *player2, Board *theBoard)
{
   int i = 0;
   while (i != 6)
   {
      theBoard->toString();
      std::cout << player1->getName() << "'s score: " << player1->getScore() << std::endl;
      std::cout << player2->getName() << "'s score: " << player2->getScore() << std::endl;
      playerMove(theBoard, player1);

      theBoard->toString();

      std::cout << std::endl;
      std::cout << player1->getName() << "'s score: " << player1->getScore() << std::endl;
      std::cout << player2->getName() << "'s score: " << player2->getScore() << std::endl;
      playerMove(theBoard, player2);

      ++i;
   }
}

void playerMove(Board *theBoard, Player *player)
{
   bool tilePlaced = false;
   bool tileReplaced = false;

   std::cout << player->getName() << " it is your turn" << std::endl;
   std::cout << player->getName() << ". Your hand is: " << std::endl;
   player->printHand();
   std::cout << std::endl;
   std::cout << "What would you like to play and where?" << std::endl;
   while (!tileReplaced && !tilePlaced)
   {
      std::vector<std::string> wordsIn = takeLineInput();

      std::cout << wordsIn.size() << wordsIn[0] << std::endl;

      if (wordsIn.size() == 4 && wordsIn[0] == "Place" && wordsIn[2] == "at")
      {

         tilePlaced = placeTile(wordsIn, theBoard, player);
      }
      else if (wordsIn.size() == 2 && wordsIn[0] == "Replace")
      {
         tileReplaced = replaceTile(wordsIn, theBoard, player);
      }

      if (tilePlaced == false && tileReplaced == false)
      {
         std::cout << std::endl;
         std::cout << "That is not a legal move" << std::endl;
         std::cout << "Please input a different move in the form:" << std::endl;
         std::cout << "> Place 'Tile' at 'location'" << std::endl;
      }

   }
   //TODO
   /*Caluculate score method
   */
}
// Takes the tile inputted and determines if it is a real tile
// And if the tile is in the players hand
bool tileInputtedIsOkay(std::string tileString, Player *player)
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

Tile *turnInputToTile(std::string tiledata)
{
   char colour = tiledata[0];
   int shape = (int)(tiledata[1] - 48);
   Tile *tile = new Tile(colour, shape);
   return tile;
}

//CHANGE LATER --ASCII MAGIC
// check letter is shape and number is Colour
//CHANGE LATER --ASCII MAGIC
Location *convertInputLoc(std::string inputLocation)
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

std::string getName()
{
   std::vector<std::string> wordsIn;
   std::string name;

   bool checker = false;

   while (checker == false)
   {
      checker = true;
      std::cout << "Enter your name (ONLY CAPITALS AND NO SPACES)" << std::endl;
      wordsIn = takeLineInput();

      // Check only one word inputted
      if (wordsIn.size() == 1)
      {
         name = wordsIn[0];

         for (unsigned int i = 0; i < name.length(); i++)
         {

            if (name[i] < 65 || name[i] > 90)
            {
               checker = false;
            }
         }
         if (checker == false)
         {
            std::cout << "Invalid Input!" << std::endl;
            std::cout << "Please enter ONLY CAPITAL LETTERS!" << std::endl;
            std::cout << std::endl;
         }
      }
      else
      {
         checker = false;
         std::cout << "Invalid Input!" << std::endl;
         std::cout << "Please enter only one name!" << std::endl;
         std::cout << std::endl;
      }
   }
   return name;
}

bool isOnBoard(int row, int col, Board *board)
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

std::vector<Tile *> initialiseTileBag()
{

   Colour tileColours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
   Shape tileShapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

   std::vector<Tile *> orderedTiles;

   for (int i = 0; i < 2; i++)
   {
      for (Colour colour : tileColours)
      {
         for (Shape shape : tileShapes)
         {
            Tile *tile = new Tile(colour, shape);
            orderedTiles.push_back(tile);
         }
      }
   }

   std::shuffle(std::begin(orderedTiles), std::end(orderedTiles), std::default_random_engine());

   return orderedTiles;
   // shuffleTiles(orderedTiles);
}

// Takes in players and the board
// Takes tiles and alternatively hands to each player
// Each player is handed 6 tiles which are removed from the bag
// Returns void, as passed by reference
bool handingTilesToPlayers(Player *player1, Player *player2, Board *theBoard)
{
   bool success = false;
   Tile *theTile;
   if (theBoard->getBag()->size() >= 12)
   {
      for (int i = 0; i <= 6; i++)
      {
         theTile = theBoard->getBag()->getFront();
         player1->getHand()->addFront(theTile);
         theBoard->getBag()->removeFront();
         theTile = theBoard->getBag()->getFront();
         player2->getHand()->addFront(theTile);
         theBoard->getBag()->removeFront();
      }
      success = true;
   }
   return success;
}

// Asks the User for an Input and takes an entire line with spaces
// Splits the input to individual words by spaces
// Puts each word in order into a vector
// Returns the vector
std::vector<std::string> takeLineInput()
{
   std::vector<std::string> wordsIn;
   std::string theMove = "";

   std::cout << ">";
   std::getline(std::cin, theMove);

   // Check that eof character not inputted
   if (!std::cin.eof())
   {
      // Take the line inputted and split by spaces to individual words
      std::stringstream check1(theMove);
      std::string tmpString = "";
      while (getline(check1, tmpString, ' '))
      {
         wordsIn.push_back(tmpString);
      }
   }
   else
   {
      quit();
   }
   return wordsIn;
}

bool tileFit(Tile *tile, Board *theBoard, Location *location)
{
   bool check = true;
   bool match = false;
   Location *checkLocation = new Location(location->row, location->col);
   std::cout << "theBoard->checkEmpty() : " << theBoard->checkEmpty() << std::endl;
   if (!theBoard->checkEmpty())
   {
      for (int direction = UP; direction <= LEFT; direction++)
      {
         checkLocation->row = getRow(location->row, direction);
         checkLocation->col = getCol(location->col, direction);

         if (!theBoard->emptyLocation(checkLocation))
         {
            if (!((tile->getColour() == theBoard->checkColour(checkLocation)) || (tile->getShape() == theBoard->checkShape(checkLocation))) )
            {
               check = false;
            }
            else
            {
               match = true;
            }
         }
      }

      if(!match)
      {
         check = false;
      }

   }

   return check;
}

//TODO CHECKLOC
bool placeTile(std::vector<std::string> wordsIn, Board *theBoard, Player *player)
{
   Tile *checkTile = nullptr;

   bool isSpotTaken;
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
      // theBoard->toString();
      // Hand new tile to the player SHOULD BE A METHOD
      Tile *tmpTile = theBoard->getBag()->getFront();
      theBoard->getBag()->removeFront();
      player->getHand()->addBack(tmpTile);
      moveMade = true;
      delete toPlace;
   
   }

   return moveMade;
}

bool replaceTile(std::vector<std::string> wordsIn, Board *theBoard, Player *player)
{
   bool rtnReplaced = false;
   std::cout << "in Loop" << std::endl;
   bool tileInputInHand = tileInputtedIsOkay(wordsIn[1], player);

   if (tileInputInHand)
   {
      std::cout << "in Loop" << std::endl;
      Tile *checkTile = turnInputToTile(wordsIn[1]);
      int tileIndex = player->getHand()->findSpecificTile(checkTile);
      Tile *playersTile = player->getHand()->get(tileIndex);
      player->getHand()->removeAt(tileIndex);

      theBoard->getBag()->addBack(playersTile);
      Tile *tmpTile = theBoard->getBag()->getFront();
      theBoard->getBag()->removeFront();
      player->getHand()->addBack(tmpTile);
      rtnReplaced = true;
   }

   return rtnReplaced;
}





int getRow(int currentRow, int direction)
{
   int rtnRow = currentRow;
   if(direction == UP)
   {
      rtnRow = currentRow - 1;
   }
   else if(direction == DOWN) 
   {
      rtnRow = currentRow + 1;
   }
   
   return rtnRow;
}


int getCol(int currentCol, int direction)
{
   int rtnCol = currentCol;
   if(direction == LEFT)
   {
      rtnCol = currentCol - 1;
   }
   else if(direction == RIGHT) 
   {
      rtnCol = currentCol + 1;
   }
   
   return rtnCol;
}
//TODO
//SCORING