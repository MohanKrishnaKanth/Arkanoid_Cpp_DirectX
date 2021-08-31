#pragma once
#include "RectF.h"
#include "Graphics.h"
class Brick
{
private:
	RectF brickRect;
	Color c;
	bool isDestroyed;

public:
	Brick(const RectF& rect_in, Color c_in);
	void Draw(Graphics& gfx)const;
};