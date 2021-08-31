#include "Brick.h"

Brick::Brick(const RectF& rect_in, Color c_in)
	:brickRect(rect_in),
	c(c_in)
{
}

void Brick::Draw(Graphics& gfx) const
{
	if(!isDestroyed)
	gfx.DrawRectByRectF(brickRect,c);
}

bool Brick::isBallCollided(Ball & ball)
{
	if (!isDestroyed && brickRect.IsOverlapping(ball.GetBoundariesofBall()))
	{
		ball.ReboundY();
		isDestroyed = true;
		return true;
	}
	return false;
}


