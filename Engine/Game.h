#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "RectF.h"
#include "Ball.h"
#include "Brick.h"
#include "Sound.h"
#include "Paddle.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float dt);
	/********************************/
	/*  User Functions              */

	void DrawBorders();

	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	static constexpr int bricksAcross = 18;
	static constexpr int bricksDown = 4;
	static constexpr int brickWidth = 40;
	static constexpr int brickHeight = 24;
	static constexpr int totalBricks = bricksAcross * bricksDown;
	static constexpr int borderWidth = 4;

	const Vec2 topLeft{ 40.0f,40.0f };
	const float Right = topLeft.x + float(bricksAcross * brickWidth);

	bool Gameover = false;
	int lives = 5;
	bool resetBallPosToPad;
	bool isStarted = false;
	FrameTimer ft;
	Ball ball;
	Paddle paddle;
	Brick bricks[totalBricks];
	RectF walls;
	Sound sfxPad = Sound(L"Sounds\\arkpad.wav");
	Sound sfxBrick = Sound(L"Sounds\\arkbrick.wav");

	/********************************/






};