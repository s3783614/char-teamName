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
bool NewGame();
std::string getName();

void menu();
void Quit();
void credits();

std::vector<Tile* > initialiseTileBag();
void handingTilesToPlayers(Player* player1, Player* player2, Bag* theBag);
void playingTheGame(Player* player1, Player* player2, Bag* theBag, Board* theBoard);


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

// bool check(char *s)
// {
//    // int l = strlen(s);
//    for (int i = 0; i < l; i++)
//    {
//       if (!(s[i] >= 'A' && s[i] <= 'Z'))
//       {
//          std::cout << "Invalid Input" << std::endl;
//          return false;
//       }
//    }
//    return true;
// }

bool NewGame()
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
   Bag* bag = new Bag();
   

   std::vector<Tile*> tPtrs = initialiseTileBag();
   for (Tile* tile : tPtrs)
   {
      bag->addFront(tile);
   }

   // bag->printBag();

   
   handingTilesToPlayers(player1, player2, bag);
   //player1->printHand();
   //player2->printHand();

   playingTheGame(player1, player2, bag, board);
   // Tile* theTile = new Tile(RED, CIRCLE);
   // board->placeTile(theTile, 12, 13);
   // board->toString();
   return true;
}

void playingTheGame(Player* player1, Player* player2, Bag* theBag, Board* theBoard)
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
   std::string intermediate = "";
   while (getline(check1, intermediate, ' ')) // seperate by spaces
   {
      wordsIn.push_back(intermediate);
   }
   for (int i =0; i < wordsIn.size(); i++) // Print out vector
   {
      std::cout << wordsIn[i] << std::endl;
   }
   if (wordsIn.size() == 4 && wordsIn[0] == "Place" && wordsIn[2] == "at")
   {
      
      Tile* checkTile = new Tile(wordsIn[1][0], wordsIn[1][1]);
      player1->hand->isInBag(checkTile);
   }
   std::cout << player2->getName() << " it is your turn" << std::endl;
   std::cout << player2->getName() << ". Your hand is: " << std::endl;
   player2->printHand();
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

void handingTilesToPlayers(Player* player1, Player* player2, Bag* theBag)
{
   Tile* theTile;
   for (int i = 0; i <= 6; i++)
   {
      theTile = theBag->getFront();
      player1->addTile(theTile);
      theBag->removeFront();
      theTile = theBag->getFront();
      player2->addTile(theTile);
      theBag->removeFront();
   }
}