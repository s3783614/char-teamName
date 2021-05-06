#include "LinkedList.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

#include "TileCodes.h"
#include "Player.h"
#include "Bag.h"
#include "Board.h"

#define EXIT_SUCCESS 0

bool check(char *s);
void NewGame();
std::string getName();

void menu();
void Quit();
void credits();

std::vector<Tile* > initialiseTileBag();
void handingTilesToPlayers(Player* player1, Player* player2, Board* theBoard);
void playingTheGame(Player* player1, Player* player2, Board* theBoard);

int convertToRow(char row);
int convertToCol(char col);


int main(void)
{
   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;

   std::string userInput = "";
   bool exit = false;
   while (exit == false)
   {
      menu();
      std::cout << ">";
      // char opt[10];
      // if (!std::cin.get(opt, 10))
      // {
      //    Quit();
      //    return false;
      // }
      // getchar();
      std::cin >> userInput;
      // if (strlen(opt) != 1)
      // {
      //    std::cout << "Invalid Input" << std::endl;
      //    continue;
      // }
      // if (!(userInput[0] >= '1' && opt[0] <= '4'))
      // {
      //    std::cout << "Invalid Input" << std::endl;
      //    continue;
      // }

      // int code = opt[0] - '0';
      if (userInput == "1")
      {
         // if (!NewGame())
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
         Quit();
         exit = true;
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

void Quit()
{
   // std::cout << std::endl;
   std::cout << "Goodbye" << std::endl;
}

void NewGame()
{
   std::string name1 = "";
   std::string name2 = "";

   std::cout << std::endl;
   std::cout << "Starting a New Game" << std::endl
             << std::endl;
   std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
   std::cout << ">";
   name1 = getName();
   Player* player1 = new Player(name1);
   std::cout << player1->getName() << std::endl;

   std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
   std::cout << ">";
   name2 = getName();
   Player* player2 = new Player(name2);
   std::cout << player2->getName() << std::endl;
   Board *board = new Board();
   

   std::vector<Tile*> tPtrs = initialiseTileBag();
   for (Tile* tile : tPtrs)
   {
      board->getBag()->addFront(tile);
   }

   // bag->printBag();

   
   handingTilesToPlayers(player1, player2, board);
   //player1->printHand();
   //player2->printHand();

   playingTheGame(player1, player2, board);
   // Tile* theTile = new Tile(RED, CIRCLE);
   // board->placeTile(theTile, 12, 13);
   // board->toString();
   
}

void playingTheGame(Player* player1, Player* player2, Board* theBoard)
{
   std::string theMove = "";
   theBoard->toString();
   std::cout << player1->getName() << "'s score: " << player1->getScore() << std::endl;
   std::cout << player2->getName() << "'s score: " << player2->getScore() << std::endl;

   std::cout << player1->getName() << " it is your turn" << std::endl;
   std::cout << player1->getName() << ". Your hand is: " << std::endl;
   player1->printHand();
   std::cout << "What would you like to play and where?" << std::endl;
   std::cin.ignore();
   std::getline(std::cin, theMove);

   std::vector<std::string> wordsIn;
   std::stringstream check1(theMove);
   std::string tmpString = "";
   while (getline(check1, tmpString, ' ')) // seperate by spaces
   {
      wordsIn.push_back(tmpString);
   }
   for (unsigned int i =0; i < wordsIn.size(); i++) // Print out vector
   {
      std::cout << wordsIn[i] << std::endl;
   }
      // std::cout << "Spot 1" << std::endl;

   if (wordsIn.size() == 4 && wordsIn[0] == "Place" && wordsIn[2] == "at" &&  wordsIn[1].size() == 2 && wordsIn[3].size() == 2)
   {
      // std::cout << "Spot 2" << std::endl;

      
//CHANGE LATER --ASCII MAGIC
// check letter is shape and number is Colour
      Tile* checkTile = new Tile(wordsIn[1][0], (int)wordsIn[1][1]-48);

      
      bool check = player1->getHand()->isInLinkedList(checkTile);

//CHANGE LATER --ASCII MAGIC
      int row = (int)wordsIn[3][0] - 65;
      int col = (int)wordsIn[3][1] - 48;
      //TODO -- check if row col are less than board size
      bool isTaken = theBoard->isSpotTaken(row,col);
      // std::cout << "check: " << check << "isTaken: " << isTaken << std::endl;

   }

}



std::string getName()
{
   std::string name;

   bool checker = false;
   while (checker == false)
   {
      // std::cout << "Enter your name (CAPITALS AND NO SPACES)" << std::endl;
      std::cin >> name;
      checker = true;
      for (unsigned int i = 0; i < name.length(); i++)
      {

         if (name[i] < 65 || name[i] > 90)
         {
            checker = false;
         }
         
      }
      if(checker == false)
      {
         std::cout << "Invalid Input!" << std::endl;
         std::cout << "Please enter ONLY CAPITAL LETTERS!" << std::endl;
         std::cout << ">" ;
      }
   }
   return name;
}

void credits()
{
   std::cout << "CREDITS" << std::endl;
   std::cout << "-------" << std::endl;
}


std::vector<Tile* > initialiseTileBag()
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

void handingTilesToPlayers(Player* player1, Player* player2, Board* theBoard)
{
   Tile* theTile;
   for (int i = 0; i <= 6; i++)
   {
      theTile = theBoard->getBag()->getFront();
      player1->getHand()->addFront(theTile);
      theBoard->getBag()->removeFront();
      theTile = theBoard->getBag()->getFront();
      player2->getHand()->addFront(theTile);
      theBoard->getBag()->removeFront();
   }
}

