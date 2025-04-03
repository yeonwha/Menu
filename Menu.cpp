#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "MainMenu.h"
#include "Test.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Test::runTest();

	// Pointer to the menu list
	Food* pFoods = nullptr;

	// Default command set to invalid
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
