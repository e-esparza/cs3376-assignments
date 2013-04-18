//
//  SeatSelection.h
//  Assignment3
//
//  Created by Michael Muggler on 3/24/13.
//  Copyright (c) 2013 Michael Muggler. All rights reserved.
//

#ifndef __Assignment3__SeatSelection__
#define __Assignment3__SeatSelection__

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class SeatSelection {
    
private:
    std::vector<std::vector<std::string>> seats;
    int total;
    
public:
    SeatSelection(int startingRow, int rowCount);
    void assignSeats(int seatCount);
    int getAvailableSeats();
    
};

#endif /* defined(__Assignment3__SeatSelection__) */
