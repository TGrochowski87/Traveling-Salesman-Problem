#pragma once
#include "Graph.h"
#include "Timer.h"

using namespace std;

class Test
{
public:
	static void tspFromFile();
	static void tspGenerated();
	static void generateAndTest(int);

private:
	static int amount[7];
};

