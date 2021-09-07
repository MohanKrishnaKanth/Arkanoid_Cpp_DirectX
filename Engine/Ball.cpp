#include "Ball.h"

Ball::Ball(const Vec2 pos, Vec2 v)
	:position(pos)
	
{
	SetDirection(v);
}

void Ball::Draw(Graphics & gfx) const
{
	SpriteCode::DrawBall(position, gfx);
}

void Ball::Update(float dt)
{
	position += vel * dt;
}

int Ball::isCollidedToWalls(const RectF & walls)
{
	RectF ballBox = GetBoundariesofBall();
	int isCollided = 0;
	if (ballBox.left < walls.left)
	{
		//clamping the excess left of ball entered into left wall which is negative ballbox.left value
		position.x += walls.left - ballBox.left;
		ReboundX();
		isCollided = 1;
	}
	else if (ballBox.right > walls.right)
	{
		//clamping the excess right of ball entered into right wall which is ballbox.right - screenwidth
		position.x -= ballBox.right - walls.right;
		ReboundX();
		isCollided = 1;
	}

	if (ballBox.top < walls.top)
	{
		//clamping the excess top of ball entered into top wall which is negative ballbox.top value
		position.y += walls.top - ballBox.top;
		ReboundY();
		isCollided = 1;
	}
	else if (ballBox.bottom > walls.bottom)
	{
		//clamping the excess bottom of ball entered into bottom wall which is ballbox.bottom - screenheight
		position.y -= ballBox.bottom - walls.bottom;
		//ReboundY();
		isCollided = 2;
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

Vec2 Ball::GetPosition() const
{
	return position;
}

Vec2 Ball::GetVelocity() const
{
	return vel;
}

void Ball::SetDirection(const Vec2& dir)
{
	vel = dir.GetNormalized() * speed;
}


