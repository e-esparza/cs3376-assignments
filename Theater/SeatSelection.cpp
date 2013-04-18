//
//  SeatSelection.cpp
//  Assignment3
//
//  Created by Michael Muggler on 3/24/13.
//  Copyright (c) 2013 Michael Muggler. All rights reserved.
//

#include "SeatSelection.h"

using namespace std;

SeatSelection::SeatSelection(int startingRow, int rowCount)
{
    
    total = rowCount*10;
    
    for( int i = 0; i < rowCount; i++ )
    {
        
        vector<string> row;
        
        row.push_back("J");
        row.push_back("I");
        row.push_back("H");
        row.push_back("G");
        row.push_back("F");
        row.push_back("E");
        row.push_back("D");
        row.push_back("C");
        row.push_back("B");
        row.push_back("A");
        
        seats.push_back(row);
        
    }
    
}

void SeatSelection::assignSeats(int seatCount)
{
    
    if( seatCount > 10 ) {
        cout << "Sorry, your reservation size cannot exceed 10." << endl;
        return;
    }
    
    if( total <= 0 ) {
        cout << "Sorry, not enough seats. Please come again!" << endl;
        return;
    }
    
    if( (total-seatCount) < 0 ) {
        cout << "Sorry, only " << total << ((total > 1) ? " seats are " : " seat is ") << "available." << endl;
        return;
    }
    
    cout << "Your seats are: ";
    
    while( seatCount > 0 )
    {
        
        bool found;
        found = false;
        
        int rowIndex;
        
        for( rowIndex = 0; rowIndex < seats.size(); rowIndex++ )
        {
            
            std::vector<string>::reverse_iterator rit = seats[rowIndex].rbegin();
            
            for (rit = seats[rowIndex].rbegin(); rit!= seats[rowIndex].rend(); ++rit) {
                
                cout << (rowIndex+1) << *rit << " ";
                
                found = true;
                seatCount--;
                total--;
                
                seats[rowIndex].pop_back();
                
                if ( found ) break;
                
            }
            
            if( found ) break;
            
        }
        
    }
    
    cout << endl;
    
}

int SeatSelection::getAvailableSeats()
{
    return total;
}