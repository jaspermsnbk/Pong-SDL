#pragma once
#include "Vec2.h"
#include "SDL.h"
#include "Paddle.h"
#include <string.h>
#include "Score.h"
// Generic Game class.
class Game
{
public:
	Game();
	~Game();

	// Initialize the game.
	bool Initialize();

	// Run the game loop until the game is over.
	void RunLoop();

	// Shutdown the game.
	void Shutdown();

	const int WINDOW_HEIGHT = 768;
	const int WINDOW_WIDTH = 1024;

	//difficulty modifier, this can be changed to a float between 0 and 1.
	// 0 == easy
	// .03 == medium
	// .1 == hard
	// 1 == EXTREME
	const float DIFF = 1; 
	
private:
	void _processInput();

	void _updateGame();
	void _generateOutput();
	void drawDashedLine(SDL_Renderer* r, int offsetX, int w, int h, int density, int gap);
	void _restartBall();
	// SDL window and renderer.
	SDL_Window *_pWindow;
	SDL_Renderer *_pRenderer;

	// Is the game still running.
	bool _bIsRunning;
	// Number of ticks since the start of the game.
	Uint32 _nTickCount;


	// pong specific vars
	int won = 0;
	Vec2 _ballPos;
	Vec2 _ballVel;
	SDL_Rect _ball;
	Paddle _player1;
	Paddle _player2;
	Score _s;
};
