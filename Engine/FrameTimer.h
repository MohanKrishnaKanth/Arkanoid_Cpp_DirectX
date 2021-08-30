#pragma once
#include<chrono>

class FrameTimer
{
public:

	FrameTimer();
	float FrameDiff();

private:
	std::chrono::steady_clock::time_point last;
	float deltaframe;
};

