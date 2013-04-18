#include "Waiter.h"


Waiter::Waiter(string name, int tableCount)
{
    
    if ( name.length() == 0 || &name == NULL ) {
        throw "Cannot create waiter without a name!";
    }
    
    this->name = string(name);
    
    this->index = 0;
    
    this->numTables = tableCount;
    
    this->tables = new Table * [this->numTables];
    
}

void Waiter::addTable(Table * table)
{
    
    if( this->numTables == this->index ) {
        this->extendTablesArray();
    }
    
    this->tables[this->index] = table;
    
    table->assignWaiter(this);
    
    index++;
    
}

void Waiter::extendTablesArray()
{
    
    Table ** newArray = new Table * [(this->numTables+1)];
    
    for( int i = 0; i < this->index; i++ )
    {
        
        newArray[i] = this->tables[i];
        
    }
    
    delete [] this->tables;
    
    this->tables = newArray;
    
    this->numTables++;
    
}

void Waiter::printTables()
{
    
    cout << "~~~~Start of " << this->name << "'s Tables~~~~" << endl;
    
    for( int i = 0; i < this->index; i++ )
    {
        
        Table * table = this->tables[i];
        
        cout << "Table (ID: " << table->getTableId() << ", Capacity: " << table->getCapacity() << ")" << endl;
        
    }
    
    cout << "~~~~End of " << this->name << "'s Tables~~~~" << endl;
    
}

int Waiter::getAssignedTables()
{
    return this->numTables;
}

string Waiter::getName()
{
    
    return string(this->name);
    
}

Waiter::~Waiter()
{
    
    this->index = 0;
    
    this->numTables = 0;
    
    delete [] tables;
    
}

WaiterManager::WaiterManager()
{
    
    this->index = 0;
    
    this->size = 1;
    
    this->waiters = new Waiter * [1];
    
}

Waiter * WaiterManager::addWaiter(string aName)
{
    
    if( aName.length() == 0 ) return NULL;
    
    if( this->index == this->size ) {
        this->expandArray();
    }
    
    this->waiters[this->index] = new Waiter(aName);
    
    Waiter * waiter = this->waiters[this->index];
    
    this->index++;
    
    return waiter;
    
}

void WaiterManager::expandArray()
{
    
    Waiter ** newArray = new Waiter * [(this->size+1)];
    
    for( int i = 0; i < this->index; i++ )
    {
        
        newArray[i] = this->waiters[i];
    
    }
    
    delete [] this->waiters;
    
    this->waiters = newArray;
    
    this->size++;
    
}

Waiter * WaiterManager::getWaiterWithName(string aName)
{
    
    if ( aName.length() == 0 ) return NULL;
    
    for( int i = 0; i < this->index; i++ )
    {
        
        Waiter * waiter = this->waiters[i];
        
        if ( waiter != NULL && waiter->getName() == aName ) return waiter;
        
    }
    
    return NULL;
    
}

Waiter * WaiterManager::getWaiterAtIndex(int anIndex)
{
    
    if( anIndex < 0 || anIndex >= this->index ) return NULL;
    
    return this->waiters[anIndex];
    
}

int WaiterManager::count(void)
{
    return this->index;
}

void WaiterManager::printData()
{
    
    cout << "~~~~Begin WaiterManager Waiters Listing for " << this->index << " Objects~~~~" << endl;
    
    for( int i = 0; i < this->index; i++ ) {
        
        Waiter * waiter = this->waiters[i];
        
        cout << "Waiter (Name: " << waiter->getName() << ", Tables: " << waiter->getAssignedTables() << ")" << endl;
        
        waiter->printTables();
        
    }
    
    cout << "~~~~End WaiterManager Waiters Listing for " << this->index << " Objects~~~~" << endl;
    
}

WaiterManager::~WaiterManager()
{
    
    for( int i = 0; i < this->index; i++ ) {
        delete this->waiters[i];
    }
    
    delete [] this->waiters;
    
}