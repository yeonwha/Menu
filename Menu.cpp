#include <iostream>
#include "MainMenu.h"

int main()
{
	// Pointer to the menu list
	Food* pFoods = nullptr;

	//bool exitMainMenu{ false };
	Command command{ Command::invalid };

	// Display the main menu, handle the input from the user
	do {
		displayMainMenu();
		command = getMenuCommand();
		handleMenuInput(pFoods, command);
	} while (command != Command::exit);

	// Deallocate any food on the menu to nullptr
	removeAllFoods(pFoods);

	return 0;
}
