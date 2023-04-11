#pragma once
#include "SDL.h"
#include "Vec2.h"
#include <vector>
class Score
{
	void _applyOffsetScale(SDL_Rect& r, Vec2 offset, int scale);
	void _removeOffsetScale(SDL_Rect& r, Vec2 offset, int scale);
	void _drawPlayerScore(int score, SDL_Renderer* r, Vec2 Offset, int scale, int won);

	void _drawNum(std::vector<SDL_Rect>& num, const Vec2& Offset, int scale, int& err, SDL_Renderer* r);

public:
	int player1Score;
	int player2Score;
	std::vector<SDL_Rect> num_0 = { {0,0,5,1}, {0,0,1,10}, {0,9,5,1}, {4,0,1,10} };
	std::vector<SDL_Rect> num_1 = { {2,0,1,10} };
	std::vector<SDL_Rect> num_2 = { {0,0,5,1}, {0,4,5,1}, {0,9,5,1}, {4,0,1,5}, {0,5,1,5}};
	std::vector<SDL_Rect> num_3 = { {0,0,5,1}, {0,4,5,1}, {0,9,5,1}, {4,0,1,10} };
	std::vector<SDL_Rect> nums[4] = { num_0 ,num_1 ,num_2 ,num_3 };
	Score();
	void drawScore(SDL_Renderer* r, Vec2 Offset, int scale, int won);
	void testNumbers(SDL_Renderer* r, Vec2 Offset, int scale);
};

