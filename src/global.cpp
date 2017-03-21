#include <SDL2/SDL.h>
#include "../headers/texture.h"
#include "../headers/board.h"


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

TTF_Font *gFont = NULL;

LTexture gSpriteSheetTexture;
//Text textures
LTexture gRestartTextTexture;
LTexture gDrawTextTexture;
LTexture gPlayerWinsTextTexture;
LTexture gAiWinsTextTexture;


//Quads that define the position and dimensions of each 'texture' in the spritesheet
SDL_Rect gSpriteQuads[3];

LBoard gBoard;
