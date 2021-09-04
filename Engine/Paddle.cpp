#include "Paddle.h"

Paddle::Paddle(const Vec2 & pos, float half_width, float half_height)
	:position(pos),
	halfWidth(half_width),
	halfHeight(half_height)
{
}

RectF Paddle::GetBoundariesOfPaddle()
{
	return RectF(position,halfWidth,halfHeight);
}

void Paddle::Draw(Graphics & gfx) 
{
	gfx.DrawRectByRectF(GetBoundariesOfPaddle(), Colors::Red);
}

bool Paddle::isBallCollided(Ball & ball) 
{
	if (!isCooldown)
	{
		const RectF paddleBox = GetBoundariesOfPaddle();
		const Vec2 ballpos = ball.GetPosition();

		if (paddleBox.IsOverlapping(ball.GetBoundariesofBall()))
		{
			if (std::signbit(ball.GetVelocity().x) == std::signbit((ballpos - position).x))
			{
				ball.ReboundY();
			}
			else if (ballpos.x >= paddleBox.left || ballpos.x <= paddleBox.right)
			{
				ball.ReboundY();
			}
			else
			{
				ball.ReboundX();
			}

			isCooldown = true;
			return true;
		}
	}
	return false;

}

void Paddle::isWallCollided(const RectF & walls)
{
	RectF paddleBox = GetBoundariesOfPaddle();
	if (paddleBox.left < walls.left)
	{
		position.x += walls.left - paddleBox.left;
	}

	if (paddleBox.right > walls.right)
	{
		position.x -= paddleBox.right - walls.right;
	}
}

void Paddle::Update(Keyboard& kb,float dt)
{
	if (kb.KeyIsPressed(VK_LEFT))
	{
		position -= Vec2(speed * dt, 0.0f);
	}
	if (kb.KeyIsPressed(VK_RIGHT))
	{
		position += Vec2(speed * dt, 0.0f);
	}

}

void Paddle::ResetCooldown()
{
	isCooldown = false;
}
