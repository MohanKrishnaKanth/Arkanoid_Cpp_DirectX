#include "MainWindow.h"
#include "Game.h"
#include "SpriteCode.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ball(Vec2(300.0f, 300.0f), Vec2(500.0f, 500.0f)),
	walls(0.0f, 0.0f, Graphics::ScreenWidth, Graphics::ScreenHeight),
	paddle(Vec2(350.0f, 450.0f),70.0f,30.0f)
{
	const Vec2 topLeft{ 0.0f,0.0f };
	Color colors[4] = { Colors::LightGray, Colors::Green ,Colors::Red , Colors::Blue };

	for (int y = 0 ,i = 0; y < bricksDown; ++y)
	{
		for (int x = 0; x < bricksAcross; ++x , ++i)
		{
			bricks[i] = Brick(RectF(topLeft + Vec2( float(x * brickWidth),  float(y * brickHeight)), brickWidth, brickHeight), colors[y]);
		}
	}

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
	paddle.Update(wnd.kbd, dt);
	paddle.isWallCollided(walls);
	ball.Update(dt);

	if (paddle.isBallCollided(ball))
	{
		sfxPad.Play();
	}


	float oldCollisionDistSq = 0;
	float newCollisionDistSq = 0;
	bool isCollided = false;
	int brickIndex = 0;
	for (int i = 0; i < totalBricks; ++i)
	{
		if (bricks[i].CheckBallCollision(ball))
		{
			if (isCollided)
			{
				newCollisionDistSq = (ball.GetPosition() - bricks[i].BrickRect().GetCenter()).GetLengthSq();
				if (newCollisionDistSq < oldCollisionDistSq)
				{
					brickIndex = i;
				}
			}
			else
			{
				oldCollisionDistSq = (ball.GetPosition() - bricks[i].BrickRect().GetCenter()).GetLengthSq();
				brickIndex = i;
				isCollided = true;
			}
		}
	}

	if (isCollided)
	{
		bricks[brickIndex].ExecuteCollision(ball);
		sfxBrick.Play();
		paddle.ResetCooldown();
	}


	if (ball.isCollidedToWalls(walls))
	{
		paddle.ResetCooldown();
		sfxPad.Play();
	}

}

void Game::ComposeFrame()
{
	paddle.Draw(gfx);
	ball.Draw(gfx);
	for (const Brick& b : bricks)
	{
		b.Draw(gfx);
	}
}
