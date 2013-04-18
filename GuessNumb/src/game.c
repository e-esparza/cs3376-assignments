//
//  game.c
//  Guess The Number
//
//  Created by Michael Müggler on 2/2/13.
//  Copyright (c) 2013 Michael Muggler. All rights reserved.
//

#include "game.h"
#include "prefix.h"

Game GameMake()
{
    
    Game game;
    
    game.guesses = 0;
    
    game.failed = false;
    
    game.answer = 0;
    
    unsigned int i;
    
    for ( i = 0; i < kMaximumRange; i++ ) {
        
        game.range[i] = (i+1);
        
#if DEBUG
        printf("DEBUG: range[%u] = %u\n", i, game.range[i]);
#endif
        
    }
    
    return game;
    
}

GamePromptResult GamePromptUser(unsigned int guess)
{
    
    char promptData;
    
	int scanResultData;
	scanResultData = EOF;
	
	while ( scanResultData == EOF ) // While scanf has not been called or has not received data.
	{
        
		printf("Is it %u (<, =, >)? ", guess);
        
		scanResultData = scanf("%1s", &promptData);
        
		if ( promptData == '<' ) {
			
#if DEBUG
            printf("DEBUG: Input is <\n");
#endif
			
            return GamePromptResultLessThan;
			
		}
        
        else if ( promptData == '>' ) {

#if DEBUG
            printf("DEBUG: Input is >\n");
#endif
            
			return GamePromptResultGreaterThan;
			
		}
        
        else {
        
#if DEBUG
            printf("DEBUG: Input is =\n");
#endif
            
			return GamePromptResultEqual;
			
		}
        
		printf("\n");
        
	}
	
#if DEBUG
    printf("DEBUG: Input is = BUT FELL OF THE LOOP\n");
#endif
    
	return GamePromptResultEqual; // Default case if scanner had an unknown error.
    
}

bool GamePromptUserNewGame()
{
    
    bool playAgain;
    playAgain = false;
    
    char promptData;
    
	int scanResultData;
	scanResultData = EOF;
    
    
    while ( scanResultData == EOF ) // While scanf has not been called or has not received data.
	{
        
		printf("Would you like to play another game (Y/N)? ");
        
		scanResultData = scanf("%1s", &promptData);
        
		if ( promptData == 'Y' || promptData == 'y' ) {
			
            playAgain = true;
			
		}
        
		printf("\n");
        
	}
    
    return playAgain;
    
}

void GameIncrementGuessCount(Game * game)
{
    
    unsigned int guesses;
    
    guesses = game->guesses;
    
    game->guesses = ( guesses + 1 );
    
    return;
    
}

void GamePlay(Game * game)
{
    
    // first - The starting index of the array.
    // last - The ending index of the array.
    // middle - The midpoint numbers of the array.
    int first, last, middle;
    
    // Set the first index to 0 to begin the binary search.
    first = 0;
    
    // The last index is the range of numbers - 1, so if we have 10 possible numbers we get last index of 9.
    last = (kMaximumRange-1);
    
    // The middle index should be between the first and last.
    middle = ( first + last ) / 2;
    
    while( first <= last ) {
        
        unsigned int guess;
        guess = game->range[middle];
        
        GameIncrementGuessCount(game);
        
        GamePromptResult prompt;
        prompt = GamePromptUser(guess);
        
        game->answer = guess;
        
        if ( prompt == GamePromptResultGreaterThan ) {
            
            first = middle + 1;
            
        }
        
        else if ( prompt == GamePromptResultLessThan ) {
            
            last = middle - 1;
            
        }
        
        else {
            
            break; // We have finished the game with an equality.
            
        }
        
        middle = ( first + last ) / 2;
        
    }
    
    // An error occurred where the number was never found.
    if ( first > last ) game->failed = true;
    
    return;
    
}

void GameInformationPrint(Game * game)
{
    
    printf("## Game Results\n");
    printf("#\n");
    printf("#    Guesses: %u\n", game->guesses);
    
    if ( game->failed ) printf("#    Result: Undetermined\n");
    else printf("#    Result: %u\n", game->answer);
    
    printf("#\n");
    printf("##\n");
    
    return;

}

void GameAveragesPrint(unsigned int games, unsigned int guesses)
{
    
    float average;
    average = ((float)guesses);
    average /= games;
    
    printf("## Statistics\n");
    printf("#\n");
    printf("#    Games Played: %u\n", games);
    printf("#    Total Guesses: %u\n", guesses);
    printf("#    Average Guesses: %f\n", average);
    printf("#\n");
    printf("##\n");
    
    return;
    
}