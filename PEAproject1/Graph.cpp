#include "Graph.h"

Graph::~Graph() //Destructor
{
	for (int i = 0; i < this->nodeAmount; i++)
	{
		delete[] this->matrix[i];
	}

	delete[] this->matrix;
}

void Graph::generate(int amount) //Randomize graph
{
    this->nodeAmount = amount;

    this->matrix = new int* [this->nodeAmount];
    for (int i = 0; i < this->nodeAmount; i++)
    {
        this->matrix[i] = new int[this->nodeAmount];
    }

    for (int j = 0; j < this->nodeAmount; j++)
    {
        for (int i = 0; i < this->nodeAmount; i++)
        {
            if(i == j)
                this->matrix[j][i] = 0;
            else
                this->matrix[j][i] = rand() & 99 + 1;
        }
    }
}

void Graph::readFromFile() //Reading graph from file
{
	int justReadValue;

	cout << "Name of file to read from: " << flush;
	string fileName;
	cin >> fileName;

	ifstream file(fileName);
	if(file.is_open())
	{
		file >> this->nodeAmount; //Saving amount of cities
		if (file.fail())
		{
			cout << "ERROR - Could not read cities' quantity!" << endl;
			return;
		}
		else
		{
			this->matrix = new int* [this->nodeAmount]; //Creating matrix

			for (int i = 0; i < this->nodeAmount; i++)
			{
				this->matrix[i] = new int[this->nodeAmount];
			}

			for (int j = 0; j < this->nodeAmount; j++) //Filling matrix
			{
				for (int i = 0; i < this->nodeAmount; i++)
				{
					file >> justReadValue;
					if (file.fail())
					{
						cout << "ERROR - Could not read matrix values!" << endl;
						return;
					}
					else
					{
						this->matrix[j][i] = justReadValue;
					}
				}
			}
			file.close();
		}
	}
	else
	{
		cout << "ERROR - Could not open file of given name!" << endl;
		return;
	}
}


int Graph::DPalgorithm(int** maskMatrix, int allVisitedMask, int mask, int currentCity)
{
    if (mask == allVisitedMask) //When all cities are visited add cost of going back to 0
    {
        return this->matrix[currentCity][0];
    }

    if (maskMatrix[mask][currentCity] != -1) //Saving cost of current path to avoid repetition
    {
        return maskMatrix[mask][currentCity];
    }

    int finalCost = INT32_MAX;
    for (int i = 0; i < this->nodeAmount; i++) //Iterating by every city
    {
        if ((mask & (1 << i)) == 0) //If city i has not been already visited, add it to path
        {
            int newCost = this->matrix[currentCity][i] + DPalgorithm(maskMatrix, allVisitedMask, mask | (1 << i), i); //Summing new cost
            if (finalCost > newCost)
            {
                finalCost = newCost;
                if(mask == 1)
                    maskMatrix[mask][1] = mask | (1 << i); //Saving path
                else
                    maskMatrix[mask][0] = mask | (1 << i);
            }
        }
    }
    return maskMatrix[mask][currentCity] = finalCost;
}

void Graph::DPalgorithm(int& finalCost, vector<unsigned>& finalPath) //Dynamic programming initializing method
{
    int  allVisitedMask = (1 << this->nodeAmount) - 1; //Bit mask of the state of all cities visited
    int** maskMatrix = new int* [pow(2, this->nodeAmount)]; //A matrix optimizing the process by saving already checked paths
    vector<unsigned> path;

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
    finalCost = DPalgorithm(maskMatrix, allVisitedMask, 1, 0);

    int temp = maskMatrix[1][1];
    for (int i = 0; i < this->nodeAmount - 1; i++) //Saving final path as decimal version of mask
    {
        path.push_back(temp - 1);
        temp = maskMatrix[temp][0];
    }

    finalPath.push_back(0);
    for (int i = 1; i < this->nodeAmount; i++) //Saving final path
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

void Graph::SimulatedAnnealing(int& finalCost, vector<unsigned>& finalPath, int neighbourhoodType)
{
    srand(time(NULL));

    finalPath = greedyAlgorithm();
    finalPath.push_back(0); //City 0 at the end
    double temperatureMax = 1;
    double temperature = temperatureMax;

    long maxit;
    if (this->nodeAmount < 10)
    {
        maxit = this->nodeAmount;
        for (int i = this->nodeAmount - 1; i > 0; i--)
        {
            maxit = maxit * i;
        }
    }
    else
    {
        maxit = 9;
        for (int i = 8; i > 1; i--)
        {
            maxit *= i;
        }
        maxit += (this->nodeAmount/10)*pow(this->nodeAmount, 2) * log2(this->nodeAmount);
    }
    for(long i = 0; i < maxit;i++)
    {
        finalCost = newCalculation(finalPath);
        vector<unsigned> neighbourRoute = finalPath;

        int first = rand() % (this->nodeAmount-1) + 1;
        int second = rand() % (this->nodeAmount-1) + 1;

        switch (neighbourhoodType)
        {
        case 0:
            swap(neighbourRoute.at(first), neighbourRoute.at(second));
            break;
        case 1:
            if(first < second)
                reverse(neighbourRoute.begin() + first, neighbourRoute.begin() + second);
            else if(first > second)
                reverse(neighbourRoute.begin() + second, neighbourRoute.begin() + first);
            else if(first == second)
                continue;
        }

        int neighbourCost = newCalculation(neighbourRoute);

        int energy = finalCost - neighbourCost;
        if (energy > 0)
        {
            finalPath = neighbourRoute;
        }
        else if (exp(energy / temperature) > (float)rand() / (float)RAND_MAX)
        {
            finalPath = neighbourRoute;
        }

        temperature *= 0.9999;
    }
}

void Graph::tabuSearch(int& finalCost, vector<unsigned>& finalPath)
{
    //srand(time(NULL));

    finalPath = greedyAlgorithm();
    finalPath.push_back(0); //City 0 at the end
    finalCost = newCalculation(finalPath);

    vector<unsigned> optimalPath = finalPath;
    int optimalCost = finalCost;

    //map<int[2], int> tabuMap;
    int** tabu = new int*[this->nodeAmount - 2];
    for (int i = 0; i < this->nodeAmount - 1; i++)
    {
        tabu[i] = new int[this->nodeAmount - 2];
    }
    for (int i = 0; i < this->nodeAmount - 1; i++)
    {
        for (int j = 0; j < this->nodeAmount - 1; j++)
        {
            tabu[i][j] = 0;
        }
    }

    int criticalRepetition = 100;

    for(int x = 0; x < 4000; x++)
    {
        //cout << x << endl;
        for (int i = 0; i < this->nodeAmount - 1; i++)
        {
            for (int j = 0 + i; j < this->nodeAmount - 1; j++)
            {
                if (tabu[i][j] > 0)
                    tabu[i][j]--;
            }
        }

        //vector<unsigned> neighbourRoute = finalPath;

        int newCost = INT32_MAX;
        int bestI = 0;
        int bestJ = 0;
        for (int i = 1; i < this->nodeAmount - 1; i++)
        {
            for (int j = 1 + i; j < this->nodeAmount; j++)
            {
                //vector<unsigned> neighbourRoute = optimalPath;
                //swap(neighbourRoute.at(i-1), neighbourRoute.at(j-2));
                vector<unsigned> neighbourRoute = insert(optimalPath, i, j);

                int currentCost = newCalculation(neighbourRoute);

                //Kryterium aspiracji
                if (tabu[i - 1][j - 2] > 0 && currentCost >= finalCost)
                    continue;

                if (currentCost < newCost)
                {
                    newCost = currentCost;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        //cout << endl;
        //for (int y = 0; y < this->nodeAmount - 1; y++)
        //{
        //    for (int z = 0; z < this->nodeAmount - 1; z++)
        //    {
        //        cout << tabu[y][z] << ", " << flush;
        //    }
        //    cout << endl;
        //}
        //cout << endl;

        if (bestI == 0 || bestJ == 0)
        {
            cout << "nothing found" << endl;
            continue;
        }
        //cout << optimalCost << endl;

        //Dywersyfikacja
        if (newCost == optimalCost)
        {
            criticalRepetition--;
            if (criticalRepetition == 0)
            {
                optimalPath = hybridAlgorithm();
                continue;
            }
        }
        else
        {
            criticalRepetition = 100;
        }

        swap(optimalPath.at(bestI - 1), optimalPath.at(bestJ - 2));
        optimalCost = newCost;

        if (optimalCost < finalCost)
        {
            finalPath = optimalPath;
            finalCost = optimalCost;
        }

        //for (unsigned u : finalPath)
        //{
        //    cout << u << " - " << flush;
        //}
        //cout << endl;

        tabu[bestI - 1][bestJ - 2] = 3;

    }
}

vector<unsigned> Graph::greedyAlgorithm()
{
    vector<unsigned> initialPath;
    initialPath.push_back(0);

    int next;
    int cost;
    for (int i = 1; i < this->nodeAmount; i++)
    {
        next = 0;
        cost = INT_MAX;
        for (int j = 0; j < this->nodeAmount; j++)
        {
            if (find(initialPath.begin(), initialPath.end(), j) == initialPath.end())
            {
                if (this->matrix[initialPath.back()][j] < cost)
                {
                    next = j;
                    cost = this->matrix[initialPath.back()][j];
                }
            }
        }
        initialPath.push_back(next);
    }
    return initialPath;
}

vector<unsigned> Graph::hybridAlgorithm()
{
    vector<unsigned> initialPath;
    initialPath.push_back(0);

    int randomizeAmount = rand() % (this->nodeAmount - 1) + 1;

    while (initialPath.size() - 1 < randomizeAmount)
    {
        unsigned randomNode = rand() % randomizeAmount + 1;
        bool used = false;

        for (int j = 1; j < initialPath.size(); j++)
        {
            if (find(initialPath.begin() + 1, initialPath.end(), randomNode) != initialPath.end())
            {
                used = true;
            }
        }
        if(!used)
            initialPath.push_back(randomNode);
    }

    int next;
    int cost;
    for (int i = 1; i < this->nodeAmount - randomizeAmount; i++)
    {
        next = 0;
        cost = INT_MAX;
        for (int j = 0; j < this->nodeAmount; j++)
        {
            if (find(initialPath.begin(), initialPath.end(), j) == initialPath.end())
            {
                if (this->matrix[initialPath.back()][j] < cost)
                {
                    next = j;
                    cost = this->matrix[initialPath.back()][j];
                }
            }
        }
        initialPath.push_back(next);
    }
    initialPath.push_back(0);

    return initialPath;
}

vector<unsigned> Graph::insert(vector<unsigned> path, int i, int j)
{
    vector<unsigned> neighbourPath = path;
    for (int k = i; k < j; k++)
    {
        swap(neighbourPath.at(k), neighbourPath.at(k + 1));
    }
    return neighbourPath;
}

int Graph::newCalculation(vector<unsigned> path) //Currently includes cost of going back to city 0
{
    int calculatedCost = 0;
    for (int i = 0; i < this->nodeAmount; i++)
    {
        calculatedCost += this->matrix[path.at(i)][path.at(i + 1)];
    }
    return calculatedCost;
}

void Graph::BBAlgorithm(int* indexesX, int* indexesY, int currentLength, int currentCost, int& finalCost, int* path, vector<unsigned>& finalPath)
{
    int* minArray = new int[currentLength]; //Arrays of the smallest numbers in rows and columns for reduction
    int* minArray2 = new int[currentLength];

    for (int i = 0; i < currentLength; i++)
    {
        minArray[i] = INT32_MAX;
    }

    reduceMatrix(currentLength, minArray, currentCost); //Reduction on rows

    for (int i = 0; i < currentLength; i++)
    {
        minArray[i] = INT32_MAX;
    }

    reduceMatrix(currentLength, minArray, currentCost, true); //Reduction on columns

    if (currentLength == 2) //Final stage of algorithm (Saving path and cost)
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

    for (int i = 0; i < currentLength; i++) //Reseting arrays
    {
        minArray[i] = INT32_MAX;
        minArray2[i] = INT32_MAX;
    }

    findMin(currentLength, minArray, true); //Seeking for the lowest numbers in rows and columns
    findMin(currentLength, minArray2);

    int maxOfMin1 = 0;
    int maxOfMin2 = 0;
    int maxOfMinIndexY = 0;
    int maxOfMinIndexX = 0;
    for (int i = 0; i < currentLength; i++) //Saving higest numbers from arrays filled with minimal numbers
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

    //FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
    if (maxOfMin1 >= maxOfMin2) //Saving the highest number with it's index
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

    path[indexesX[maxOfMinIndexX]] = indexesY[maxOfMinIndexY]; //Updating path 

    this->matrix[indexesY[maxOfMinIndexY]][indexesX[maxOfMinIndexX]] = -1; //Blocking the way of comming back

    //HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
    for (int i = maxOfMinIndexY; i < currentLength - 1; i++) //Deleting now unavailable paths to ptimize the algorithm..
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

    for (int i = maxOfMinIndexX; i < currentLength - 1; i++)  //... with indexes
    {
        indexesX[i] = indexesX[i + 1];
    }
    for (int i = maxOfMinIndexY; i < currentLength - 1; i++)
    {
        indexesY[i] = indexesY[i + 1];
    }
    delete[] minArray;
    delete[] minArray2;
    BBAlgorithm(indexesX, indexesY, (currentLength - 1), currentCost, finalCost, path, finalPath);

    return;
}


void Graph::findMin(const int currentLength, int* minArray, bool column) //Finding and saving minimal numbers in rows and columns of matrix
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
                    if (zeros > 1) //Zeros are considered only when there are more than 1 found
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

void Graph::reduceMatrix(const int currentLength, int* minArray, int& currentCost, bool column) //Reducing matrix
{
    for (int i = 0; i < currentLength; i++) //Finding the lowest numbers in rows and columns
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

    for (int i = 0; i < currentLength; i++) //Reducing the matrix by previously found numbers
    {
        for (int j = 0; j < currentLength; j++)
        {
            if(column)
                this->matrix[j][i] -= minArray[i];
            else
                this->matrix[i][j] -= minArray[i];
        }
        currentCost += minArray[i];
    }
    return;
}

void Graph::BBAlgorithm(int& finalCost, vector<unsigned>& finalPath) //Brand and bound initializing method
{
    for (int i = 0; i < this->nodeAmount; i++) //Unavailable paths need to be negative
    {
        for (int j = 0; j < this->nodeAmount; j++)
        {
            if (this->matrix[i][j] == 0)
            {
                this->matrix[i][j] = -1;
            }
        }
    }

    int* indexesX = new int[this->nodeAmount]; //Rows and columns need to have indexes for this algorithm
    int* indexesY = new int[this->nodeAmount];

    for (int i = 0; i < this->nodeAmount; i++)
    {
        indexesX[i] = i;
        indexesY[i] = i;
    }

    int* path = new int[this->nodeAmount];

    BBAlgorithm(indexesX, indexesY, this->nodeAmount, 0, finalCost, path, finalPath);

    delete[] indexesX;
    delete[] indexesY;
    delete[] path;
    return;
}

void Graph::BBAlgorithm2(int& finalCost, vector<unsigned>& finalPath) //Second method of implementing branch and bound
{
    std::priority_queue<std::vector<unsigned>, std::vector< std::vector<unsigned> >, priorityCompare> queue; //Queue that segregates

    std::vector<unsigned> currentOptimalPath; //The most optimal path at the moment
    int currentCost = -1;
    std::vector<unsigned> path; //Current path

    path.push_back(0);
    path.push_back(0);
    queue.push(path);

    while (!queue.empty())
    {
        path = queue.top(); //Check the next most probable path
        queue.pop();

        if (path.at(0) < currentCost || currentCost == -1) //Check if it is worth checking. If not the algorithm can stop because of using priority queue
        {
            for (int i = 0; i < this->nodeAmount; i++)
            {
                bool visited = false;
                for (int j = 1; j < path.size(); j++) //If current city has already been chacked we can skip it
                {
                    if (path.at(j) == i)
                    {
                        visited = true;
                        break;
                    }
                }
                if (visited)
                    continue;

                std::vector<unsigned> pathCopy = path; //Creating a copy of path so it can be modified
                pathCopy.push_back(i);

                if(pathCopy.size() <= this->nodeAmount) //Finding new path
                {
                    pathCopy.at(0) = 0;
                    for (int j = 1; j < pathCopy.size() - 1; j++) //Summing current cost
                    {
                        pathCopy.at(0) += this->matrix[pathCopy.at(j)][pathCopy.at(j + 1)];
                    }

                    for (int j = 1; j < this->nodeAmount; j++)
                    {
                        bool visited = false;
                        for (int k = 1; k < path.size(); k++) //If current city has already been chacked we can skip it
                        {
                            if (j == path.at(k))
                            {
                                visited = true;
                                break;
                            }
                        }
                        if (visited)
                            continue;

                        int minCost = -1;
                        for (int k = 0; k < this->nodeAmount; k++)
                        {
                            if (j == i && k == 0) //Ignoring the path to city 0
                                continue;

                            bool visited = false;
                            for (int p = 2; p < pathCopy.size(); p++)
                            {
                                if (k == pathCopy.at(p))
                                {
                                    visited = true;
                                    break;
                                }
                            }
                            if (visited)
                                continue;

                            if (k == j) //Ignoring the path to itself
                                continue;
                            unsigned consideredLength = this->matrix[j][k];

                            if (minCost == -1 || minCost > consideredLength)
                                minCost = consideredLength;
                        }
                        pathCopy.at(0) += minCost;

                    }

                    if (currentCost == -1 || pathCopy.at(0) < currentCost)
                    {
                        queue.push(pathCopy);
                    }
                } 
                else //If every city is visited we can save new path and it's cost
                {
                    pathCopy.push_back(0);

                    pathCopy.at(0) = 0;

                    for (int j = 1; j < pathCopy.size() - 1; j++)
                    {
                        pathCopy.at(0) += this->matrix[pathCopy.at(j)][pathCopy.at(j + 1)];
                    }
                    if (currentCost == -1 || pathCopy.at(0) < currentCost)
                    {
                        currentCost = pathCopy.at(0);
                        pathCopy.erase(pathCopy.begin());
                        currentOptimalPath = pathCopy;
                    }
                }
            }
        }
        else
        {
            break;
        }
    }

    finalCost = currentCost; //Saving final path and cost
    currentOptimalPath.pop_back();
    finalPath = currentOptimalPath;
}


bool Graph::findInArray(int* array, int value) //Function checking if city is already visited
{
    for (int i = 0; i < this->nodeAmount; i++)
    {
        if (array[i] == value)
            return true;
    }
    return false;
}

void Graph::bruteForce(int visitedCities[], int visitedArrayLength, int currentCity, int currentCost, int& finalCost, vector<unsigned>& finalPath)
{
    if (currentCost > finalCost) //Whenever new cost is bigger than already saved one, go back
        return;

    if (visitedArrayLength == this->nodeAmount) //When all cities are visited, check if new cost is to be saved
    {
        currentCost += this->matrix[currentCity][0];
        if (currentCost < finalCost) //If the new cost is smaller, it replaces the rpevious one
        {
            finalPath.clear();
            finalCost = currentCost;
            for (int i = 0; i < this->nodeAmount; i++) //Saving path
            {
                finalPath.push_back(visitedCities[i]);
            }
        }
    }

    for (int i = 0; i < this->nodeAmount; i++)
    {
        if (!findInArray(visitedCities, i)) //Check if city i is already visited
        {
            int savedNum = visitedCities[visitedArrayLength];

            visitedCities[visitedArrayLength] = i;
            bruteForce(visitedCities, visitedArrayLength + 1, i, (currentCost + this->matrix[currentCity][i]), finalCost, finalPath);
            visitedCities[visitedArrayLength] = savedNum;
        }
    }
    return;
}

void Graph::bruteForce(int& finalCost, vector<unsigned>& finalPath) //Brute force initializing method
{
    int* visitedCities = new int[this->nodeAmount]; //Array of visited cities
    for (int i = 0; i < this->nodeAmount; i++)
        visitedCities[i] = -1;

    visitedCities[0] = 0;

    bruteForce(visitedCities, 1, 0, 0, finalCost, finalPath);

    delete[] visitedCities;
    return;
}