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
	static constexpr float padding = 1.0f;

public:
	Brick() = default;
	Brick(const RectF& rect_in, Color c_in);
	void Draw(Graphics& gfx)const;
	bool CheckBallCollision(Ball& ball);
	void ExecuteCollision(Ball& ball);
	RectF GetPaddedRect(float offset) const;
	RectF BrickRect() const;
	void ResetBrick();

};