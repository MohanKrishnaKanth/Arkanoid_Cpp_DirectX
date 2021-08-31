#include "RectF.h"

RectF::RectF(float l, float t, float r, float b)
	:left(l),
	top(t),
	right(r),
	bottom(b)
{
}

RectF::RectF(const Vec2 & topleft, const Vec2 & bottomright)
	:RectF(topleft.x, topleft.y, bottomright.x, bottomright.y)
{
}

RectF::RectF(const Vec2& topleft, float width, float height)
	: RectF(topleft, Vec2(topleft.x + width, topleft.y + height))
{
}

bool RectF::IsOverlapping(const RectF & val) const
{
	return val.left < right && val.right > left && val.bottom > top && val.top < bottom;
}

RectF RectF::FromCenter(const Vec2& center, float halfwidth, float halfheight)
{
	const Vec2 half(halfwidth, halfheight);
	return RectF(center - half, center + half);
}
