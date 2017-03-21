

#ifndef GLOBALS_H
#define GLOBALS_h

#include <SDL2/SDL.h>
#include "../headers/texture.h"
#include "../headers/board.h"


extern SDL_Window *gWindow ;
extern SDL_Renderer *gRenderer;

extern TTF_Font *gFont;

extern LTexture gSpriteSheetTexture;
//Text textures
extern LTexture gRestartTextTexture;
extern LTexture gDrawTextTexture;
extern LTexture gPlayerWinsTextTexture;
extern LTexture gAiWinsTextTexture;


//Quads that define the position and dimensions of each 'texture' in the spritesheet
extern SDL_Rect gSpriteQuads[3];

extern LBoard gBoard;

#endif
