#include "GamePlay.h"

#define EXIT_SUCCESS 0

void menu();

void credits();

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
