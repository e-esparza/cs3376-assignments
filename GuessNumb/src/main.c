//
//  main.c
//  Guess The Number
//
//  Created by Michael Müggler on 2/2/13.
//  Copyright (c) 2013 Michael Muggler. All rights reserved.
//

#include "main.h"
#include "game.h"

int main(int argc, const char * argv[])
{
    
    unsigned int totalGames;
    totalGames = 0;
    
    unsigned int totalGuesses;
    totalGuesses = 0;
    
    bool playing;
    playing = true;
    
    while ( playing ) {
        
        Game game;
        game = GameMake();
        
        printf("Think of a number between 1 and %u (inclusive).\n", kMaximumRange);
        GamePlay(&game);
        
        GameInformationPrint(&game);
        
        totalGames += 1;
        
        totalGuesses += game.guesses;
        
        playing = GamePromptUserNewGame();
        
    }
    
    GameAveragesPrint(totalGames, totalGuesses);
    
    return 0;
    
}

