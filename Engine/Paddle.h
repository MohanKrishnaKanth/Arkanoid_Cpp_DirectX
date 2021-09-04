#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "Ball.h"
#include "Keyboard.h"
class Paddle
{
private:
	Vec2 position;
	float halfWidth = 150.0f;
	float halfHeight = 50.0f;
	static constexpr float speed = 600.0f;
	bool isCooldown = false;

public:
	Paddle(const Vec2& pos, float halfwidth, float halfheight);
	RectF GetBoundariesOfPaddle();
	void Draw(Graphics& gfx);
	bool isBallCollided(Ball& ball) ;
	void isWallCollided(const RectF& walls);
	void Update(Keyboard& kb,float dt);
	void ResetCooldown();
};