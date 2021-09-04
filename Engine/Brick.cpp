#include "Brick.h"

Brick::Brick(const RectF& rect_in, Color c_in)
	:brickRect(rect_in),
	c(c_in)
{
}

void Brick::Draw(Graphics& gfx) const
{
	if(!isDestroyed)
	gfx.DrawRectByRectF(GetPaddedRect(padding),c);
}

bool Brick::CheckBallCollision(Ball & ball)
{
	return (!isDestroyed && brickRect.IsOverlapping(ball.GetBoundariesofBall()));
}


void Brick::ExecuteCollision(Ball& ball)
{
	const Vec2 ballpos = ball.GetPosition();
	if (std::signbit(ball.GetVelocity().x) == std::signbit((ballpos - brickRect.GetCenter()).x)) //  checking hitting brick at corner from inside way
	{
		ball.ReboundY();
	}
	else if(ballpos.x >= brickRect.left || ballpos.x <= brickRect.right)
	{
		ball.ReboundY();
	}
	else
	{
		ball.ReboundX();
	}
	isDestroyed = true;
}

RectF Brick::GetPaddedRect(float offset) const
{
	return RectF(brickRect.left + offset, brickRect.top + offset, brickRect.right - offset, brickRect.bottom - offset);
}

RectF Brick::BrickRect() const
{
	return brickRect;
}


