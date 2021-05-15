#include "Menu.h"

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

void Menu::printCredits()
{
   std::cout << "CREDITS" << std::endl;
   std::cout << "-------" << std::endl;
}

// Asks the User for an Input and takes an entire line with spaces
// Splits the input to individual words by spaces
// Puts each word in order into a vector
// Returns the vector
std::vector<std::string> Menu::takeLineInput(char charToSplit)
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
      while (getline(check1, tmpString, charToSplit))
      {
         wordsIn.push_back(tmpString);
      }
   }
   else
   {
      wordsIn.push_back(std::to_string(EOF));
   }
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
      if(wordsIn.size() ==1 && wordsIn[0] != std::to_string(EOF))
      {
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
      else
      {
         name = std::to_string(EOF);
         checker = true;
      }
      
   }
   return name;
}