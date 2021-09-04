#pragma once
#include "Graphics.h"
#include "Vec2.h"
class SpriteCode
{
public:
	static void DrawBall(const Vec2& center, Graphics& gfx);
	static void DrawGameover(const Vec2& center, Graphics& gfx);
};