#pragma once
#include "SDL.h"
#include "Vec2.h"

class Score
{
	void _applyOffsetScale(SDL_Rect& r, Vec2 offset, int scale);
	void _removeOffsetScale(SDL_Rect& r, Vec2 offset, int scale);
	void _drawPlayerScore(int score, SDL_Renderer* r, Vec2 Offset, int scale, int won);

public:
	int player1Score;
	int player2Score;
	SDL_Rect num_0 [4] = { {0,0,5,1}, {0,0,1,10}, {0,9,5,1}, {4,0,1,10} };
	SDL_Rect num_1 [1] = { {2,0,1,10} };
	SDL_Rect num_2 [5] = { {0,0,5,1}, {0,4,5,1}, {0,9,5,1}, {4,0,1,5}, {0,5,1,5}};
	SDL_Rect num_3[4] = { {0,0,5,1}, {0,4,5,1}, {0,9,5,1}, {4,0,1,10} };
	
	Score();
	void drawScore(SDL_Renderer* r, Vec2 Offset, int scale, int won);
	void testNumbers(SDL_Renderer* r, Vec2 Offset, int scale);
	
};

