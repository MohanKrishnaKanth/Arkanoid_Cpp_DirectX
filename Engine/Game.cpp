#include "MainWindow.h"
#include "Game.h"
#include "SpriteCode.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	walls(topLeft, Vec2(Right, (gfx.ScreenHeight - (borderWidth + topLeft.y)))),
	paddle(Vec2(Graphics::GetRect().GetCenter().x, 450.0f),70.0f,30.0f),
	rng(std::random_device()()),
	xDist(-2.0f,2.0f)
{
	Color colors[4] = { Colors::LightGray, Colors::Green ,Colors::Red , Colors::Blue };

	for (int y = 0 ,i = 0; y < bricksDown; ++y)
	{
		for (int x = 0; x < bricksAcross; ++x , ++i)
		{
			bricks[i] = Brick(RectF(topLeft + Vec2( float(x * brickWidth),  float(y * brickHeight)), brickWidth, brickHeight), colors[y]);
		}
	}
	gamestate = GameState::Title;
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
	if (gamestate == GameState::IsStarted)
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

		const int collided = ball.isCollidedToWalls(walls);
		if (collided == 1||collided == 2)
		{

			if (collided == 2)
			{
				if (lives > 0)
				{
					gamestate = GameState::Reset;
				}
				else
				{
					gamestate = GameState::Gameover;
				}
				sfxPad.Play();
			}

			else if(collided == 1)
			{
				if (!paddle.isBallCollided(ball)) // checking the ball between wall and paddle for continuous collision
				{
					paddle.ResetCooldown();
				}
				sfxPad.Play();
			}
		}
		

	}

	if (gamestate == GameState::Reset)
	{
		ResetGame();
	}
	if (gamestate==GameState::IsReady)
	{
		if((curWaitTime += dt) > waitTime)
		{
			gamestate = GameState::IsStarted;
			--lives;
			curWaitTime = 0.0f;
		}
	}
	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		switch (gamestate)
		{

		case GameState::Gameover:
			for (Brick& b : bricks)
			{
				b.ResetBrick();
			}

			lives = 5;
			gamestate = GameState::Reset;
			break;

		case GameState::Title:
			ResetGame();
			break;


		default:
			break;
		}



	}

	
}



void Game::ComposeFrame()
{
	DrawBorders();

	if (gamestate==GameState::IsStarted || gamestate == GameState::IsReady)
	{
		paddle.Draw(gfx);
		ball.Draw(gfx);
		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}
		if (gamestate == GameState::IsReady)
		{
			SpriteCode::DrawReady({ 400.0f,200.0f }, gfx);
		}

		DrawLifes();
	}

	else if(gamestate == GameState::Gameover)
	{
		SpriteCode::DrawGameover({ 390.0f,250.0f },gfx);
	}

	else if (gamestate == GameState::Title)
	{
		SpriteCode::DrawTitle({ 300.0f,210.0f }, gfx);
	}

	
}

void Game::DrawBorders()
{
	gfx.DrawRectWithPoints(int(topLeft.x), int(topLeft.y), int(Right), int(topLeft.y - borderWidth), Colors::LightGray); //top
	gfx.DrawRectWithPoints(int(topLeft.x - borderWidth), int(topLeft.y - borderWidth), int(topLeft.x), int(gfx.ScreenHeight - (borderWidth + topLeft.y)), Colors::LightGray); // left
	gfx.DrawRectWithPoints(int(Right), int(topLeft.y - borderWidth),int( Right + borderWidth), int(gfx.ScreenHeight - (borderWidth + topLeft.y)), Colors::LightGray);//right
	gfx.DrawRectWithPoints(int(topLeft.x - borderWidth), int(gfx.ScreenHeight - (borderWidth + topLeft.y)), int(Right + borderWidth),int( gfx.ScreenHeight - (1 + topLeft.y)), Colors::LightGray);//bottom
}

void Game::ResetGame()
{
	const Vec2 centerOfScreen = Graphics::GetRect().GetCenter();
	ball = Ball(centerOfScreen, Vec2(xDist(rng), -1.0f));
	paddle.ResetPosition(Vec2(centerOfScreen.x - 35.0f, 450.0f));
	gamestate = GameState::IsReady;
	curWaitTime = 0.0f;
	soundReady.Play();
}

void Game::DrawLifes()
{
	for (int i = 0, a = 0; i < lives; ++i)
	{
		if (i < 3)
		{
			SpriteCode::DrawLife(Vec2(50.0f + (i * 45.0f), 100.0f), gfx);
		}
		else
		{
			SpriteCode::DrawLife(Vec2(70.0f + (a * 50.0f), 100.0f + 40.0f), gfx);
			++a;
		}
	}
}
