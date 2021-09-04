#include "MainWindow.h"
#include "Game.h"
#include "SpriteCode.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ball(Vec2(350.0f, 400.0f), Vec2(0.0f, 0.0f)),
	walls(topLeft, Vec2(Right, gfx.ScreenHeight - borderWidth)),
	paddle(Vec2(350.0f, 450.0f),70.0f,30.0f)
{
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
	float elapsedTime = ft.FrameDiff();
	while (elapsedTime > 0.0f) 
	{
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}

	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	if (isStarted)
	{
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

			if (ball.GetPosition().y > paddle.GetPosition().y)
			{
				--lives;
				resetBallPosToPad = true;
				Gameover = (lives == 0);
			}

			else
			{
				paddle.ResetCooldown();
				sfxPad.Play();
			}
		}
		

	}
	if (resetBallPosToPad)
	{
		ball.ResetPos(Vec2(350.0f, 400.0f));
		resetBallPosToPad = false;
		isStarted = false;
	}
	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		if (!isStarted)
		{
			isStarted = true;
			ball.SetVelocity(Vec2(500.0f, -500.0f));
		}
		if (Gameover)
		{
			Gameover = false;
			isStarted = false;
			lives = 5;
			for (Brick& b : bricks)
			{
				b.ResetBrick();
			}
		}
	}

	
}



void Game::ComposeFrame()
{
	DrawBorders();

	if (!Gameover)
	{
		paddle.Draw(gfx);
		ball.Draw(gfx);
		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}
	}

	else
	{
		SpriteCode::DrawGameover({ 380.0f,250.0f },gfx);
	}



	
}

void Game::DrawBorders()
{
	gfx.DrawRectWithPoints(topLeft.x, topLeft.y, Right, topLeft.y - borderWidth, Colors::LightGray); //top
	gfx.DrawRectWithPoints(topLeft.x - borderWidth, topLeft.y - borderWidth, topLeft.x, gfx.ScreenHeight - borderWidth, Colors::LightGray); // left
	gfx.DrawRectWithPoints(Right, topLeft.y - borderWidth, Right + borderWidth, gfx.ScreenHeight - borderWidth, Colors::LightGray);//right
	gfx.DrawRectWithPoints(topLeft.x - borderWidth, gfx.ScreenHeight - borderWidth, Right + borderWidth, gfx.ScreenHeight - 1, Colors::LightGray);//bottom
}
