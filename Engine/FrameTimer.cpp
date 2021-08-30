#include "FrameTimer.h"



FrameTimer::FrameTimer()
{
	last = std::chrono::steady_clock::now();
}

float FrameTimer::FrameDiff()
{
	std::chrono::steady_clock::time_point oldFrame = last;
	last = std::chrono::steady_clock::now();
	std::chrono::duration<float> deltatime = last - oldFrame;
	return deltatime.count();
}
