#ifndef MAINMENU_H
#define MAINMENU_H

#include <string>

const float MIN_PRICE = 1.0f; // minimum price for food
const float MAX_PRICE = 1000.0f; // maximum price for food
const float MIN_RATE = 0.05f; // minimum discount rate
const float MAX_RATE = 0.9f; // maximum discount rate

enum class Command{ viewMenu, addMenu, editPrice, removeMenu, removeAll, exit, invalid };

struct Food {
	int id;
	std::string name;
	float price;
	Food* pNext;
};

struct NodeInfo {
	Food* pNode;
	Food* pParent;
	Food* pTail;
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
Food* createFood(const std::string name, float price);

// Create a new food nod, add it to the menu list
void addNewFood(Food*& pHead, std::string name, float price);

// Search through the list for a node with id
NodeInfo getNodeInfo(Food* pHead, int idFood);

// Edit food's price
void editFoodPrice(Food*& pHead, int idFood);

// Apply discount rate
void applyDiscount(Food*& pHead, float rate);

// Removes a food menu node with the given id from the list.
void removeFood(Food*& pHead, int idFood);

//Remove all food menu after showing the list
void removeAllFoods(Food*& pHead);

#endif