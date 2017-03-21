
#include "../headers/texture.h"
#include "../headers/globals.h"
#include <stdio.h>

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	free();
}


void LTexture::free()
{
	if(mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}


bool LTexture::loadFromFile( std::string path, bool HasChroma)
{
	free();
	SDL_Surface *loadedSurface = IMG_Load( path.c_str() );
	
	if(loadedSurface == NULL)
		printf("Unable to load from %s! SDL_image error: %s\n", path.c_str(), IMG_GetError() );
	else
	{
		//here we set the chroma key color, in this case: green
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xff, 0));
		
		mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		
		if(mTexture == NULL)
			printf("Unable to create texture from %s! SDL error: %s\n", path.c_str(), SDL_GetError() );
		else
		{
			mWidth = loadedSurface -> w;
			mHeight = loadedSurface -> h;
		}
		
		SDL_FreeSurface(loadedSurface);
	}
	
	return mTexture != NULL;
}


bool LTexture::loadFromRenderedText( std::string text, SDL_Color color)
{
	free();
	SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, text.c_str(), color);
	if(textSurface == NULL)
		printf("Unable to render text surface! SDL_ttf error: %s\n", TTF_GetError() );
	else
	{
		
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		
		if(mTexture == NULL)
			printf("Unable to create texture from rendered text! SDL error: %s\n", SDL_GetError() );
		else
		{
			mWidth = textSurface -> w;
			mHeight = textSurface -> h;
		}
		
		SDL_FreeSurface(textSurface);
	}
	
	return mTexture != NULL;
}


void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};
	if(clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}


void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}


int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
