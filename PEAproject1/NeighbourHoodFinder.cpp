/*
* Traveling Salesman Problem Solver By Tomasz Grochowski.
*/


#include "NeighbourHoodFinder.h"

std::vector<unsigned> NeighbourHoodFinder::neighbourhoodByInsert(std::vector<unsigned> path, int i, int j)
{
    std::vector<unsigned> neighbourPath = path;
    for (int k = i; k < j; k++)
    {
        std::swap(neighbourPath.at(k), neighbourPath.at(k + 1));
    }

    return neighbourPath;
}

std::vector<unsigned> NeighbourHoodFinder::neighbourhoodByReverse(std::vector<unsigned> path, int i, int j)
{
    std::vector<unsigned> neighbourPath = path;
    if (i < j)
        std::reverse(neighbourPath.begin() + i, neighbourPath.begin() + j);
    else if (i > j)
        std::reverse(neighbourPath.begin() + j, neighbourPath.begin() + i);

    return neighbourPath;
}

std::vector<unsigned> NeighbourHoodFinder::neighbourhoodBySwap(std::vector<unsigned> path, int i, int j)
{
    std::vector<unsigned> neighbourPath = path;
    std::swap(neighbourPath.at(i), neighbourPath.at(j));
    return neighbourPath;
}
