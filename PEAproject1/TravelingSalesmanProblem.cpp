/*
Traveling Salesman Problem Solver By Tomasz Grochowski.
*/


#include "Test.h"

using namespace std;


/// <summary>
/// Main menu of the application
/// </summary>
/// <returns></returns>
int main()
{
    srand(time(NULL));

    //int finalCost = INT32_MAX;
    //std::vector<unsigned> finalPath;

    //Graph graph;
    //graph.readFromFile();

    //GeneticAlgorithm geneticAlgorithm(graph.getNodeAmount(), graph.getMatrix(), 1000, 0, 0);
    //geneticAlgorithm.run(finalCost, finalPath);

    //cout << "cost = " << finalCost << endl;
    //cout << endl;
    //for (unsigned u : finalPath)
    //{
    //    cout << u << " - " << flush;
    //}
    //cout << endl;

    bool running = true;
    cout << "Traveling Salesman Problem\n" << endl;

    while (1)
    {
        cout << "       MENU\n\n"
            << "1 - Generate graph randomly and begin testing\n"
            << "2 - Read graph from file and check correctness\n"
            << "0 - Close program" << endl;

        int grapthGenMethod;
        cin >> grapthGenMethod;

        switch (grapthGenMethod)
        {
        case 1:
        {
            Test::tspGenerated();
            break;
        }
        case 2:
        {
            Test::tspFromFile();
            break;
        }
        case 0:
        {
            exit(0);
            break;
        }
        default:
        {
            cout << "Choose one of available options!" << endl;
            break;
        }
        }
    }
    return 0;
}