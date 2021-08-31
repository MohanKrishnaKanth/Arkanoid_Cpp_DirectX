#include "Brick.h"

Brick::Brick(const RectF& rect_in, Color c_in)
	:brickRect(rect_in),
	c(c_in)
{
}

void Brick::Draw(Graphics& gfx) const
{
	gfx.DrawRectByRectF(brickRect,c);
}