#include <iostream>
#include <sstream>
#include <string>
#include "MainMenu.h"


#define TEST

#ifdef TEST
namespace Test {

	// This method displays a condensed version of the list on a single line.
	// It is intended to be used for testing.
	// The field displayed in the list elements is the name field:
	// eg: [3]->[5]-#    // "3" and "5" are the actual names.  
	void viewMenuList(const Food* pHead) {
		const Food* pCurrent = pHead;
		if (pCurrent == nullptr) {
			std::cout << "-#";	// indicates a null pointer.
		}
		else {
			// while the node we're looking at is not null...
			while (pCurrent != nullptr) {
				std::cout << "[" << pCurrent->name << "]";	// output the name
				std::string next = "->";					// default pointer representation
				if (pCurrent->pNext == nullptr) {
					next = "-#";							// null pointer representation
				}
				std::cout << next;
				pCurrent = pCurrent->pNext;
			}
		}
		std::cout << "\n\n";
	}

	void viewMenuPrice(const Food* pHead) {
		const Food* pCurrent = pHead;
		if (pCurrent == nullptr) {
			std::cout << "-#";	// indicates a null pointer.
		}
		else {
			// while the node we're looking at is not null...
			while (pCurrent != nullptr) {
				std::cout << "[" << pCurrent->name << " price: $" << pCurrent->price << "]";	// output the name
				std::string next = "\n";					// default pointer representation
				if (pCurrent->pNext == nullptr) {
					next = "\n";							// null pointer representation
				}
				std::cout << next;
				pCurrent = pCurrent->pNext;
			}
		}
		std::cout << "\n\n";
	}

	// prints out a message to preceed the actual list
	void printExpectedMsg(const std::string& msg) {
		std::cout << "\n----------------------------------\n";
		std::cout << "expected: \t" << msg << "\n";
		std::cout << "actual: \t";
	}

	// runs a bunch of tests to see if list implementation works as expected.
	void testBasicFunctionality(Food*& pHead) {

		std::cout << "test empty list:\n";
		printExpectedMsg("-#.");
		viewMenuList(pHead);

		std::cout << "test (invalid) removal from empty list:\n";
		removeFood(pHead, 0);
		printExpectedMsg("-#");
		viewMenuList(pHead);

		std::cout << "test add 5 foods:\n";
		addNewFood(pHead, "0", 10);
		addNewFood(pHead, "1", 20);
		addNewFood(pHead, "2", 30);
		addNewFood(pHead, "3", 40);
		addNewFood(pHead, "4", 50);
		viewMenuList(pHead);
		printExpectedMsg("[0]->[1]->[2]->[3]->[4]-#");
		viewMenuList(pHead);

		std::cout << "test invalid removal from full list:\n";
		removeFood(pHead, 99);
		printExpectedMsg("[0]->[1]->[2]->[3]->[4]-#");
		viewMenuList(pHead);

		std::cout << "test removal from head:\n";
		removeFood(pHead, 0);
		printExpectedMsg("[1]->[2]->[3]->[4]-#");
		viewMenuList(pHead);

		std::cout << "test removal from tail:\n";
		removeFood(pHead, 4);
		printExpectedMsg("[1]->[2]->[3]-#");
		viewMenuList(pHead);


		std::cout << "test removal from middle:\n";
		removeFood(pHead, 2);
		printExpectedMsg("[1]->[3]-#");
		viewMenuList(pHead);

		std::cout << "test (invalid) removal of pre-existing element:\n";
		removeFood(pHead, 2);
		printExpectedMsg("[1]->[3]-#");
		viewMenuList(pHead);

		std::cout << "test remove last 2 individually:\n";
		removeFood(pHead, 1);
		removeFood(pHead, 3);
		viewMenuList(pHead);
		printExpectedMsg("-#");
		viewMenuList(pHead);

		std::cout << "test invalid removal on an empty list:\n";
		removeFood(pHead, 999);
		printExpectedMsg("-#");
		viewMenuList(pHead);

		std::cout << "test invalid removal on a list of one element:\n";
		addNewFood(pHead, "5", 60);
		removeFood(pHead, 999);
		printExpectedMsg("[5]-#");
		viewMenuList(pHead);

		std::cout << "test invalid removal on a list of two elements:\n";
		addNewFood(pHead, "6", 70);
		removeFood(pHead, 999);
		printExpectedMsg("[5]->[6]-#");
		viewMenuList(pHead);

		std::cout << "test remove head, add new element:\n";
		removeFood(pHead, 5);
		addNewFood(pHead, "7", 80);
		printExpectedMsg("[6]->[7]-#");
		viewMenuList(pHead);

		std::cout << "test remove tail, add new element:\n";
		removeFood(pHead, 7);
		addNewFood(pHead, "8", 90);
		printExpectedMsg("[6]->[8]-#");
		viewMenuList(pHead);

		std::cout << "test add 10 foods & remove them all with removeAllFoods():\n";
		for (int i = 0; i < 10; i++)
		{
			addNewFood(pHead, std::to_string(i), (i + 1) * 10);
		}
		removeAllFoods(pHead);
		printExpectedMsg("-#");
		viewMenuList(pHead);

		std::cout << "test change the price with editFoodPrice():\n";

		addNewFood(pHead, "19", 19);
		std::cout << "test with invalid id:\n";
		printExpectedMsg("Food id: 999 not found\n");
		editFoodPrice(pHead, 999);

		std::cout << "test with valid id:\n";
		std::istringstream validInput("50");
		std::streambuf* cinBackup = std::cin.rdbuf(validInput.rdbuf());
		editFoodPrice(pHead, 19);
		std::cin.rdbuf(cinBackup);
		printExpectedMsg("[19 price: $50]");
		viewMenuPrice(pHead);

		std::cout << "test discount applying with applyDiscount():";
		addNewFood(pHead, "20", 50);
		addNewFood(pHead, "21", 50);

		std::cout << "test with invalid id:\n"; {
			std::istringstream validInput("999\n-1\n");
			std::streambuf* cinBackup = std::cin.rdbuf(validInput.rdbuf());
			applyDiscount(pHead, 0.5);
			std::cin.rdbuf(cinBackup);
		}
		printExpectedMsg("[19 price: $50]\n[20 price: $50]\n[21 price: $50]\n");
		viewMenuPrice(pHead);

		std::cout << "test with duplicate id:\n"; {
			std::istringstream validInput("19\n19\n-1\n");
			std::streambuf* cinBackup = std::cin.rdbuf(validInput.rdbuf());
			applyDiscount(pHead, 0.5);
			std::cin.rdbuf(cinBackup);
		}
		printExpectedMsg("[19 price: $25]\n[20 price: $50]\n[21 price: $50]\n");
		viewMenuPrice(pHead);

		std::cout << "test with valid ids:\n"; {
			std::istringstream validInput("19\n20\n-1\n");
			std::streambuf* cinBackup = std::cin.rdbuf(validInput.rdbuf());
			applyDiscount(pHead, 0.5);
			std::cin.rdbuf(cinBackup);
		}
		printExpectedMsg("[19 price: $12.5]\n[20 price: $25]\n[21 price: $50]\n");
		viewMenuPrice(pHead);
	}

	void runTest() {
		Food* pFoods = nullptr;
		testBasicFunctionality(pFoods);
	}
}

#endif