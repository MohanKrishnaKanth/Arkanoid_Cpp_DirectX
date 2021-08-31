#include "Ball.h"

Ball::Ball(Vec2 pos, Vec2 v)
	:position(pos),
	 vel(v)
{
}

void Ball::Draw(Graphics & gfx) const
{
	SpriteCode::DrawBall(position, gfx);
}

void Ball::Update(float dt)
{
	position += vel * dt;
}

void Ball::isCollidedToWalls(const RectF & walls)
{
	RectF ballBox = GetBoundariesofBall();

	if (ballBox.left < walls.left)
	{
		//clamping the excess left of ball entered into left wall which is negative ballbox.left value
		position.x += walls.left - ballBox.left;
		vel.x *= -1;
	}
	else if (ballBox.right > walls.right)
	{
		//clamping the excess right of ball entered into right wall which is ballbox.right - screenwidth
		position.x -= ballBox.right - walls.right;
		vel.x *= -1;
	}

	if (ballBox.top < walls.top)
	{
		//clamping the excess top of ball entered into top wall which is negative ballbox.top value
		position.y += walls.top - ballBox.top;
		vel.y *= -1;
	}
	else if (ballBox.bottom > walls.bottom)
	{
		//clamping the excess bottom of ball entered into bottom wall which is ballbox.bottom - screenheight
		position.y -= ballBox.bottom - walls.bottom;
		vel.y *= -1;
	}
}

RectF Ball::GetBoundariesofBall() const
{
	return RectF::FromCenter(position, radius, radius);
}
