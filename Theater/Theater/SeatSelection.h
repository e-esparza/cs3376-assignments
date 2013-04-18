//
//  SeatSelection.h
//  Theater
//
//  Created by Michael Müggler on 4/13/13.
//  Copyright (c) 2013 Taptivia. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#ifndef SeatSelection_H
#define SeatSelection_H

class SeatSelection {
    
private:
    std::vector<std::vector<std::string> > seats;
    int total;
    int startingRow;
    
public:
    SeatSelection(int startingRow, int rowCount);
    void assignSeats(int seatCount);
    int getAvailableSeats();
    
};

#endif
