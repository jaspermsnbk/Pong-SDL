#include "Score.h"
#include "Vec2.h"
#include <iostream>
#include <vector>
Score::Score() {
	player1Score = 0;
	player2Score = 0;
}

void Score::drawScore(SDL_Renderer* r, Vec2 Offset, int scale, int won) 
{
	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
	_drawPlayerScore(player1Score, r, Offset, scale, won == 1 ? 1 : 0);
	_drawPlayerScore(player2Score, r, { Offset.x + 42, Offset.y }, scale, won == 2 ? 1 : 0);
}

void Score::_drawPlayerScore(int score, SDL_Renderer* r, Vec2 Offset, int scale = 1, int won = 0) 
{
	int err = 0;
	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		
	if (score >= 0 && score < 4) {
		_drawNum(*(nums)[score], Offset, scale, err, r);
	}
	if (won) 
	{
		SDL_Rect temp{0,11,5,2};
		_applyOffsetScale(temp, Offset, scale);
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		err = SDL_RenderFillRect(r, &temp);
		_removeOffsetScale(temp, Offset, scale);
	}

	if (err) 
	{
		throw SDL_GetError();
	}
}

void Score::_drawNum(std::vector<SDL_Rect> & num,  const Vec2& Offset, int scale, int& err, SDL_Renderer* r)
{
	for (SDL_Rect& rect : num) {
		_applyOffsetScale(rect, Offset, scale);
		err = SDL_RenderFillRect(r, &rect);
		_removeOffsetScale(rect, Offset, scale);
	}
}

void Score::testNumbers(SDL_Renderer* r, Vec2 Offset, int scale) 
{
	int err;
	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);

	for (size_t i = 0; i < 4; i++)
	{
		_drawNum(*(nums)[i], Offset, scale, err, r);
		Offset.x += scale * 3;
	}
	
}
void Score::_applyOffsetScale(SDL_Rect& r, Vec2 offset, int scale)
{
	r.x *= scale;
	r.y *= scale;
	r.w *= scale;
	r.h *= scale;
	r.x += offset.x;
	r.y += offset.y;
}
void Score::_removeOffsetScale(SDL_Rect& r, Vec2 offset, int scale) 
{
	r.x -= offset.x;
	r.y -= offset.y;
	r.x /= scale;
	r.y /= scale;
	r.w /= scale;
	r.h /= scale;
}
Score::~Score() {
	free(num_0);
	free(num_1);
	free(num_2);
	free(num_3);
}