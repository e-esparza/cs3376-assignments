#ifndef MENU_H
#define MENU_H

#include "MenuItem.h"

#define MENU_DEFAULT_ITEMS_SIZE 1

class Menu 
{
private:
	int maxItems; // MAX capacity 
	int numItems; // current # of items in menu
	MenuItem *menup;
    void extendMenuItemArray(void); // extends the menup array by 2 elements.

public:

	Menu(int items = MENU_DEFAULT_ITEMS_SIZE); //constructor to allocate memory
	void addItem(MenuItem item); //add one menu item at a time
	MenuItem* findItem(string code); //lookup operation
	~Menu(); //destructor
    void printMenuItems(); // used for debugging
};

// Usage:
// Menu menu;
// MenuItem *ip = menu.findItem(code);

// IMPLEMENTATION:
// MenuItem* Menu::findItem(string code) CORRECT
#endif