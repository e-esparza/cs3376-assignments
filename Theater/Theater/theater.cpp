//
//  main.cpp
//  Assignment3
//
//  Created by Michael Muggler on 3/24/13.
//  Copyright (c) 2013 Michael Muggler. All rights reserved.
//

#include <iostream>
#include "SeatSelection.h"

using namespace std;

int main(int argc, const char * argv[])
{

    
    SeatSelection premium(1, 5);
    SeatSelection regular(6, 15);
    
    while (true) {
        
        if( premium.getAvailableSeats() == 0 && regular.getAvailableSeats() == 0 )
        {
            cout << "Sorry, not enough seats. Please come again!" << endl;
            break;
        }
        
        int mode, seats;
        
        // Get and validate the mode
        while (true) {
            
            cout << "Premium(1) or Regular(2): ";
            cin >> mode;
            
            if ( mode == 1 || mode == 2 ) break;
            
        }
        
        // Get Seats
        cout << "# of tickets: ";
        cin >> seats;
        
        (( mode == 1 ) ? premium : regular).assignSeats(seats);
        
    }
    
    return 0;
}

