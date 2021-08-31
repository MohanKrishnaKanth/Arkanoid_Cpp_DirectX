#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "RectF.h"
#include "Ball.h"
#include "Brick.h"
#include "Sound.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	FrameTimer ft;
	Ball ball;
	Brick bricks;
	RectF walls;
	Sound sfxPad = Sound(L"Sounds\\arkpad.wav");
	Sound sfxBrick = Sound(L"Sounds\\arkbrick.wav");

	/********************************/






};