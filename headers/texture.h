
#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class LTexture{
	SDL_Texture *mTexture;
	int mWidth;
	int mHeight;
	public:
		LTexture();
		~LTexture();
		
		void free();
		//I added an additional parameter to indicate if the texture uses a chroma key
		bool loadFromFile( std::string, bool = false);
		
		bool loadFromRenderedText( std::string, SDL_Color);
		
		//function to modulate texture color
		void setColor(Uint8, Uint8, Uint8);
		
		void render(int, int, SDL_Rect* = NULL, double = 0.0, SDL_Point* = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		
		int getWidth();
		int getHeight();
};

#endif
