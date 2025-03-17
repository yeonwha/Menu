#ifndef MAINMENU_H
#define MAINMENU_H

#include <string>

enum class Command{ viewMenu, addMenu, removeMenu, removeAll, exit, invalid };

struct Food {
	int id;
	std::string name;
	float price;
	Food* pPrev;
};

struct NodeInfo {
	Food* pNode;
	Food* pParent;
};

// Clear any characters from the input buffer
void ignoreLine();

// Read and return an int from the console.
int getIntFromUser();

// Display the main menu
void displayMainMenu();

// Fetch and return a menu command from user input
Command getMenuCommand();

void handleMenuInput(Food*& pHead, Command command);

// Output a list of all food on menu
void viewMenu(Food* pHead);

// Create a new food menu on the heap
Food* createFood(const std::string name, int price);

// Create a new food nod, add it to the menu list
void addNewFood(Food*& pTail, std::string name, int price);

// Search through the list for a node with id
NodeInfo getNodeInfo(Food* pTail, int idFood);

// Removes a food menu node with the given id from the list.
void removeFood(Food*& pTail, int idFood);

//Remove all food menu after showing the list
void removeAllFoods(Food*& pTail);

#endif