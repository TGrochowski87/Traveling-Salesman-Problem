/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/


#include "Timer.h"

void Timer::timerStart()
{
	startPoint = high_resolution_clock::now();
}

void Timer::timerStop()
{
	stopPoint = high_resolution_clock::now();
}

long Timer::elapsedTime()
{
	return duration_cast<nanoseconds>(Timer::stopPoint - Timer::startPoint).count();
}