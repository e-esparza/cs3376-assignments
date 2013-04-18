#include "Menu.h"

Menu::Menu(int items)
{
    
    if ( items <= 0 ) items = MENU_DEFAULT_ITEMS_SIZE;
    
    this->maxItems = items;
    
    this->numItems = 0;
    
    this->menup = new MenuItem[this->maxItems];
    
}

void Menu::addItem(MenuItem item)
{
    
    // We cannot add anymore menu items.
    if ( this->maxItems == this->numItems ) {
        this->extendMenuItemArray();
    }
    
    this->menup[this->numItems] = MenuItem(item);
    
    this->numItems++; // Increment total number of items.
    
}

void Menu::extendMenuItemArray()
{
    
    MenuItem * newArray = new MenuItem[(this->maxItems+1)];
    
    for( int i = 0; i < this->numItems; i++ ) {
        
        newArray[i] = MenuItem(this->menup[i]);
        
    }
    
    delete [] this->menup;
    
    this->menup = newArray;
    
    this->maxItems++;

}

void Menu::printMenuItems()
{
    
    cout << "~~~~Begin Menu~~~~" << endl;
    
    for( int i = 0; i < this->numItems; i++ ) {
        
        this->menup[i].printItemData();
        
    }
    
    cout << "~~~~End Menu~~~~" << endl;
    
}

MenuItem * Menu::findItem(string code)
{
    
    if ( code.length() == 0 ) return NULL;
    
    for( int i = 0; i < this->numItems; i++ )
    {
        
        MenuItem * item = &this->menup[i];
        
        if ( item->isCode(code) )
        {
            return item;
        }
        
    }
    
    return NULL;
    
}

Menu::~Menu()
{
    
    this->maxItems = 0;
    this->numItems = 0;
    
    delete [] this->menup;
    
}