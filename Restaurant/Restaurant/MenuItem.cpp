#include "MenuItem.h"

MenuItem::MenuItem(string mcode, string mname, double mprice)
{
    
    this->code = string(mcode);
    
    this->name = string(mname);
    
    this->price = mprice;
    
}

MenuItem::MenuItem(MenuItem * item)
{
    
    this->code = string(item->code);
    
    this->name = string(item->name);
    
    this->price = item->price;
    
}

bool MenuItem::isCode(string code)
{
    
    return ( this->code == code );
    
}

void MenuItem::printItemData()
{
    
    cout << "MenuItem (Item ID: " << this->code << ", Item Name: " << this->name << ", Item Price: " << this->price << ")" << endl;
    
}

void MenuItem::setName(string name)
{
    
    if ( name.length() == 0 ) return;
    
    this->name = string(name);
    
}

double MenuItem::getPrice()
{
    
    return this->price;
    
}