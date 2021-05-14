#include <iostream>
#include <fstream>

#include "GamePlay.h"
#include "Menu.h"
#include "LinkedList.h"

#define EXIT_SUCCESS 0

void menu();

void credits();
bool NewGame(Menu *menu, GamePlay *gameTime);
bool LoadGame(Menu* menu);
std::vector<Tile *> initialiseTileBag();
bool handingTilesToPlayers(Player *player1, Player *player2, Board *theBoard);
bool playingTheGame(Player *player1, Player *player2, Board *theBoard, GamePlay *gameTime, Menu *theMenu);
Player* loadInPlayer(std::ifstream& saveFile, Menu* menu);
Board* loadInBoard(std::ifstream& saveFile, Menu* menu);
std::vector<std::string> splitString(std::string string, std::string delim);
bool onePlayerTurn(Board* theBoard, Player* currentPlayer, Player* otherPlayer, GamePlay* gameTime, Menu* theMenu);

int main(void)
{
   bool quit = false;
   Menu *theMenu = new Menu();
   GamePlay *gameTime = new GamePlay();

   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;

   std::vector<std::string> userString;
   std::string userInput = "";

   while (!quit)
   {
      theMenu->printMenu();

      userString = theMenu->takeLineInput(' ');
      if (userString.size() == 1 && userString[0] != std::to_string(EOF))
      {
         if (userString.size() == 1)
         {
            // set the one word to the menu choice
            userInput = userString[0];
         }

         if (userInput == "1")
         {
            quit = NewGame(theMenu, gameTime);
         }
         else if (userInput == "2")
         {
            quit = LoadGame(theMenu);
         }
         else if (userInput == "3")
         {
            theMenu->printCredits();
         }
         else if (userInput == "4")
         {
            quit = true;
         }
         else
         {
            std::cout << "Invalid Input!" << std::endl;
         }
      }
      else
      {
         quit = true;
      }
   }
   delete gameTime;
   delete theMenu;
   std::cout << "GoodBye!" << std::endl;
   return EXIT_SUCCESS;
}

bool NewGame(Menu *menu, GamePlay *gameTime)
{
   bool gameQuit = false;
   std::string name1 = "";
   std::string name2 = "";

   std::cout << std::endl;
   std::cout << "Starting a New Game" << std::endl
             << std::endl;
   std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
   name1 = menu->getName();
   if (name1 != std::to_string(EOF))
   {
      Player *player1 = new Player(name1);
      player1->setNumber(1);
      std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
      std::cout << ">";
      name2 = menu->getName();
      if (name2 != std::to_string(EOF))
      {
         Player *player2 = new Player(name2);
         player2->setNumber(2);

         Board *board = new Board();

         std::vector<Tile *> tPtrs = initialiseTileBag();
         for (Tile *tile : tPtrs)
         {
            board->getBag()->addFront(tile);
         }
         
         handingTilesToPlayers(player1, player2, board);
         gameTime->setPlayer(player1);
         gameTime->setPlayer(player2);
         gameTime->setBoard(board);
         gameQuit = playingTheGame(player1, player2, board, gameTime, menu);
      }
      else
      {
         gameQuit = true;
      }
   }
   else
   {
      gameQuit = true;
   }

   return gameQuit;
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

bool handingTilesToPlayers(Player *player1, Player *player2, Board *theBoard)
{
   bool success = false;
   Tile *theTile;
   if (theBoard->getBag()->getSize() >= 12)
   {
      for (int i = 0; i < 6; i++)
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

bool playingTheGame(Player *player1, Player *player2, Board *theBoard, GamePlay *gameTime, Menu *theMenu)
{
   bool quit = false;
   int i = 0;

   while (player1->getHand()->getSize() != 0 && player2->getHand()->getSize() != 0 && !quit)
   {
      
      quit = onePlayerTurn(theBoard, player1, player2,gameTime, theMenu);
      if (quit != true && player1->getHand()->getSize() != 0)
      {
         quit = onePlayerTurn(theBoard, player2, player1,gameTime, theMenu);
      }
      ++i;
   }
   if (!quit)
   {
      std::string winnerName;
      int winnerScore;
      if (player1->getScore() > player2->getScore())
      {
         winnerName = player1->getName();
         winnerScore = player1->getScore();
      }
      else if (player2->getScore() > player1->getScore())
      {
         winnerName = player2->getName();
         winnerScore = player2->getScore();
      }
      else
      {
         winnerName = "... It's tie! You both scorede:";
         winnerScore = player1->getScore();
      }
      std::cout << "Congratulations " << winnerName << " won with a score of: " << winnerScore << std::endl;
   }

   return quit;
}

bool onePlayerTurn(Board* theBoard, Player* currentPlayer, Player* otherPlayer, GamePlay* gameTime, Menu* theMenu)
{
   bool quit = false;
   theBoard->toString();
   if(currentPlayer->getNumber() == 1)
   {
      std::cout << currentPlayer->getName() << "'s score: " << currentPlayer->getScore() << std::endl;
      std::cout << otherPlayer->getName() << "'s score: " << otherPlayer->getScore() << std::endl;
   }
   else{
      std::cout << otherPlayer->getName() << "'s score: " << otherPlayer->getScore() << std::endl;
      std::cout << currentPlayer->getName() << "'s score: " << currentPlayer->getScore() << std::endl;
   }
   std::cout << currentPlayer->getNumber() <<std::endl;

   quit = gameTime->playerMove(theMenu,currentPlayer->getNumber() );
   return quit;
}

bool LoadGame(Menu* menu)
{
   GamePlay* play = new GamePlay();
   bool quit = false;
   std::vector<std::string> filename;
   std::string file;
   Player* player2;
   Player* player1;
   Board* theBoard;

    std::cout << "Enter the filename from which to load a game" << std::endl;
    filename = menu->takeLineInput(' ');
    if(filename.size() == 1 && filename[0] != std::to_string(EOF))
    {
      file = filename[0];
      file += ".save";
      std::ifstream saveFile(file);

      if(saveFile.is_open())
      {

         player1 = loadInPlayer(saveFile, menu);
         player1->setNumber(1);
         player2 = loadInPlayer(saveFile, menu);
         player2->setNumber(2);
         theBoard = loadInBoard(saveFile, menu);

         std::string playerTurn = "";

         std::getline(saveFile, playerTurn);
      
         play->setPlayer(player1);
         play->setPlayer(player2);
         play->setBoard(theBoard);
         // std::getline(saveFile, 
         if(player1->getName() == playerTurn)
         {
            quit = playingTheGame(player1, player2, theBoard, play, menu);
         }
         else
         {
            quit = playingTheGame(player2, player1, theBoard, play, menu);
         }
      }
      else
      {
         std::cout << std::endl;
         std::cout << "File does not exist!" << std::endl;
      }
   }
   else
   {
      quit = true;
   }

   return quit;
}

Player* loadInPlayer(std::ifstream& saveFile, Menu* menu)
{
//Read data for player one and two
   std::string playerName = "";
   std::string playerScore= "";
   std::string playerHand= "";
   std::vector<std::string> playerHandVector;
   int player1score= 0;
   int hundreds= 0;
   int tens = 0;
   int ones = 0;

   //Read data for player one
   if (saveFile.is_open())
   {
      std::getline(saveFile, playerName);
      std::getline(saveFile, playerScore);
      std::getline(saveFile, playerHand);
   }

   if (playerScore.size() == 3)
   {
      hundreds = (int)playerScore[0] - 48;
      tens = (int)playerScore[1] - 48;
      ones = (int)playerScore[2] - 48;
      player1score = (100*hundreds)+(10 * tens) + (ones);
   }
   else if(playerScore.size() == 2)
   {
      tens = (int)playerScore[0] - 48;
      ones = (int)playerScore[1] - 48;
      player1score = (10 * tens) + (ones);
   }
   else
   {
      player1score = ones;
   }
   
   playerHandVector = splitString(playerHand, ",");

   LinkedList* player1Hand = new LinkedList();
   for (unsigned int i =0; i < playerHandVector.size(); i++)
   {

      Colour colour = playerHandVector[i][0];
      Shape shape = (int)playerHandVector[i][1] - 48;
      Tile* newTile = new Tile(colour, shape);
      player1Hand->addBack(newTile);
   }

   Player* playerOne = new Player(playerName, player1score, player1Hand);
   return playerOne;
}

Board* loadInBoard(std::ifstream& saveFile, Menu* menu)
{
   std::vector<std::string> boardDimentions;
   std::vector<std::string> locationsW;
   std::vector<std::string> bagTiles;

   std::string locations = "";
   std::string theBagString = "";
   Board* theBoard = new Board();

   LinkedList* theBag = new LinkedList();
   int row = 0;
   int col = 0;
   std::string dimentions = "";
   //Read data for player one
   if (saveFile.is_open())
   {
      std::getline(saveFile, dimentions);
      std::getline(saveFile, locations);
      std::getline(saveFile, theBagString);
   }
   boardDimentions = splitString(dimentions, ",");
   locationsW = splitString(locations, ", ");
   
   if (boardDimentions.size() ==2)
   {
      row = (int)boardDimentions[0][0] - 48;
      col = (int)boardDimentions[1][0] - 48;
      
   }
   
   for (unsigned int i =0; i < locationsW.size(); i++)
   {
      Colour colour = locationsW[i][0];
      
      Shape shape= (int)locationsW[i][1] -48;
      Tile* tile = new Tile(colour, shape);
      
      row = (int)locationsW[i][3] - 65;
      if (locationsW[i].size() == 6)
      {
         int tens = (int)locationsW[i][4] - 48;
         int ones = (int)locationsW[i][5] - 48 - 1;
         col = 10* tens + ones;
      }
      else
      {
         col = (int)locationsW[i][4] - 48;
      }
      Location location(row,col);
      theBoard->placeTile(tile, location);
   }
   bagTiles = splitString(theBagString, ",");

   for (unsigned int i =0; i < bagTiles.size(); i++)
   {
      Colour colour = bagTiles[i][0];
      Shape shape= (int)bagTiles[i][1] -48;
      Tile* newTile = new Tile(colour, shape);
      theBag->addBack(newTile);
   }
   theBoard->setBag(theBag);


   return theBoard;
}  
    
std::vector<std::string> splitString(std::string string, std::string delim)
{
   std::vector<std::string> playerHandVector;
   if(string != "")
   {
      int start = 0;
      int end = string.find(delim);
      int length = string.size();
      std::string word;
      if(end != -1)
      {
         while(end != -1)
         {
            word = string.substr(start, end - start);
            playerHandVector.push_back(word);
            start = end + delim.size();
            end= string.find(delim, start);
         }
         
         word = string.substr(start, length);
         playerHandVector.push_back(word);
      }
      else
      {
         playerHandVector.push_back(string);
      }
   }
   
   
   return playerHandVector;
}