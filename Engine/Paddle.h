#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "Ball.h"
#include "Keyboard.h"
class Paddle
{
private:
	Vec2 position;
	float halfWidth;
	float halfHeight;
	static constexpr float speed = 600.0f;
	static constexpr float MaxXdirExitRatio = 2.0f;
	static constexpr float fixedZoneWidthRatio = 0.15f;

	bool isCooldown = false;
	float fixedZoneHalfWidth;
	float maxXdirExitFactor;
	float XdirExitFactor;

public:

	Paddle(const Vec2& pos, float halfwidth, float halfheight);
	RectF GetBoundariesOfPaddle();
	void Draw(Graphics& gfx);
	bool isBallCollided(Ball& ball) ;
	void isWallCollided(const RectF& walls);
	void Update(Keyboard& kb,float dt);
	void ResetCooldown();
	Vec2 GetPosition() const;
	void ResetPosition(const Vec2& p);
};