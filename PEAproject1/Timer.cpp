#include "Timer.h"

void Timer::timerStart() //Saving starting time
{
	startPoint = high_resolution_clock::now();
}

void Timer::timerStop() //Saving ending time
{
	stopPoint = high_resolution_clock::now();
}

long Timer::elapsedTime() //Function returning the time that passed between two saved points in nanoseconds
{
	return duration_cast<milliseconds>(Timer::stopPoint - Timer::startPoint).count();
}