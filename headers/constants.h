
#ifndef CONSTANTS_H
#define CONSTANTS_H

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int FONT_SIZE = 50;

//square dimensions
const int SQUARE_SIZE = 100;
const int TOTAL_SQUARES = 9;

const int BOARD_SIZE = 300;
const int BOARD_POS_X = (SCREEN_WIDTH - BOARD_SIZE)/2;
const int BOARD_POS_Y = (SCREEN_HEIGHT - BOARD_SIZE)/2;

//enumeration of possible square states
enum squareStates{
	SQUARE_EMPTY,
	SQUARE_CROSS,
	SQUARE_CIRCLE
};

//enumeration of game states
enum gameStates{
	GAME_PLAYER_TURN,
	GAME_AI_TURN,
	GAME_DRAW,
	GAME_PLAYER_WINS,
	GAME_AI_WINS,
	GAME_WAIT
};

#endif
