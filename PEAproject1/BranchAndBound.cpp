/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/


#include "BranchAndBound.h"

BranchAndBound::BranchAndBound(int nodeAmount, int** matrix) : AlgorithmTSP(nodeAmount, matrix) {}

void BranchAndBound::run(int& finalCost, std::vector<unsigned>& finalPath)
{
    for (int i = 0; i < this->nodeAmount; i++)
    {
        for (int j = 0; j < this->nodeAmount; j++)
        {
            if (this->matrix[i][j] == 0)
            {
                this->matrix[i][j] = -1;
            }
        }
    }

    int* indexesX = new int[this->nodeAmount];
    int* indexesY = new int[this->nodeAmount];

    for (int i = 0; i < this->nodeAmount; i++)
    {
        indexesX[i] = i;
        indexesY[i] = i;
    }

    int* path = new int[this->nodeAmount];

    executeAlgorithm(indexesX, indexesY, this->nodeAmount, 0, finalCost, path, finalPath);

    delete[] indexesX;
    delete[] indexesY;
    delete[] path;
    return;
}

void BranchAndBound::executeAlgorithm(int* indexesX, int* indexesY, int currentLength, int currentCost, int& finalCost, int* path, std::vector<unsigned>& finalPath)
{
    int* minArray = new int[currentLength];
    int* minArray2 = new int[currentLength];

    for (int i = 0; i < currentLength; i++)
    {
        minArray[i] = INT32_MAX;
    }

    reduceMatrix(currentLength, minArray, currentCost);

    for (int i = 0; i < currentLength; i++)
    {
        minArray[i] = INT32_MAX;
    }

    reduceMatrix(currentLength, minArray, currentCost, true);

    if (currentLength == 2)
    {
        for (int i = 0; i < 2; i++)
        {
            path[indexesX[i]] = indexesY[i];
        }

        int city = 0;
        for (int i = 0; i < this->nodeAmount; i++)
        {
            finalPath.push_back(city);
            city = path[city];
        }

        finalCost = currentCost;
        return;
    }

    for (int i = 0; i < currentLength; i++)
    {
        minArray[i] = INT32_MAX;
        minArray2[i] = INT32_MAX;
    }

    findMin(currentLength, minArray, true);
    findMin(currentLength, minArray2);

    int maxOfMin1 = 0;
    int maxOfMin2 = 0;
    int maxOfMinIndexY = 0;
    int maxOfMinIndexX = 0;
    for (int i = 0; i < currentLength; i++)
    {
        if (minArray[i] > maxOfMin1)
        {
            maxOfMin1 = minArray[i];
            maxOfMinIndexY = i;
        }
        if (minArray2[i] > maxOfMin2)
        {
            maxOfMin2 = minArray2[i];
            maxOfMinIndexX = i;
        }
    }

    if (maxOfMin1 >= maxOfMin2)
    {
        for (int i = 0; i < currentLength; i++)
        {
            if (this->matrix[i][maxOfMinIndexY] == 0)
            {
                maxOfMinIndexX = i;
            }
        }
    }
    else
    {
        for (int i = 0; i < currentLength; i++)
        {
            if (this->matrix[maxOfMinIndexX][i] == 0)
            {
                maxOfMinIndexY = i;
            }
        }
    }

    path[indexesX[maxOfMinIndexX]] = indexesY[maxOfMinIndexY];

    this->matrix[indexesY[maxOfMinIndexY]][indexesX[maxOfMinIndexX]] = -1;

    for (int i = maxOfMinIndexY; i < currentLength - 1; i++)
    {
        for (int j = 0; j < currentLength; j++)
        {
            this->matrix[j][i] = this->matrix[j][i + 1];
        }
    }

    for (int i = maxOfMinIndexX; i < currentLength - 1; i++)
    {
        for (int j = 0; j < currentLength; j++)
        {
            this->matrix[i][j] = this->matrix[i + 1][j];
        }
    }

    for (int i = maxOfMinIndexX; i < currentLength - 1; i++)
    {
        indexesX[i] = indexesX[i + 1];
    }
    for (int i = maxOfMinIndexY; i < currentLength - 1; i++)
    {
        indexesY[i] = indexesY[i + 1];
    }
    delete[] minArray;
    delete[] minArray2;
    executeAlgorithm(indexesX, indexesY, (currentLength - 1), currentCost, finalCost, path, finalPath);

    return;
}

void BranchAndBound::findMin(const int currentLength, int* minArray, bool column)
{
    for (int i = 0; i < currentLength; i++)
    {
        int zeros = 0;
        for (int j = 0; j < currentLength; j++)
        {
            if (column)
            {
                if (this->matrix[j][i] == 0)
                {
                    zeros++;
                    if (zeros > 1)
                    {
                        minArray[i] = 0;
                        break;
                    }
                    continue;
                }
                if (this->matrix[j][i] > 0 && this->matrix[j][i] < minArray[i])
                {
                    minArray[i] = this->matrix[j][i];
                }
            }
            else
            {
                if (this->matrix[i][j] == 0)
                {
                    zeros++;
                    if (zeros > 1)
                    {
                        minArray[i] = 0;
                        break;
                    }
                    continue;
                }
                if (this->matrix[i][j] > 0 && this->matrix[i][j] < minArray[i])
                {
                    minArray[i] = this->matrix[i][j];
                }
            }
        }
    }
    return;
}

void BranchAndBound::reduceMatrix(const int currentLength, int* minArray, int& currentCost, bool column)
{
    for (int i = 0; i < currentLength; i++)
    {
        for (int j = 0; j < currentLength; j++)
        {
            if (column)
            {
                if (this->matrix[j][i] >= 0 && this->matrix[j][i] < minArray[i])
                {
                    minArray[i] = this->matrix[j][i];
                }
            }
            else
            {
                if (this->matrix[i][j] >= 0 && this->matrix[i][j] < minArray[i])
                {
                    minArray[i] = this->matrix[i][j];
                }
            }
        }
    }

    for (int i = 0; i < currentLength; i++)
    {
        for (int j = 0; j < currentLength; j++)
        {
            if (column)
                this->matrix[j][i] -= minArray[i];
            else
                this->matrix[i][j] -= minArray[i];
        }
        currentCost += minArray[i];
    }
    return;
}
