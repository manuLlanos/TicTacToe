
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "../headers/globals.h"

bool init()
{
	bool success = true;
	
	if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if(! SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			printf("Warning: linear filter could not be set.\n");
		
		gWindow = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		
		if(gWindow == NULL)
		{
			printf("Window could not be created! SDL error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			
			if(gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL error: %s\n", SDL_GetError() );
				success = false;
			}
			
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xff,0xff,0xff,0xff);
				
				if(TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf error: %s\n", TTF_GetError() );
					success = false;
				}
			}
				
			
		}
	}
	
	return success;
}


bool loadMedia()
{
	bool success = true;
	
	gFont = TTF_OpenFont("resources/FreeSans.ttf", FONT_SIZE);
	
	if(! gSpriteSheetTexture.loadFromFile("resources/tateti.png", true))
	{
		printf("Unable to load sprite sheet!\n");
		success = false;
	}
	
	else if(gFont == NULL)
	{
		printf("Failed to open font! SDL_ttf error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		SDL_Color textColor = {0,0,0};
		if( ! gDrawTextTexture.loadFromRenderedText("It's a draw!", textColor))
		{
			printf("Failed to render text texture (draw)!\n");
			success = false;
		}
		else if( ! gPlayerWinsTextTexture.loadFromRenderedText("You won!", textColor))
		{
			printf("Failed to render text texture (player wins)!\n");
			success = false;
		}
		else if( ! gAiWinsTextTexture.loadFromRenderedText("The AI wins!", textColor))
		{
			printf("Failed to render text texture(AI wins)\n");
			success = false;
		}
		else if( ! gRestartTextTexture.loadFromRenderedText("SPACEBAR to restart", textColor))
		{
			printf("Failed to render text texture (restart)\n");
			success = false;
		}
		
		else
		{
			gSpriteQuads[0].x = 0;
			gSpriteQuads[0].y = 0;
			gSpriteQuads[0].w = 100;
			gSpriteQuads[0].h = 100;
			
			gSpriteQuads[1].x = 100;
			gSpriteQuads[1].y = 0;
			gSpriteQuads[1].w = 100;
			gSpriteQuads[1].h = 100;
			
			gSpriteQuads[2].x = 200;
			gSpriteQuads[2].y = 0;
			gSpriteQuads[2].w = 300;
			gSpriteQuads[2].h = 300;
		}
	}
		
	return success;
}


void close()
{
	gSpriteSheetTexture.free();
	gDrawTextTexture.free();
	gPlayerWinsTextTexture.free();
	gAiWinsTextTexture.free();
	gRestartTextTexture.free();
	
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	TTF_CloseFont(gFont);
	gWindow = NULL;
	gRenderer = NULL;
	gFont = NULL;
	
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

