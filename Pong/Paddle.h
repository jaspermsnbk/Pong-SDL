#pragma once
#include "Vec2.h"
#include "SDL.h"
#include <utility>
/*
Paddle class of the game pong
*/
class Paddle
{
private:
	//member variables
	int _spd;
	int _upperLimit;
	int _lowerLimit;
	int _paddleDir;

	Vec2 _pos;
	SDL_Rect _body;
	SDL_Scancode _keys[2];


	bool _axis_check(int a_min, int a_max, int b_min, int b_max);

public:
	Paddle();
	/*
	takes four ints. 
	x and y are the top left corner of the paddles starting position.
	w and h are the width and height of the paddle.
	up and down keys are not initially set
	upper and lower limits are also not set
	*/
	Paddle(int x, int y, int w, int h);

	/*
	constructor with an upper and lower limit defined
	*/
	Paddle(int x, int y, int w, int h, int upperLimit, int lowerLimit);
	/*
	constructor with an upper and lower limit defined as well as a up and down key
	*/
	Paddle(int x, int y, int w, int h, int upperLimit, int lowerLimit, SDL_Scancode up, SDL_Scancode down);
	~Paddle();

	/*
	takes an upper limit int and a lower limit int to use 
	as the limits of the paddles up and down movement.
	returns void
	*/
	void setLimits(int upper, int lower);

	/*
	takes two SDL_Scancodes for the up and down keys to be used for the paddle
	*/
	void setUpDownKeys(SDL_Scancode up, SDL_Scancode down);

	/*
	Takes a state array from the SDL_GetKeyboardState func and processes any input
	*/
	void processInput(const Uint8* state);

	/*
	call this in the update func of the game. 
	*/
	void update(float * deltaTime);
	
	/*
	call this in the draw func of the game
	*/
	void draw(SDL_Renderer* r);

	/*
	decides if this paddle has collided with a rect
	*/
	bool collided(const SDL_Rect & other);
};

