
#include "../headers/board.h"
#include "../headers/Random.h"
#include <stdio.h>
#include "../headers/globals.h"

LBoard::LBoard()
{
	mGameState = GAME_PLAYER_TURN;
	mWinner = GAME_DRAW;
	mMoves = 0;
	
	//set the position of each square, made this way to center the board to the screen
	mSquares[0].setPos(BOARD_POS_X , BOARD_POS_Y);
	mSquares[1].setPos(BOARD_POS_X + SQUARE_SIZE, BOARD_POS_Y);
	mSquares[2].setPos(BOARD_POS_X + 2*SQUARE_SIZE, BOARD_POS_Y);
	mSquares[3].setPos(BOARD_POS_X , BOARD_POS_Y + SQUARE_SIZE);
	mSquares[4].setPos(BOARD_POS_X + SQUARE_SIZE, BOARD_POS_Y + SQUARE_SIZE);
	mSquares[5].setPos(BOARD_POS_X + 2*SQUARE_SIZE, BOARD_POS_Y + SQUARE_SIZE);
	mSquares[6].setPos(BOARD_POS_X , BOARD_POS_Y + 2*SQUARE_SIZE);
	mSquares[7].setPos(BOARD_POS_X + SQUARE_SIZE, BOARD_POS_Y + 2*SQUARE_SIZE);
	mSquares[8].setPos(BOARD_POS_X + 2*SQUARE_SIZE, BOARD_POS_Y + 2*SQUARE_SIZE);
	
}


void LBoard::restart()
{
	mGameState = GAME_PLAYER_TURN;
	mMoves = 0;
	
	//clear all the squares
	for(int i = 0; i < TOTAL_SQUARES; i++)
		mSquares[i].empty();
}


void LBoard::render()
{
	//first render the board, then the squares
	gSpriteSheetTexture.render(BOARD_POS_X, BOARD_POS_Y, &gSpriteQuads[2]);
	
	for(int i = 0; i < TOTAL_SQUARES; i++)
		mSquares[i].render();
		
		
	//rendered text if the game is over
	if(mGameState == GAME_WAIT)
	{
		gRestartTextTexture.render( 0, 0);
		
		switch(mWinner)
		{
			case GAME_DRAW:
				gDrawTextTexture.render( (SCREEN_WIDTH - gDrawTextTexture.getWidth())/2, SCREEN_HEIGHT - FONT_SIZE - 20);
				break;
				
			case GAME_AI_WINS:
				gAiWinsTextTexture.render( (SCREEN_WIDTH - gAiWinsTextTexture.getWidth())/2, SCREEN_HEIGHT - FONT_SIZE - 20);
				break;
		
			case GAME_PLAYER_WINS:
				gPlayerWinsTextTexture.render( (SCREEN_WIDTH - gPlayerWinsTextTexture.getWidth())/2, SCREEN_HEIGHT - FONT_SIZE - 20);
				break;
		}
	}
		
}


void LBoard::handleEvent( SDL_Event *e)
{
	bool madeMove = false;

	if( e->type == SDL_MOUSEBUTTONDOWN)
	{
		bool insideBoard = true;
		int x, y;
		
		SDL_GetMouseState(&x, &y);
		
		if(x < BOARD_POS_X)
			insideBoard = false;
		else if(x > BOARD_POS_X + BOARD_SIZE)
			insideBoard = false;
		else if(y < BOARD_POS_Y)
			insideBoard = false;
		else if(y > BOARD_POS_Y + BOARD_SIZE)
			insideBoard = false;
		
		//if a mouse button was clicked inside the board, check the squares.
		//Only if a valid move was made, the 
		if(insideBoard)
			for(int i = 0; i < TOTAL_SQUARES; i++)
				//returns true if a valid move was made
				 if( mSquares[i].handleMouseInput(x, y) )
				 	madeMove = true;
			
	}
	
	//If the player made a valid move, we increment the number of moves made to check if the game is over or not
	
	if(madeMove)
	{	
		mMoves ++;
		
		//the someoneWon function will set the game state to GAME_DRAW by itself
		//if it returns true, it will either set the game state to GAME_AI_WINS or GAME_PLAYER_WINS
		if( !someoneWon() && mMoves < 9)
			mGameState = GAME_AI_TURN;
	}
}


gameStates LBoard::getGameState()
{
	return mGameState;
}


bool LBoard::someoneWon()
{
	//the minimum amount of moves for someone to be able to win is 5
	/*
		0 1 2
		3 4 5
		6 7 8
	*/
	bool someoneWon = false;
	
	if(mMoves >= 5)
	{
		//check horizontal lines
		for(int i = 0; i < 7 && !someoneWon; i += 3)
			if( mSquares[i].getState() == mSquares[i+1].getState() && mSquares[i+1].getState() == mSquares[i+2].getState() && mSquares[i].getState() != SQUARE_EMPTY)
			{
				someoneWon = true;
				if(mSquares[i].getState() == SQUARE_CIRCLE)
					mGameState = GAME_AI_WINS;
				else
					mGameState = GAME_PLAYER_WINS;
			}
		
		//check vertical lines
		for(int i = 0; i < 3 && !someoneWon; i++)
			if( mSquares[i].getState() == mSquares[i+3].getState() && mSquares[i+3].getState() == mSquares[i+6].getState() && mSquares[i].getState() != SQUARE_EMPTY)
			{
				someoneWon = true;
				if(mSquares[i].getState() == SQUARE_CIRCLE)
					mGameState = GAME_AI_WINS;
				else
					mGameState = GAME_PLAYER_WINS;
			}
		
		//check diagonals
		if( mSquares[0].getState() == mSquares[4].getState() && mSquares[4].getState() == mSquares[8].getState() && mSquares[0].getState() != SQUARE_EMPTY && !someoneWon)
		{
			someoneWon = true;
			if(mSquares[0].getState() == SQUARE_CIRCLE)
				mGameState = GAME_AI_WINS;
			else
				mGameState = GAME_PLAYER_WINS;
		}
		else if( mSquares[2].getState() == mSquares[4].getState() && mSquares[4].getState() == mSquares[6].getState() && mSquares[2].getState() && !someoneWon)
		{
			someoneWon = true;
			if(mSquares[2].getState() == SQUARE_CIRCLE)
				mGameState = GAME_AI_WINS;
			else
				mGameState = GAME_PLAYER_WINS;
		}
		
				
	}
	
	if(mMoves >= 9 && !someoneWon)
		mGameState = GAME_DRAW;
	return someoneWon;
}


//For now, there is no real AI, it just picks a random empty square
//Later, when the code is better organized, implement a working AI with minimax algorithm
void LBoard::AImove()
{
	int x;
	do
	{
		x = Random(9);
	} while( mSquares[x].getState() != SQUARE_EMPTY);
	mSquares[x].placeCircle();
	
	
	mMoves++;
	
	if( !someoneWon() && mMoves < 9)
			mGameState = GAME_PLAYER_TURN;
}
