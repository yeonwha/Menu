#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "MainMenu.h"

// clear any characters from the (keyboard) input buffer
void ignoreLine() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// read and return an int from the console.  Keep trying if invalid until an int is returned.
int getIntFromUser() {
	while (true) {
		int guess;
		std::cin >> guess;

		if (std::cin.fail()) {
			std::cin.clear();
			ignoreLine();
			std::cerr << "Invalid input. Input must be a valid int.  Please try again.\n";
		}
		else
		{
			ignoreLine();
			return guess;
		}
	}
}

// output the menu choices to the console.
void displayMainMenu()
{
	std::cout << "\n";
	std::cout << "--- MENU ---\n";
	std::cout << "1) View Menu\n";
	std::cout << "2) Add Menu\n";
	std::cout << "3) Remove Menu\n";
	std::cout << "4) Remove all\n";
	std::cout << "5) Edit Price\n";
	std::cout << "0) Exit\n";
	std::cout << "-------------\n";
	std::cout << "Select:";
}

// Attempt to read an int from the keyboard.  
// If there was a failure, clear the buffer and return -1.
Command getMenuCommand() {
	// read user input
	int input{ -1 };  // default 
	std::cin >> input;
	if (std::cin.fail()) {
		std::cin.clear();	// clear the failure
		input = -1;			// indicate an error
	}
	ignoreLine();	// ignore any extra input

	Command command = Command::invalid;	// default
	// match input with specific commands
	switch (input) {
	case 1: command = Command::viewMenu; break;
	case 2: command = Command::addMenu; break;
	case 3: command = Command::removeMenu; break;
	case 4: command = Command::removeAll; break;
	case 5: command = Command::editPrice; break;
	case 0: command = Command::exit; break;
	}
	return command;
}

// This function is called when a user picks a selection from the menu.
// It determines what action to take depending on the menuItemSelected, 
// and calls the appropriate function.
// Returns true the selection was a request to exit menu, false otherwise.
void handleMenuInput(Food*& pHead, Command command)
{
	switch (command)
	{
	case Command::viewMenu:
		std::cout << ">> View Menu:\n";
		viewMenu(pHead);
		break;

	case Command::addMenu: {
		std::cout << ">> Add Menu:\n";
		std::cout << "Enter name:";
		std::string name;
		std::getline(std::cin, name);
		
		float price{ MIN_PRICE };  // set the price as minimum price, $1
		// repeat till get a price in the range ($1 ~ $1,000) and numeric
		while (true) {
			std::cout << "Enter food price(only number):";
			std::cin >> price;

			if (std::cin.fail() || price < MIN_PRICE || price > MAX_PRICE) {
				std::cout << "Invalid input or the price is out of range. Please enter a valid price between "
					<< MIN_PRICE << " and " << MAX_PRICE << ".\n";
				ignoreLine();
			}
			else {
				break;
			}
		}

		addNewFood(pHead, name, price);
		std::cout << name << " is added.";
		break;
	}
	case Command::removeMenu:
		std::cout << ">> Remove Menu:\n";
		viewMenu(pHead);
		std::cout << "Enter id:";
		removeFood(pHead, getIntFromUser());
		break;

	case Command::removeAll:
		std::cout << ">> Remove All:\n";
		removeAllFoods(pHead);
		break;

	case Command::editPrice: {
		if (pHead == nullptr) {
			std::cout << "empty list.\n";
			break;
		}
		else {
			std::cout << ">> Edit Price:\n";
			std::cout << "Select an option:\n";
			std::cout << "-------------------------\n";
			std::cout << "1) Price Modification\n";
			std::cout << "2) Discount Application\n";
			std::cout << "3) Cancel\n";
			std::cout << "-------------------------\n";
			std::cout << "Select:";

			int option{ -1 };	// edit price option
			std::cin >> option;
			if (std::cin.fail()) {
				std::cin.clear();		// clear the failure
				option = -1;			// indicate an error
			}
			ignoreLine();

			switch (option) {
			case 1: {
				viewMenu(pHead);	// display menu to show the ids
				std::cout << "Enter id:";
				editFoodPrice(pHead, getIntFromUser());
				break;
			}
			case 2: {
				float discountRate{ 1.0 };	// discount rate to apply (cost price)
				// repeat asking rate till the input is in the range (5% ~ 90%)
				while (true) {
					std::cout << "Enter the discount rate between 5% ~ 90% (e.g., 0.1 for 10%):";
					std::cin >> discountRate;

					if (std::cin.fail() || discountRate < MIN_RATE || discountRate > MAX_RATE) {
						std::cout << "Invalid input or the rate is out of range.\nPlease enter a valid rate between "
							<< MIN_RATE * 100 << "% and " << MAX_RATE * 100 << "%.\n";
						ignoreLine();
					}
					else {
						break;
					}
				}
				
				applyDiscount(pHead, discountRate);
				break;
			}
			case 3:
				std::cout << "Edit Price cancelled.\n";
				break;
			default:
				std::cout << "Invalid input.\n";
				break;
			}
		}
	}
	case Command::exit:
		std::cout << "Exiting\n";
		break;

	default:
		std::cout << "Invalid input.\n";
		break;
	}
}

// Output a list of all food menu.
// If the list is empty (nullptr), print "empty list." 
// If it isn't empty, print each food's id, name and price to the console:
//    eg: [id: 5, name: Cheese burger price: $12.99]
// Create a pointer to traverse the list, point it at the front of the list,
// process the node (output as shown above), and advance the pointer through the
// list.  Repeat until you process the last node.
// -param 1: the head pointer to Food struct 
void viewMenu(Food* pHead) {
	if (pHead != nullptr) {
		while (pHead != nullptr) {
			std::stringstream ss;
			ss.imbue(std::locale("en_US.UTF-8"));
			ss << pHead->price;
			std::cout << "[id: " << pHead->id << ", name: " << pHead->name << ", price: $" << ss.str() << "]\n";
			pHead = pHead->pNext;
		}
	} else {
		std::cout << "empty list.\n";
	}
}

// Create a new Food struct
// initialized it with:
//		-the unique id,
//		-the name passed in as a paramter,
//		-nullptr.
// - param 1: a string - the food's name.
// - return: a pointer to the new Food struct
Food* createFood(const std::string name, float price) {
	Food* newFood = new Food;
	static int id = 0;

	newFood->id = id++;
	newFood->name = name.empty() ? "no name" : name;
	newFood->price = price;
	newFood->pNext = nullptr;

	return newFood;
}

// Create a new food nod, add it to the menu list
// - param 1: a pointer to the front of the food list to check if the list is empty or not
// - param 2: a string (food name for a new food struct)
// - param 3: a float (the food price). 
void addNewFood(Food*& pHead, std::string name, float price) {
	Food* newFood{ createFood(name, price) };

	if (pHead == nullptr) {
		// if the list is empty, new food is the head pointer
		pHead = newFood;
	}
	else {
		// add new food at the tail of the list 
		Food* temp = pHead;
		while (temp->pNext != nullptr) {
			temp = temp->pNext;
		}
		temp->pNext = newFood;
	}
}

// Search through the list for a node with id
// - param 1: a pointer to the front of the food list
// - param 2: an int id to search for
// - return: a NodeInfo struct. It contains a pointer to the node that matches  
//			 the id and a pointer to that node's parent. 
//           If node not found, pointers inside NodeInfo should both be nullptr.
//           If node is first in the list, NodeInfo.pParent should be nullptr.
NodeInfo getNodeInfo(Food* pHead, int idFood) {
	NodeInfo theNode{};
	theNode.pNode = nullptr;
	theNode.pParent = nullptr;

	while (pHead != nullptr) {
		if (pHead->id == idFood) {
			theNode.pNode = pHead;
			break;
		}
		theNode.pParent = pHead;
		pHead = pHead->pNext;
	}
	if (pHead == nullptr) {
		theNode.pParent = nullptr;
	}
	return theNode;
};

// Edit food's price
// Try to find a node with the id (getNodeInfo()). 
// If node not found, output "Error: Food id:# not found\n". 
// If node found, change node.pNode.price with the new price (user input)
// and output "[Food name]'s price is updated successfully."
// - param 1: a pointer to the front of the food list
// - param 2: an int id to search for
void editFoodPrice(Food*& pHead, int idFood) {
	NodeInfo node{ getNodeInfo(pHead, idFood) };

	if (node.pNode == nullptr) {
		std::cout << "Food id: " << idFood << " not found\n";
	}
	else {
		std::cout << "Enter the new price (only number): ";
		float newPrice;		// new price to apply
		std::cin >> newPrice;
		// repeat until the price is in the range ($1 ~ $1,000) and numeric
		while (true) {
			if (std::cin.fail() || newPrice < MIN_PRICE || newPrice > MAX_PRICE) {
				std::cout << "Invalid input or the price is out of range. Please enter a valid price between "
					<< MIN_PRICE << " and " << MAX_PRICE << ".\n";
				ignoreLine();
			}
			else {
				node.pNode->price = newPrice;
				std::cout << node.pNode->name << "'s price updated successfully.\n";
				break;
			}
		}
	}
}

// Apply discount rate
// Collect ids first (only valid id and no duplicate id)
// and apply the discount rate to all collected ids, then
// output "Discount applied to [Food name] (ID: [Food id]). New price: "[rate-applied price]";
// - param 1: a pointer to the front of the food list
// - param 2: the discount rate to apply
void applyDiscount(Food*& pHead, float rate) {
	viewMenu(pHead);	// display the food list first
	std::vector<int> selectedIds;	// ids to apply the discount rates

	// keep collecting ids till enter -1 to finish
	while (true) {
		std::cout << "Enter Food ID to apply discount (or -1 to finish): ";
		int id;
		std::cin >> id;
		if (id == -1) break;

		NodeInfo node{ getNodeInfo(pHead, id) };
		if (node.pNode == nullptr) {
			std::cout << "Food id: " << id << " not found\n";
			viewMenu(pHead);
		}
		else {
			if (std::find(selectedIds.begin(), selectedIds.end(), id) != selectedIds.end()) {
				std::cout << "Food id: " << id << " already selected.\n";
			}
			else {
				selectedIds.push_back(id);
			}
		}
	}

	for (int id : selectedIds) {
		Food* temp = pHead;
		while (temp != nullptr) {
			if (temp->id == id) {
				temp->price *= (1 - rate);
				std::cout << "Discount applied to " << temp->name << " (ID: " << temp->id << "). New price: " << temp->price << "\n";
				break;
			}
			temp = temp->pNext;
		}
	}
}

// Remove a food menu node with the given id from the list.
//  Try to find a node with the id (getNodeInfo()). 
//	If node not found, output "Error: employee id:# not found\n". 
//  If node found, but parent is nullptr, the node is first in the list:
//			-Set the pHead to point to the second node in the list.
//			-Output "removed id:#"
//			-Deallocate the node
//  otherwise the node was found and a parent exists
//			-Set the parent's next pointer to the next pointer of the node we want to delete
//			-Output a "removed id: #n"
//			-Deallocate the node
// - param 1: a pointer to the front of the food list
// - param 2: an int id to search for
void removeFood(Food*& pHead, int idFood) {
	NodeInfo node{ getNodeInfo(pHead, idFood) };

	if (node.pNode == nullptr) {
		std::cout << "Food id: " << idFood << " not found\n";
	}
	else {
		std::cout << "removed id: " << idFood << "\n";
		if (node.pParent == nullptr) {
			Food* old = pHead;
			pHead = pHead->pNext;
			delete old;
		}
		else {
			Food* old = node.pParent->pNext;
			node.pParent->pNext = node.pNode->pNext;
			delete old;
		}
	}
};

// Removes all employees after showing the list.
void removeAllFoods(Food*& pHead) {
	viewMenu(pHead);
	while (pHead != nullptr) {
		removeFood(pHead, pHead->id);
	}
};
