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

bool Ball::isCollidedToWalls(const RectF & walls)
{
	RectF ballBox = GetBoundariesofBall();
	bool isCollided = false;
	if (ballBox.left < walls.left)
	{
		//clamping the excess left of ball entered into left wall which is negative ballbox.left value
		position.x += walls.left - ballBox.left;
		ReboundX();
		isCollided = true;
	}
	else if (ballBox.right > walls.right)
	{
		//clamping the excess right of ball entered into right wall which is ballbox.right - screenwidth
		position.x -= ballBox.right - walls.right;
		ReboundX();
		isCollided = true;
	}

	if (ballBox.top < walls.top)
	{
		//clamping the excess top of ball entered into top wall which is negative ballbox.top value
		position.y += walls.top - ballBox.top;
		ReboundY();
		isCollided = true;
	}
	else if (ballBox.bottom > walls.bottom)
	{
		//clamping the excess bottom of ball entered into bottom wall which is ballbox.bottom - screenheight
		position.y -= ballBox.bottom - walls.bottom;
		ReboundY();
		isCollided = true;
	}

	return isCollided;
}

RectF Ball::GetBoundariesofBall() const
{
	return RectF::FromCenter(position, radius, radius);
}

void Ball::ReboundX()
{
	vel.x *= -1;
}

void Ball::ReboundY()
{
	vel.y *= -1;
}
