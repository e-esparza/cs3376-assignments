#ifndef WAITER_H
#define WAITER_H

#include <string>
#include "Table.h"

class Table; // to take care of circular reference.

class Waiter
{
private:
	string name;	// waiter's name
    int index; // current index of tables
	int numTables;	// number of tables waiter is in-charge for
	Table **tables;	// waiter's table list
    void extendTablesArray(void);

public:
	Waiter(string name, int tableCount=1);
    void addTable(Table * table);
    void printTables(void); // used for debugging
    string getName(void);
    int getAssignedTables(void);
    ~Waiter();
};

class WaiterManager
{
private:
    Waiter ** waiters;
    int index;
    int size;
    void expandArray(void);
    
public:
    WaiterManager();
    Waiter * addWaiter(string aName);
    Waiter * getWaiterWithName(string aName);
    Waiter * getWaiterAtIndex(int anIndex);
    int count(void);
    void printData(void);
    ~WaiterManager();
};

#endif