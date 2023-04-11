#include "Paddle.h"
#include <iostream>
Paddle::Paddle() {
	_paddleDir = 0;
	_spd = 300;
	_pos = { 0, 0 };
	_body = { 0, 0, 10, 100 };
	setUpDownKeys(SDL_SCANCODE_W, SDL_SCANCODE_S);
	setLimits(-1, -1);
}
Paddle::Paddle(int x, int y, int w, int h)
{
	_paddleDir = 0;
	_spd = 300;
	_pos = { x, y };
	_body = { x, y, w, h };
	setUpDownKeys(SDL_SCANCODE_W, SDL_SCANCODE_S);
	setLimits(0, 0);
}
Paddle::Paddle(int x, int y, int w, int h, int upperLimit, int lowerLimit)
{
	_paddleDir = 0;
	_spd = 300;
	_pos = { x, y };
	_body = { x, y, w, h };
	setLimits(upperLimit, lowerLimit);
	setUpDownKeys(SDL_SCANCODE_W, SDL_SCANCODE_S);
}
Paddle::Paddle(int x, int y, int w, int h, int upperLimit, int lowerLimit, SDL_Scancode up, SDL_Scancode down)
{

	_paddleDir = 0;
	_spd = 300;
	_pos = { x, y };
	_body = { x, y, w, h };
	setLimits(upperLimit, lowerLimit);
	setUpDownKeys(up, down);
}
Paddle::~Paddle()
{

}
void Paddle::setLimits(int upper, int lower) {
	_upperLimit = upper;
	_lowerLimit = lower;
}
void Paddle::setUpDownKeys(SDL_Scancode up, SDL_Scancode down)
{
	_keys[0] = up;
	_keys[1] = down;
}
void Paddle::processInput(const Uint8* state) {
	
	_paddleDir = 0;
	if (state[_keys[1]]) //down key
	{
		_paddleDir += 1;
	}
	if (state[_keys[0]]) //up key
	{
		_paddleDir += -1;
	}
}

void Paddle::update(float * deltaTime) {
	if (_paddleDir != 0 && (
		(_pos.y > _upperLimit && _paddleDir == -1) || 
		(_pos.y < (_lowerLimit - _body.h) && _paddleDir == 1)))
	{
		_pos.y += _spd * _paddleDir * (*deltaTime);
	}

	_body.x = _pos.x;
	_body.y = _pos.y;
}

void Paddle::draw(SDL_Renderer* r) {
	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
	SDL_RenderFillRect(r, &_body);
}
bool Paddle::collided(const SDL_Rect & other) {
	if (_axis_check(
			this->_body.x, 
			this->_body.x + this->_body.w , 
			other.x, 
			other.x + other.w) && 
		_axis_check(
			this->_body.y, 
			this->_body.y + this->_body.h, 
			other.y, 
			other.y + other.h))
		return true;
	else
		return false;
}

bool Paddle::_axis_check(int a_min, int a_max, int b_min, int b_max)
{
	if (a_max < b_min || b_max < a_min) return false;
	else return true;
}