#include "Game.h"
//#include "SDL_ttf.h" I didnt know if we could use the ttf library so I made my own numbers.
#include <string.h>
#include "Score.h"
#include <random>
#include <time.h>
#include <iostream>
Game::Game()
{
	_pWindow = nullptr;
	_pRenderer = nullptr;
	_bIsRunning = true;
	_nTickCount = 0;
	_ball = { WINDOW_WIDTH / 2 ,WINDOW_HEIGHT / 2, 15, 15};
	srand((unsigned)time(NULL));
	_restartBall();
}

Game::~Game()
{
}


// Initialize the game.
bool Game::Initialize()
{
	// Initialize SDL.
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Create the SDL window.
	_pWindow = SDL_CreateWindow("Pong", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (_pWindow == nullptr)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// Create the SDL renderer for all drawing.
	_pRenderer = SDL_CreateRenderer(_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (_pRenderer == nullptr)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	// pong specific init

	_player1 = Paddle(
		10,					//x
		WINDOW_HEIGHT / 2,			//y
		15, 100,			//width
		15,					//height
		WINDOW_HEIGHT - 15			//bottom limit
	);
	_player2 = Paddle(
		1004,				//x
		WINDOW_HEIGHT / 2,			//y
		15,					//width
		100,				//height
		15,					//top limit
		WINDOW_HEIGHT - 15,			//bottom limit
		SDL_SCANCODE_I,     //up key
		SDL_SCANCODE_K		//down key
	);    


	


	return true;
}

// Run the overall game loop.
void Game::RunLoop()
{
	// Keep running the game until it is over.
	while (_bIsRunning)
	{
		_processInput();
		if (won != 0)
			continue;
		_updateGame();
		_generateOutput();
	}
}

// Shutdown the game.
void Game::Shutdown()
{
	// Cleanup SDL.
	SDL_DestroyRenderer(_pRenderer);
	SDL_DestroyWindow(_pWindow);
	SDL_Quit();
}

void Game::_processInput()
{
	// Poll for events in the window.
	// Needed to keep the window open.
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_bIsRunning = false;
			break;
		}
		
	}

	// Get the entire state of the keyboard in an unsigned integer array.
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	//
	_player1.processInput(state);
	_player2.processInput(state);

	// Check state of particular keys.
	if (state[SDL_SCANCODE_ESCAPE])
	{
		_bIsRunning = false;
	}

	if (state[SDL_SCANCODE_RETURN] && won != 0)
	{
		won = 0;
		_s.player1Score = 0;
		_s.player2Score = 0;
		_restartBall();
	}
}

void Game::_updateGame()
{
	
	// Wait until 16ms have elapsed.
	// while (!SDL_TICKS_PASSED(SDL_GetTicks(), _nTickCount + 16))
	// 	;

	// Delta time is the difference in ticks from the last frame
	// to this frame, converted to seconds.
	float deltaTime = (SDL_GetTicks() - _nTickCount) / 1000.f;
	_nTickCount = SDL_GetTicks();

	// move paddle
	_player1.update(&deltaTime);
	_player2.update(&deltaTime); 
	// move the ball
	_ballPos.x += _ballVel.x * deltaTime;
	_ballPos.y += _ballVel.y * deltaTime;
	_ball.x = _ballPos.x;
	_ball.y = _ballPos.y;
	// check for collision

	// bottom wall
	if (_ballPos.y >= WINDOW_HEIGHT - 2 * 15 && _ballVel.y > 0)
	{
		_ballVel.y *= -1;
	}
	// top wall
	if (_ballPos.y <= 2 * 15 && _ballVel.y < 0)
	{
		_ballVel.y *= -1;
	}
	
	// player 1
	if (_ballVel.x < 0 && _player1.collided(_ball)) {
		_ballVel.x *= -1 * (1 + DIFF);
		_ballVel.y *= 1 + DIFF;
	}

	// player 2
	if (_ballVel.x > 0 && _player2.collided(_ball)) {
		_ballVel.x *= -1 * (1 + DIFF);
		_ballVel.y *= 1 + DIFF;
	}

	//out of bounds
	if (_ballPos.x < 0 - _ball.w ) {
		if (_s.player2Score == 3) {
			won = 2;
			
		}
		else {
			_s.player2Score++;
			_restartBall();
		}
	}
	if (_ballPos.x > WINDOW_WIDTH) {
		if (_s.player1Score == 3) {
			won = 1;
			
		}
		else {
			_s.player1Score++;
			_restartBall();
		}
	}

}

void Game::_generateOutput()
{
	// Set background to blue.
	SDL_SetRenderDrawColor(_pRenderer, 0, 0, 255, 255);

	// Clear the back buffer to be ready to draw.
	SDL_RenderClear(_pRenderer);

	// set draw color to white
	SDL_SetRenderDrawColor(_pRenderer, 255, 255, 255, 255);

	SDL_Rect wall{0, 0, WINDOW_WIDTH, 15};
	SDL_RenderFillRect(_pRenderer, &wall);
	wall.y = WINDOW_HEIGHT - 15;
	SDL_RenderFillRect(_pRenderer, &wall);

	//call draw methods of paddles
	_player1.draw(_pRenderer);
	_player2.draw(_pRenderer);

	// draw ball
	SDL_Rect ball{_ballPos.x, _ballPos.y, 15, 15};
	SDL_RenderFillRect(_pRenderer, &ball);

	//draw dashed line down middle of screen
	SDL_SetRenderDrawColor(_pRenderer, 255, 255, 255, 255);
	drawDashedLine(_pRenderer, WINDOW_WIDTH / 2, 3, WINDOW_HEIGHT, 20, 10);
	//draw score
	_s.drawScore(_pRenderer, { WINDOW_WIDTH /2 - 30, WINDOW_HEIGHT/2 - 20}, 4, won);
	
	// Swap the front and back buffers.
	SDL_RenderPresent(_pRenderer);
}

void Game::drawDashedLine(SDL_Renderer* r, int offsetX, int w, int h, int density, int gap) {
	for (int i = 0; i < density; i++)
	{
		SDL_Rect temp{ 
			offsetX - w/2,
			gap + ((i * h) / density), 
			w, 
			gap + (i * h)/ density - ((((i + 1) * h) / density) - gap)};
		SDL_RenderFillRect(r, &temp);
	}
}

void Game::_restartBall() 
{
	_ballPos = { WINDOW_WIDTH / 2 - 7, WINDOW_HEIGHT / 2 - 7 };

	int r = rand() % 10;
	Vec2 r_vel = { 0,0 };
	if (r > 5) 
		r_vel.x = 1;
	else 
		r_vel.x = -1;
	
	r = rand() % 10;
	if (r > 5)
		r_vel.y = 1;
	else
		r_vel.y = -1;
	
	_ballVel = { 200 , 200 };
	_ballVel = _ballVel * r_vel;
}