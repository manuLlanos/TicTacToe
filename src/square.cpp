
#include "../headers/square.h"
#include "../headers/globals.h"

LSquare::LSquare()
{
	mSquareState = SQUARE_EMPTY;
	xPos = 0;
	yPos = 0;
}

void LSquare::setPos(int x, int y)
{
	xPos = x;
	yPos = y;
}


bool LSquare::handleMouseInput(int x, int y)
{
	//This function will only be called if its the player's turn and he/she clicks INSIDE the board.
	//This makes each button of the board check if it was clicked and then act.
	//Only empty squares will check
	bool validMove = false;
	
	if( mSquareState == SQUARE_EMPTY)
	{
		bool inside = true;
		
		if(x < xPos)
			inside = false;
		else if(x > xPos + SQUARE_SIZE)
			inside = false;
		else if(y < yPos)
			inside = false;
		else if(y > yPos + SQUARE_SIZE)
			inside = false;
			
		if( inside )
		{
			validMove = true;
			mSquareState = SQUARE_CROSS;
		}
			
	}
	
	return validMove;
}

//function only used by the AI
void LSquare::placeCircle()
{
	if(mSquareState == SQUARE_EMPTY)
		mSquareState = SQUARE_CIRCLE;
}


void LSquare::render()
{
	if( mSquareState == SQUARE_CROSS)
		gSpriteSheetTexture.render(xPos, yPos, &gSpriteQuads[0]);
	
	else if( mSquareState == SQUARE_CIRCLE)
		gSpriteSheetTexture.render(xPos, yPos, &gSpriteQuads[1]);
}


void LSquare::empty()
{
	mSquareState = SQUARE_EMPTY;
}


squareStates LSquare::getState()
{
	return mSquareState;
}

