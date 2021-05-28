#include "Menu.h"

Menu::Menu()
{
   quit = false;
}


bool Menu::getQuit()
{
   return quit;
}
void Menu::setQuit(bool quitBool)
{
   quit = quitBool;
}
// Prints out a menu
void Menu::printMenu()
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

// Prints the credits 
void Menu::printCredits()
{
   std::cout << "CREDITS" << std::endl;
   std::cout << "-------------------------------------------" << std::endl;
   std::cout << "Name:       " << "Aidan McGinniss" << std::endl;
   std::cout << "Student Id: " << "s3545999" << std::endl;
   std::cout << "Email:      " << "s3545999@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
   std::cout << "Name:       " << "Ashwin Venkita Subharaman" << std::endl;
   std::cout << "Student Id: " << "s3783614" << std::endl;
   std::cout << "Email:      " << "s3783614@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
   std::cout << "Name:       " << "Shewit Tikue" << std::endl;
   std::cout << "Student Id: " << "s3545853" << std::endl;
   std::cout << "Email:      " << "s3545853@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
   std::cout << "Name:       " << "Hamida Ehsani" << std::endl;
   std::cout << "Student Id: " << "s3653728" << std::endl;
   std::cout << "Email:      " << "s3653728@student.rmit.edu.au" << std::endl;
   std::cout << "-------------------------------------------" << std::endl;
   
}

// Converts a char of an integer to an integer
int Menu::charToInt(char character)
{
   return (int)character - ASCII_ZERO;
}

// Asks the User for an Input and takes an entire line with spaces
// Splits the input to individual words by spaces
// Puts each word in order into a vector
// Returns the vector
std::vector<std::string> Menu::takeLineInput(char charToSplit)
{
   std::vector<std::string> wordsIn;
   std::string theMove = "";

   std::cout << "> ";
   std::getline(std::cin, theMove);

   // Check that eof character not inputted
   if (!std::cin.eof())
   {
      // Take the line inputted and split by spaces to individual words
      std::stringstream check1(theMove);
      std::string tmpString = "";
      while (getline(check1, tmpString, charToSplit))
      {
         wordsIn.push_back(tmpString);
      }
   }
   else
   {
      quit = true;
   }

   // if the return vector is a vector with only element 'help', print help command
   if(wordsIn.size() == 1 && wordsIn[0] == "help")
   {
      printHelp();
      return takeLineInput(charToSplit);
   } 
   else
      return wordsIn;
}

std::string Menu::getName()
{
   std::vector<std::string> wordsIn;
   std::string name;

   bool checker = false;

   while (checker == false)
   {
      checker = true;
      std::cout << "Enter your name (ONLY CAPITALS AND NO SPACES)" << std::endl;
      wordsIn = takeLineInput(' ');
      if(wordsIn.size() == 1 && wordsIn[0] != std::to_string(EOF))
      {
         name = wordsIn[0];

         for (unsigned int i = 0; i < name.length(); i++)
         {

            if (name[i] < 65 || name[i] > 90)
            {
               checker = false;
               break;
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
         std::cout << "Invalid Input!" << std::endl
                   << "Please enter EXACTLY one name!" << std::endl;
         std::cout << std::endl;
         checker = false;
      }
      
   }
   return name;
}

void Menu::printHelp()
{
   std::cout << "In menu, enter 1-4 to select options;" << std::endl
             << "In new game, enter names to start play; " << std::endl
             << "In load game, enter file name to load a old game; " << std::endl
             << "After game starts, enter \"place <tile> at <grid location>\" to place a tile" << std::endl
             << "(or use \"place A1,B2,C2 at D1,F2,K3\" to place at multiple places), or enter" << std::endl
             << "\"replace <tile>\" to replace a tile, tile and grid format follows <ROW><COL>." << std::endl
             << "During a game round, enter \"save <filename>\" to save the game to specified" << std::endl
             << "file, or enter \"quit\" to directly exit the game without saving." << std::endl
             << "========================= ENJOY THE GAME =========================" << std::endl;
}