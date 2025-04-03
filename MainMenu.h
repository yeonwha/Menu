#ifndef MAINMENU_H
#define MAINMENU_H

#include <string>

const float MIN_PRICE = 1.0f; // minimum price for food
const float MAX_PRICE = 1000.0f; // maximum price for food
const float MIN_RATE = 0.05f; // minimum discount rate
const float MAX_RATE = 0.9f; // maximum discount rate

// Command set to handle user input from the menu selection
enum class Command{ viewMenu, addMenu, editPrice, removeMenu, removeAll, exit, invalid };

// Struct to store food information
struct Food {
	int id;
	std::string name;
	float price;
	Food* pNext;
};

// A struct used to return multiple return values from the getNodeInfo() function.
// getNodeInfo() traverses the list looking for a target node (and its parent node).
// NodeInfo contains info needed to facilitate node insertion & deletion in the list.
struct NodeInfo {
	Food* pNode;	// a pointer to the target node.
	Food* pParent;  // a pointer to the node prior to pNode (nullptr if node is at the front)
};

// Clear any characters from the input buffer
void ignoreLine();

// Read and return an int from the console.
int getIntFromUser();

// Display the main menu
void displayMainMenu();

// Fetch and return a menu command from user input
Command getMenuCommand();

// Given a Command, this will determine the appropriate function to call.
// - param 1: a pointer to the front of the food list
// - param 2: a Command representing the action to be taken.
void handleMenuInput(Food*& pHead, Command command);

// Output a list of all food on menu
void viewMenu(Food* pHead);

// Create a new food menu on the heap
// - param 1: a string (food name for a new food struct)
// - param 2: a float (the food price). 
// - return: new Food struct pointer
Food* createFood(const std::string name, float price);

// Create a new food nod, add it to the menu list
// - param 1: a pointer to the front of the food list to check if the list is empty or not
// - param 2: a string (food name for a new food struct)
// - param 3: a float (the food price). 
void addNewFood(Food*& pHead, std::string name, float price);

// Search through the list for a node with id
// - param 1: a pointer to the front of the food list
// - param 2: an int id to search for
NodeInfo getNodeInfo(Food* pHead, int idFood);

// Edit food's price
// - param 1: a pointer to the front of the food list
// - param 2: an int id to search for
void editFoodPrice(Food*& pHead, int idFood);

// Apply discount rate
// - param 1: a pointer to the front of the food list
// - param 2: the discount rate to apply
void applyDiscount(Food*& pHead, float rate);

// Remove a food menu node with the given id from the list.
// - param 1: a pointer to the front of the food list
// - param 2: an int id to search for
void removeFood(Food*& pHead, int idFood);

//Remove all food menu after showing the list
void removeAllFoods(Food*& pHead);

#endif