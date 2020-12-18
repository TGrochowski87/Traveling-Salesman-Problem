/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/


#include "DynamicProgramming.h"

DynamicProgramming::DynamicProgramming(int nodeAmount, int** matrix) : AlgorithmTSP(nodeAmount, matrix) {}

void DynamicProgramming::run(int& finalCost, std::vector<unsigned>& finalPath)
{
    int  allVisitedMask = (1 << this->nodeAmount) - 1;
    int** maskMatrix = new int* [pow(2, this->nodeAmount)];
    std::vector<unsigned> path;

    for (int i = 0; i < pow(2, this->nodeAmount); i++)
    {
        maskMatrix[i] = new int[this->nodeAmount];
    }

    for (int i = 0; i < (1 << this->nodeAmount); i++)
    {
        for (int j = 0; j < this->nodeAmount; j++)
        {
            maskMatrix[i][j] = -1;
        }
    }

    path.push_back(0);
    finalCost = executeAlgorithm(maskMatrix, allVisitedMask, 1, 0);

    int temp = maskMatrix[1][1];
    for (int i = 0; i < this->nodeAmount - 1; i++)
    {
        path.push_back(temp - 1);
        temp = maskMatrix[temp][0];
    }

    finalPath.push_back(0);
    for (int i = 1; i < this->nodeAmount; i++)
    {
        finalPath.push_back(log2(path.at(i) - path.at(i - 1)));
    }

    for (int i = 0; i < this->nodeAmount; i++)
    {
        delete[] maskMatrix[i];
    }

    delete[] maskMatrix;
    return;
}

int DynamicProgramming::executeAlgorithm(int** maskMatrix, int allVisitedMask, int mask, int currentCity)
{
    if (mask == allVisitedMask)
    {
        return this->matrix[currentCity][0];
    }

    if (maskMatrix[mask][currentCity] != -1)
    {
        return maskMatrix[mask][currentCity];
    }

    int finalCost = INT32_MAX;
    for (int i = 0; i < this->nodeAmount; i++)
    {
        if ((mask & (1 << i)) == 0)
        {
            int newCost = this->matrix[currentCity][i] + executeAlgorithm(maskMatrix, allVisitedMask, mask | (1 << i), i);
            if (finalCost > newCost)
            {
                finalCost = newCost;
                if (mask == 1)
                    maskMatrix[mask][1] = mask | (1 << i);
                else
                    maskMatrix[mask][0] = mask | (1 << i);
            }
        }
    }
    return maskMatrix[mask][currentCity] = finalCost;
}
