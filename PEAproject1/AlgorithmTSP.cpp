/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/


#include "AlgorithmTSP.h"

AlgorithmTSP::AlgorithmTSP(int nodeAmount, int** matrix)
{
	this->nodeAmount = nodeAmount;
	this->matrix = matrix;
}
