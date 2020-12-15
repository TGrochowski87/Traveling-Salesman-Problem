#pragma once
#include <chrono>

using namespace std::chrono;

class Timer
{
public:
	void timerStart();
	void timerStop();
	long elapsedTime();

private:
	high_resolution_clock::time_point startPoint;
	high_resolution_clock::time_point stopPoint;
};

