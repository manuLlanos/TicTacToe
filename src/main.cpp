
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>

#include "../headers/Random.h"

#include "../headers/texture.h"
#include "../headers/board.h"

#include "../headers/globals.h"
#include "../headers/constants.h"
#include "../headers/functions.h"




int main(int argc, char **argv)
{
	bool quit = false;
	SDL_Event e;
	
	SEED;
	
	if( ! init())
		printf("Initialization error!\n");
	else if( ! loadMedia())
		printf("Media could not be loaded!\n");
	else
	{
		while(!quit)
		{
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT)
					quit = true;
				//send the event to the board to check if it was inside of a square,
				//and if the square was empty, then make a move. It has to be the player's turn.
				if(gBoard.getGameState() == GAME_PLAYER_TURN)
					gBoard.handleEvent(&e);
				
				else if( gBoard.getGameState() == GAME_WAIT)
					if(e.key.keysym.sym == SDLK_SPACE)
						gBoard.restart();
			}
			
			
			if(gBoard.getGameState() == GAME_AI_TURN)
				gBoard.AImove();
			
			else if(gBoard.getGameState() == GAME_DRAW ||gBoard.getGameState() == GAME_AI_WINS || gBoard.getGameState() == GAME_PLAYER_WINS)
				gBoard.gameOver();
			
			
			SDL_SetRenderDrawColor(gRenderer, 0xff,0xff,0xff,0xff);
			SDL_RenderClear(gRenderer);
					
			gBoard.render();
			
			SDL_RenderPresent(gRenderer);
		}
	}
	
	close();
	return 0;
}

