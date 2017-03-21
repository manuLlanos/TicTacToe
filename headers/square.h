
#ifndef SQUARE_H
#define SQUARE_H

#include <SDL2/SDL.h>
#include "../headers/constants.h"

//This class represents a square of the tic-tac-toe board
class LSquare{
	squareStates mSquareState;
	int xPos;
	int yPos;
	public:
		LSquare();
		
		void setPos(int, int);
		
		//returns true if the player made a move
		bool handleMouseInput(int, int);
		
		//this will only be used by the AI
		void placeCircle();
		
		void render();
		
		void empty();
		
		squareStates getState();
		
};

#endif
