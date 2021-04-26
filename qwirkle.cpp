#include "LinkedList.h"

#include <iostream>

#define EXIT_SUCCESS    0

void Menu() {
	std::cout << std::endl;
	std::cout << "Menu" << std::endl;
	std::cout << "----" << std::endl;
	std::cout << "1. New Game" << std::endl;
	std::cout << "2. Load Game" << std::endl;
	std::cout << "3. Credits (Show student information)" << std::endl;
	std::cout << "4. Quit" << std::endl;
	std::cout << std::endl;
}

void Quit() {
	std::cout << std::endl << "Goodbye";
}

bool check(char* s) {
	int l = strlen(s);
	for (int i = 0; i < l; i++) {
		if (!(s[i] >= 'A' && s[i] <= 'Z')) { std::cout << "Invalid Input" << std::endl; return false; }
	}
	return true;
}

bool NewGame() {
	char name1[10], name2[10];
	std::cout << std::endl;
	std::cout << "Starting a New Game" << std::endl << std::endl;
	std::cout << "Enter a name for palyer 1 (uppercase characters only)" << std::endl;
	std::cout << ">";
	if (!std::cin.getline(name1, 10)) {
		Quit(); return false;
	}
	while (!check(name1)) {
		std::cout << "Enter a name for palyer 1 (uppercase characters only)" << std::endl;
		std::cout << ">";
		if (!std::cin.getline(name1, 10)) {
			Quit(); return false;
		}
	}
	std::cout << "Enter a name for palyer 2 (uppercase characters only)" << std::endl;
	std::cout << ">";
	if (!std::cin.getline(name2, 10)) {
		Quit(); return false;
	}
	while (!check(name2)) {
		std::cout << "Enter a name for palyer 2 (uppercase characters only)" << std::endl;
		std::cout << ">";
		if (!std::cin.getline(name2, 10)) {
			Quit(); return false;
		}
	}

}


int main(void) {
   LinkedList* list = new LinkedList();
   delete list;
   std::cout << "TODO: Implement Qwirkle!" << std::endl;

   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;

   Menu();
   
   while (true) {
	   std::cout << ">";
	   char opt[10];
	   if (!std::cin.get(opt, 10)) {
		   Quit(); return false;
	   }
	   getchar();
	   if (strlen(opt) != 1) { std::cout << "Invalid Input" << std::endl; continue; }
	   if (!(opt[0] >= '1' && opt[0] <= '4')) { std::cout << "Invalid Input" << std::endl; continue; }
	   int code = opt[0] - '0';
	   if (code == 1) {
		   if (!NewGame())return 0;
	   }
	   else if (code == 2) {

	   }
	   else if (code == 3) {

	   }
	   else if (code == 4) {
		   Quit(); return 0;
	   }
   }

   return EXIT_SUCCESS;
}

