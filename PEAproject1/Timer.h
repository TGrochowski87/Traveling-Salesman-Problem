/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/


#pragma once
#include <chrono>

using namespace std::chrono;

/// <summary>
/// A simple class for measuring time
/// </summary>
class Timer
{
public:
	/// <summary>
	/// Saving current time (use before algorithm execution)
	/// </summary>
	void timerStart();

	/// <summary>
	/// Saving current time (use after algorithm execution)
	/// </summary>
	void timerStop();

	/// <summary>
	/// Showing measured time
	/// </summary>
	/// <returns>Time</returns>
	long elapsedTime();

private:
	high_resolution_clock::time_point startPoint;
	high_resolution_clock::time_point stopPoint;
};

