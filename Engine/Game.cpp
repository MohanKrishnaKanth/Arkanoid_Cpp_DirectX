#include "MainWindow.h"
#include "Game.h"
#include "SpriteCode.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ball(Vec2(300.0f, 300.0f), Vec2(500.0f, 500.0f)),
	walls(0.0f, 0.0f, Graphics::ScreenWidth, Graphics::ScreenHeight)
{

}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.FrameDiff();
	ball.Update(dt);
	if (bricks.isBallCollided(ball))
	{
		sfxBrick.Play();
	}
	if (ball.isCollidedToWalls(walls))
	{
		sfxPad.Play();
	}

}

void Game::ComposeFrame()
{

	ball.Draw(gfx);
	bricks.Draw(gfx);
}
