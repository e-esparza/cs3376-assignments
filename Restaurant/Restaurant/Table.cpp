#include "Table.h"

Table::Table(int tblid, int mseats)
{
    
    this->tableId = tblid;
    
    this->maxSeats = mseats;
    
    this->status = IDLE;
    
    this->numPeople = 0;
    
    this->order = NULL;
    
    this->waiter = NULL;
    
}

void Table::assignWaiter(Waiter *person)
{
    
    this->waiter = person;
    
}

void Table::partySeated(int npeople)
{
    
    if( this->waiter == NULL ) return;
    
    if( npeople > this->maxSeats ) return; // We cannot seat more than we have.
    
    this->status = SEATED;
    
    this->numPeople = npeople;
    
}

void Table::partyOrdered(Order *order)
{
    
    if ( this->status != SEATED || order == NULL ) return;
    
    if( this->order != NULL ) {
        delete this->order;
    }
    
    this->order = order;
    
    this->status = ORDERED;
    
}

void Table::partyServed()
{
    
    if ( this->status != ORDERED ) return;
    
    this->status = SERVED;
    
}

void Table::printTableStatus()
{
    
    cout << "~~~Begin Status Report for Table " << this->tableId << "~~~" << endl;
    
    cout << "Table ID: " << this->tableId << endl;
    
    cout << "Capacity: " << this->maxSeats << endl;
    
    if ( this->waiter == NULL ) {
        cout << "Waiter: (Not Assigned)" << endl;
    } else {
        cout << "Waiter: " << this->waiter->getName() << endl;
    }
    
    string stat;
    
    if ( this->status == IDLE ) stat = "Table is empty.";
    else if ( this->status == SEATED ) stat = "People have been seated.";
    else if ( this->status == ORDERED ) stat = "People have placed an order.";
    else if ( this->status == SERVED ) stat = "People served and waiting for checkout.";
    else stat = "(Unknown Status)";
    
    cout << "Status: " << stat << endl;
    
    if ( this->status == SEATED || this->status == ORDERED || this->status == SERVED ) {
        cout << "Party Size: " << this->numPeople << endl;
    }
    
    if ( this->status == ORDERED || this->status == SERVED ) {
        cout << "Order Subtotal: $" << this->order->getOrderTotal() << endl;
    }
    
    cout << "~~~End Status Report for Table " << this->tableId << "~~~" << endl;
    
}

void Table::partyCheckout()
{
    
    if ( this->status != SERVED ) return;
    
    this->status = IDLE;
    
    cout << "~~~Begin Receipt for Table " << this->tableId << " Closed by " << this->waiter->getName() << "~~~~" << endl;
    
    int percentFull = 0.0;
    
    percentFull = (int)((this->numPeople/(double)this->maxSeats)*100.0);
    
    cout << "Table Size: " << this->numPeople << " of " << this->maxSeats << " (" << percentFull << "%)" << endl;
    
    this->order->printOrderData();
    
    cout << "Subtotal: $" << this->order->getOrderTotal() << endl;
    
    double tax;
    
    tax = 0.0825;
    
    tax *= this->order->getOrderTotal();
    
    cout << "Tax: $" << tax << " (8.25% Tx)" << endl;
    
    double tip;
    
    tip = (this->numPeople >= 6) ? 0.20 : 0.15;
    
    tip *= this->order->getOrderTotal();
    
    cout << "Tip: $" << tip << " (" << ( (this->numPeople >= 6) ? "20% (for parties of 6 or more)" : "15%" ) << ")" << endl;
    
    cout << "Total: $" << (this->order->getOrderTotal()+tax+tip) << endl;
    
    cout << "~~~End Receipt for Table " << this->tableId << " Closed by " << this->waiter->getName() << "~~~~" << endl;
    
    this->order = NULL;
    
    this->numPeople = 0;
    
}

int Table::getTableId()
{
    return this->tableId;
}

int Table::getCapacity()
{
    return this->maxSeats;
}

string Table::getWaiterName()
{
    
    if( this->waiter == NULL ) return "(Not assigned.)";
    
    else return string(this->waiter->getName());
    
}

Table::~Table()
{
    
    this->tableId = 0;
    
    this->maxSeats = 0;
    
    this->numPeople = 0;
    
    if( this->order != NULL ) delete this->order;
    
    this->order = NULL;
    
    this->waiter = NULL;
    
}

TableManager::TableManager()
{
    
    this->index = 0;
    
    this->size = 1;
    
    this->tables = new Table * [1];
    
}

void TableManager::addTable(int tableId, int capacity)
{
    
    if( tableId < 0 || capacity < 0 ) return;
    
    if( this->index == this->size ) {
        this->expandArray();
    }
    
    this->tables[this->index] = new Table(tableId, capacity);
    
    this->index++;
    
}

void TableManager::expandArray()
{
    
    Table ** newArray = new Table * [(this->size+1)];
    
    for( int i = 0; i < this->index; i++ )
    {
        
        newArray[i] = this->tables[i];
        
    }
    
    delete [] this->tables;
    
    this->tables = newArray;
    
    this->size++;
    
}

Table * TableManager::getTableWithId(int aTableId)
{
    
    if ( aTableId < 0 ) return NULL;
    
    for( int i = 0; i < this->index; i++ )
    {
        
        Table * table = this->tables[i];
        
        if ( table != NULL && table->getTableId() == aTableId ) return table;
        
    }
    
    return NULL;
    
}

Table * TableManager::getTableAtIndex(int anIndex)
{
    
    if( anIndex < 0 || anIndex >= this->index ) return NULL;
    
    return this->tables[anIndex];
    
}

int TableManager::count(void)
{
    return this->index;
}

void TableManager::printData()
{
    
    cout << "~~~~Begin TableManager Tables Listing for " << this->index << " Objects~~~~" << endl;
    
    for( int i = 0; i < this->index; i++ ) {
        
        Table * table = this->tables[i];
        
        string waiter = table->getWaiterName();
        
        cout << "Table (Id: " << table->getTableId() << ", Capacity: " << table->getCapacity() << ", Waiter: " << waiter << ")" << endl;
        
    }
    
    cout << "~~~~End TableManager Tables Listing for " << this->index << " Objects~~~~" << endl;
    
}

TableManager::~TableManager()
{
    
    for( int i = 0; i < this->index; i++ ) {
        delete this->tables[i];
    }
    
    delete [] this->tables;
    
}
