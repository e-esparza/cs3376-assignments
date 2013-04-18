#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

#include "MenuItem.h"
#include "Menu.h"
#include "Order.h"
#include "Waiter.h"
#include "Table.h"

using namespace std;

enum ConfigTokenizationSection {
    ConfigTokenizationSectionTables,
    ConfigTokenizationSectionWaiters,
    ConfigTokenizationSectionMenu,
    ConfigTokenizationSectionNull
};

int main(int argc, const char * argv[])
{
    
    // Create the menu storage object.
    Menu * menu = new Menu();
    
    // Create the table storage object.
    TableManager * tableManager = new TableManager();
    
    // Create the waiter storage object.
    WaiterManager * waiterManager = new WaiterManager();
    
    ifstream input("config.txt");
    string line;
    
    ConfigTokenizationSection mode;
    
    mode = ConfigTokenizationSectionNull;
    
    // Current table data. Used when parsing for tables.
    int tableId, tableCapacity;
    
    tableId = -1; // default
    tableCapacity = -1; // default
    
    // Current waiter data. Used when parsing for waiters.
    string waiterName;
    string assignedTables;
    
    // Current menu item data. Used when parsing for menu items.
    string itemId;
    string itemName;
    double itemPrice;
    
    itemPrice = -0.0; // default
    
    while(getline(input, line))
    {
        
        istringstream iss(line);
        
        string token;
        
        while (iss >> token)
        {
            
            // If token is 'Tables:'
            if ( token == "Tables:" ) {
                
                mode = ConfigTokenizationSectionTables;
                continue; // We can skip to the next token.
                
            }
            
            // If token is 'Waiters:'
            else if ( token == "Waiters:" ) {
                
                mode = ConfigTokenizationSectionWaiters;
                continue; // We can skip to the next token.
                
            }
            
            // If token is 'Menu:'
            else if ( token == "Menu:" ) {
                
                mode = ConfigTokenizationSectionMenu;
                continue; // We can skip to the next token.
                
            }
            
            // We're looking for the next two tokens to tell us to assign a table id
            // and the capacity of the table.
            if ( mode == ConfigTokenizationSectionTables ) {
                
                // Each iteration of the loop will grab the first token which is the table id
                // and the iteration + 1 of the loop will grab the second token which is the
                // maximum capacity of the table, followed by the end of line.
                
                // If the tableId is filled then the token is the capcity. Otherwise the token
                // is the tableId. If the tableId and capacity are filled and they havent been
                // cleared to default values we must have some sort of error or extra tokens
                // in which case those will be ignored.
                
                // If tableId is our default value we need to fill it with the atoi of the token.
                if ( tableId == -1 ) {
                    
                    tableId = atoi(token.c_str());
                    
                    // We cannot have a negative table id. If we assign a table id.
                    if ( tableId < 0 ) tableId *= -1;
                    
                    // the tableId is filled so now it is time to fill the capacity if not filled already.
                } else {
                    
                    if ( tableCapacity == -1 ) {
                        
                        tableCapacity = atoi(token.c_str());
                        
                        // We cannot have a negative capacity. Make it positive.
                        if ( tableCapacity < 0 ) tableCapacity *= -1;
                        
                    }
                    
                }
                
            }
            
            // We're looking for waiters. For this we are going to take the first token which
            // is a string, the the following tokens will be integers.
            else if ( mode == ConfigTokenizationSectionWaiters ) {
                
                // If we don't have a waiter name. We determine this by the length being 0.
                if ( waiterName.length() == 0 ) {
                    
                    waiterName.append(token);
                    
                    // the waiter name is filled so now we just need to collect the table ids
                    // the waiter is waiting.
                } else {
                    
                    assignedTables.append(token).append(",");
                    
                }
                
            }
            
            // We're looking for menu items. So the first token is the menu item ID, followed
            // by the name of the menu item, followed by the price (as a double).
            else if ( mode == ConfigTokenizationSectionMenu ) {
                
                // If we don't have an Id then we need that first.
                if ( itemId.length() == 0 ) {
                    
                    itemId.append(token);
                    
                    // We have the Id so now we need the menu name.
                } else {
                    
                    // If we don't have a name we need that.
                    if ( itemName.length() == 0 ) {
                        
                        itemName.append(token);
                        
                        // we have a name so now we need to parse the amount.
                    } else {
                        
                        itemPrice = atof(token.c_str());
                        
                        // The price cannot be negative so lets make it positive.
                        if ( itemPrice < 0.0 ) itemPrice *= -1.0;
                        
                    }
                    
                }
                
            }
            
        }
        
        // If we're in table parsing mode and the tableId and tableCapacity are not at defaults,
        // then we have a table to add to the database.
        if ( mode == ConfigTokenizationSectionTables && tableId != -1 && tableCapacity != -1 ) {
            
            tableManager->addTable(tableId, tableCapacity);
            
            // Set table id and capacity to default values for next go around.
            tableId = -1;
            tableCapacity = -1;
            
        }
        
        // If we're parsing for waiters and the we have a waiter with a name (i.e. the string length is
        // not 0) then we need to create a new waiter. Note we need to set the waiter name and tables
        // to new blank strings again.
        else if ( mode == ConfigTokenizationSectionWaiters && waiterName.length() != 0 )
        {
            
            // When we appended all the id tokens.
            
            cout << "New Waiter! (Name: " << waiterName << " Tables: " << assignedTables << ")" << endl;
            waiterManager->addWaiter(waiterName);
            
            // Set to defaults for next line.
            waiterName = string();
            assignedTables = string();
            
        }
        
        // If we're parsing menu items and we have all the require information, which we should, then
        // we can go ahead and make a menu item.
        else if ( mode == ConfigTokenizationSectionMenu && itemId.length() != 0 && itemName.length() != 0 && itemPrice != -0.0 )
        {
            
            //cout << "New Menu Item! (Id: " << itemId << " Name: " << itemName << " Price: " << itemPrice << ")" << endl;
            
            menu->addItem(MenuItem(itemId, itemName, itemPrice));
            
            // set defaults for next line.
            itemId = string();
            itemName = string();
            itemPrice = -0.0;
            
        }
        
    }
    
    // Some debugging information about the total objects managed.
    menu->printMenuItems();
    tableManager->printData();
    waiterManager->printData();
    
    // Deallocate memory that stores the table manager.
    delete tableManager;
    
    // Deallocate memory that stores the waiters.
    delete waiterManager;
    
    // Deallocate memory that stores the menu items.
    delete menu;
    
    return 0;
    
}
