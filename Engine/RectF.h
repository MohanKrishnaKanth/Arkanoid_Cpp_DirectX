#pragma once
#include "Vec2.h"

class RectF
{

public:
	RectF() = default;
	RectF(float l, float r, float t, float b);
	RectF(const Vec2& topleft, const Vec2& bottomright);
	RectF(const Vec2& topleft, float width, float height);
	bool IsOverlapping(const RectF& val)const;
	static RectF FromCenter(const Vec2& center, float halfwidth, float halfheight);


public:
	float left;
	float top;
	float right;
	float bottom;

};