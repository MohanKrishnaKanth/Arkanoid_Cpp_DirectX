#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "SpriteCode.h"
class Ball
{
private:
	Vec2 position;
	Vec2 vel;
	static constexpr float radius = 7.0f;
public:
	Ball(Vec2 pos, Vec2 v);
	void Draw(Graphics& gfx) const;
	void Update(float dt);
	bool isCollidedToWalls(const RectF& walls);
	RectF GetBoundariesofBall()const;
	void ReboundX();
	void ReboundY();


};