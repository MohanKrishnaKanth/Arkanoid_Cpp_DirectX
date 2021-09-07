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
#include <random>


class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
	enum GameState { Title ,IsStarted, IsReady,Reset, Gameover, Won };
private:
	void ComposeFrame();
	void UpdateModel(float dt);
	/********************************/
	/*  User Functions              */

	void DrawBorders();
	void ResetGame();
	void DrawLifes();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	static constexpr int bricksAcross = 12;
	static constexpr int bricksDown = 4;
	static constexpr int brickWidth = 40;
	static constexpr int brickHeight = 24;
	static constexpr int totalBricks = bricksAcross * bricksDown;
	static constexpr int borderWidth = 4;
	static constexpr float waitTime = 4.3f;
	float curWaitTime = 0.0f;
	
	const Vec2 topLeft{ 160.0f,40.0f };
	const float Right = topLeft.x + float(bricksAcross * brickWidth);

	GameState gamestate;
	int lives = 5;

	FrameTimer ft;
	Ball ball;
	Paddle paddle;
	Brick bricks[totalBricks];
	RectF walls;
	Sound sfxPad = Sound(L"Sounds\\arkpad.wav");
	Sound sfxBrick = Sound(L"Sounds\\arkbrick.wav");
	Sound soundReady = Sound(L"Sounds\\ready.wav");

	std::default_random_engine rng;
	std::uniform_real_distribution<float> xDist;

	/********************************/






};
