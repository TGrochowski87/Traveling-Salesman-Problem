#include "Test.h"

using namespace std;

int finalCost = INT32_MAX;

int main()
{
    //srand(time(NULL));

    //vector<unsigned> finalPath;
    //int finalCost = INT32_MAX;

    //Graph graph;
    //graph.readFromFile();

    //graph.SimulatedAnnealing(finalCost, finalPath, 1);
    //graph.tabuSearch(finalCost, finalPath);
    //finalPath = graph.greedyAlgorithm();
    //cout << "greedy = " << finalPath.size() << endl;
    //finalPath = graph.hybridAlgorithm();
    //cout << "hybrid = " << finalPath.size() << endl;

    //cout << finalCost << endl;
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