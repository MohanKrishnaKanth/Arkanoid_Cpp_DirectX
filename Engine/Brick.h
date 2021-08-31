#pragma once
#include "RectF.h"
#include "Graphics.h"
#include "Ball.h"

class Brick
{
private:
	RectF brickRect;
	Color c;
	bool isDestroyed = false;
	static constexpr float halfWidth = 20.0f;
	static constexpr float halfHeight = 10.0f;

public:
	Brick() = default;
	Brick(const RectF& rect_in, Color c_in);
	void Draw(Graphics& gfx)const;
	bool isBallCollided(Ball& ball);

};