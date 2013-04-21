#ifndef TABLE_H
#define TABLE_H
#include "Order.h"
#include "Waiter.h"

enum TableStatus { IDLE = 0, SEATED = 1, ORDERED = 2, SERVED = 3 };

/*
 In addition to processing these commands, when a table is closed, display the check as well. Include table #, waiter name, # of customers in the party, name and price of each ordered item and the total. No need to worry about tax or tips.
 */

class Waiter; // to take care of circular reference.

class Table 
{
private:
	int tableId;		// table number
    int maxSeats;	// table seat capacity
	TableStatus status;	// current status, you can use assign like
				// status = IDLE;
	int numPeople;		// number of people in current party
	Order *order;		// current party's order
	Waiter *waiter;		// pointer to waiter for this table

public:
	Table(int tblid =0, int mseats = 0);	// initialization, IDLE
	void assignWaiter(Waiter *person); 	// initially no waiter
	void partySeated(int npeople);		// process IDLE --> SEATED
	void partyOrdered(Order *order);	// process SEATED --> ORDERED
	void partyServed(void);			// process ORDERED --> SERVED
	void partyCheckout(void);		// process SERVED --> IDLE
    void printTableStatus(void);
    int getTableId(void);
    int getCapacity(void);
    string getWaiterName(void);
    ~Table();
};

class TableManager
{
private:
    Table ** tables;
    int index;
    int size;
    void expandArray(void);
    
public:
    TableManager();
    void addTable(int tableId, int capacity);
    Table * getTableWithId(int aTableId);
    Table * getTableAtIndex(int anIndex);
    int count(void);
    void printData(void);
    ~TableManager();
};

#endif
