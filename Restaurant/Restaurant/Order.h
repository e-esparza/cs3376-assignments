#ifndef ORDER_H
#define ORDER_H

#include "MenuItem.h"
#include "Menu.h"

class Order
{
private:
	int maxItems;  // # of items in the order
	int numItems;  // current # of items in the order
	MenuItem **itemsp;
	
public:
	Order(int count); //allocates array of pointers to "selected" menu items
	void addItem(MenuItem *itemp); // add one item at a time to the order
    void printOrderData(void); // used for debugging
    double getOrderTotal(void); // user for debugging
	~Order();
};
#endif