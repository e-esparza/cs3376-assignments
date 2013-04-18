#include "Order.h"

Order::Order(int count)
{
    
    this->maxItems = count;
    
    this->numItems = 0;
    
    this->itemsp = new MenuItem * [this->maxItems];
    
}

void Order::addItem(MenuItem *itemp)
{
    
    // We cannot add anymore menu items.
    if ( this->maxItems == this->numItems ) return;
    
    this->itemsp[this->numItems] = itemp;
    
    this->numItems++; // Increment total number of items.
    
    return;
    
}

void Order::printOrderData()
{
    
    cout << "~~~~Start of Order~~~~" << endl;
    
    for( int i = 0; i < this->numItems; i++ )
    {
        
        MenuItem * item = this->itemsp[i];
        
        item->printItemData();
        
    }
    
    cout << "Total: " << this->getOrderTotal() << endl;
    
    cout << "~~~~End of Order~~~~" << endl;
    
}

double Order::getOrderTotal()
{
    
    double total = 0.0;
    
    for( int i = 0; i < this->numItems; i++ )
    {
        
        MenuItem * item = this->itemsp[i];
        
        double price = item->getPrice();
        
        total+=price;
        
    }
    
    return total;
    
}

Order::~Order()
{
    
    this->maxItems = 0;
    
    this->numItems = 0;
    
    delete [] this->itemsp;
    
}