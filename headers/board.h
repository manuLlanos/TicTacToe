
#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>
#include "../headers/square.h"
#include "../headers/constants.h"

class LBoard{
	//array of 9 squares (going from left to right, then from top to bottom)
	LSquare mSquares[TOTAL_SQUARES];
	gameStates mGameState;
	gameStates mWinner;
	int mMoves;
	public:
		LBoard();
	
		void restart();
		
		void render();
		
		void handleEvent( SDL_Event *);
		
		gameStates getGameState();
		
		//this functions checks if there is a winner, used to end the game/ change turns
		//Returns true if someone won, and changes the state of the game accordingly
		bool someoneWon();
		
		//just sets the game state to wait, so it waits for the player to quit or hit space to continue
		void gameOver()
		{
			mWinner = mGameState;
			mGameState = GAME_WAIT;
		}
		
		void AImove();
};

#endif
