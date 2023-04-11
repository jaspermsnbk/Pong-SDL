#include "Score.h"
#include "Vec2.h"
#include <iostream>
Score::Score() {
	player1Score = 0;
	player2Score = 0;
}

void Score::drawScore(SDL_Renderer* r, Vec2 Offset, int scale, int won) {
	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
	_drawPlayerScore(player1Score, r, Offset, scale, won == 1? 1 : 0);
	_drawPlayerScore(player2Score, r, { Offset.x + 42, Offset.y }, scale, won == 2 ? 1 : 0);
	/*SDL_Rect dash{ (Offset.x + 25), (Offset.y + 18), 3 * scale, 2 * scale};
	SDL_RenderFillRect(r, &dash);*/


}

void Score::_drawPlayerScore(int score, SDL_Renderer* r, Vec2 Offset, int scale = 1, int won = 0) {
	int err = 0;
	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
	switch (score) {
	case 0:
		for (SDL_Rect& rect : num_0) {
			_applyOffsetScale(rect, Offset, scale);
			err = SDL_RenderFillRect(r, &rect);
			_removeOffsetScale(rect, Offset, scale);
		}
		break;
	case 1:
		for (SDL_Rect& rect : num_1) {
			_applyOffsetScale(rect, Offset, scale);
			err = SDL_RenderFillRect(r, &rect);
			_removeOffsetScale(rect, Offset, scale);
		}
		break;
	case 2:
		for (SDL_Rect& rect : num_2) {
			_applyOffsetScale(rect, Offset, scale);
			err = SDL_RenderFillRect(r, &rect);
			_removeOffsetScale(rect, Offset, scale);
		}
		break;
	case 3:
		for (SDL_Rect& rect : num_3) {
			_applyOffsetScale(rect, Offset, scale);
			err = SDL_RenderFillRect(r, &rect);
			_removeOffsetScale(rect, Offset, scale);
		}
		break;
	default:
		std::cout << "default" << std::endl;
		break;
	}
	if (won) {
		SDL_Rect temp{0,11,5,2};
		_applyOffsetScale(temp, Offset, scale);
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		err = SDL_RenderFillRect(r, &temp);
		_removeOffsetScale(temp, Offset, scale);
	}



	if (err) {
		throw SDL_GetError();
	}
}

void Score::testNumbers(SDL_Renderer* r, Vec2 Offset, int scale) {
	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
	for (SDL_Rect &rect : num_0) {
		_applyOffsetScale(rect, Offset, scale);
		SDL_RenderFillRect(r, &rect);
		_removeOffsetScale(rect, Offset, scale);
	}
	Offset.x += scale * 3;
	for (SDL_Rect& rect : num_1) {
		_applyOffsetScale(rect, Offset, scale);
		SDL_RenderFillRect(r, &rect);
		_removeOffsetScale(rect, Offset, scale);
	}
	Offset.x += scale * 3;
	for (SDL_Rect& rect : num_2) {
		_applyOffsetScale(rect, Offset, scale);
		SDL_RenderFillRect(r, &rect);
		_removeOffsetScale(rect, Offset, scale);
	}
	Offset.x += scale * 3;
	for (SDL_Rect& rect : num_3) {
		_applyOffsetScale(rect, Offset, scale);
		SDL_RenderFillRect(r, &rect);
		_removeOffsetScale(rect, Offset, scale);
	}
	
}
void Score::_applyOffsetScale(SDL_Rect& r, Vec2 offset, int scale) {
	
	r.x *= scale;
	r.y *= scale;
	r.w *= scale;
	r.h *= scale;
	r.x += offset.x;
	r.y += offset.y;
}
void Score::_removeOffsetScale(SDL_Rect& r, Vec2 offset, int scale) {
	r.x -= offset.x;
	r.y -= offset.y;
	r.x /= scale;
	r.y /= scale;
	r.w /= scale;
	r.h /= scale;
	
}
