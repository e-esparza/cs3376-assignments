//
//  game.h
//  Guess The Number
//
//  Created by Michael Müggler on 2/2/13.
//  Copyright (c) 2013 Michael Muggler. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define kMaximumRange 100

// Represents a single game.
struct Game {
    
    // The total number of guesses made during the duration of the game.
    unsigned int guesses;
    
    // Indicates if the computer failed to guess the number.
    bool failed;
    
    // Array containing all the possible guesses that can be made.
    unsigned int range[kMaximumRange];
    
    // The correct guess that the computer made.
    unsigned int answer;
    
};

typedef struct Game Game;


enum GamePromptResult {
    
    // Less than (<) indicates that the users number is less than the computers guess.
	GamePromptResultLessThan,
    
    // Greater than (>) indicates that the users number is greater than the computers guess.
	GamePromptResultGreaterThan,
    
    // Equals (=) indicates that the users guess is equal to the computers guess.
	GamePromptResultEqual,

};

typedef enum GamePromptResult GamePromptResult;

// Creates a blank Game with all values initialized to defaults.
// Returns a Game struct.
Game GameMake();

// Asks the user if the computers guess is less than, equal to
// or greater than the number they picked and returns that result
// expressed as the enumerated GamePromptResult values.
GamePromptResult GamePromptUser(unsigned int guess);

// Asks the user if he or she would like to play another game.
// Returns a boolean value indicating the response of the user.
bool GamePromptUserNewGame();

// Increments the guess count for the game. This method is called
// each time the computer makes a guess.
void GameIncrementGuessCount(Game * game);

// Begins the prompt and guess loop. This method implements a
// binary search algorithm to guess the number the user is thinking
// of in the most efficient way possible.
void GamePlay(Game * game);

// Prints the game results. This method can be used for debugging,
// however it is called when the user finishes the game reguardless
// of the result.
void GameInformationPrint(Game * game);

// Prints the total number of games played, the total number of
// guesses made and the average number of guesses per game.
void GameAveragesPrint(unsigned int games, unsigned int guesses);