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
	static constexpr float speed = 600.0f;
public:
	Ball() = default;
	Ball(const Vec2 pos, Vec2 v);
	void Draw(Graphics& gfx) const;
	void Update(float dt);
	int& isCollidedToWalls(const RectF& walls);
	RectF GetBoundariesofBall()const;
	void ReboundX();
	void ReboundY();
	Vec2 GetPosition() const;
	Vec2 GetVelocity() const;
	void SetDirection(const Vec2& value);


};