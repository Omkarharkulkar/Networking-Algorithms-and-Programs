#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max(); // Infinity value

// Structure to represent a router
struct Router 
{
    int id;
    vector<int> neighbors;
    vector<int> costs;
};

// Function to find the router with the minimum cost
int findMinCostRouter(const vector<int>& distances, const vector<bool>& visited) 
{
    int minCost = INF;
    int minRouter = -1;
    for (int i = 0; i < distances.size(); ++i) 
	{
        if (!visited[i] && distances[i] < minCost) 
		{
            minCost = distances[i];
            minRouter = i;
        }
    }
    return minRouter;
}

// Function to perform link state routing
void linkStateRouting(vector<Router>& routers, int sourceRouter) 
{
    int numRouters = routers.size();

    vector<int> distances(numRouters, INF);  // Shortest distances from source to all routers
    vector<bool> visited(numRouters, false); // Tracks visited routers
    vector<int> previous(numRouters, -1);    // Previous router in the shortest path

    distances[sourceRouter] = 0;

    for (int i = 0; i < numRouters - 1; ++i) 
	{
        int currentRouter = findMinCostRouter(distances, visited);
        visited[currentRouter] = true;

        for (int j = 0; j < routers[currentRouter].neighbors.size(); ++j) 
		{
            int neighborRouter = routers[currentRouter].neighbors[j];
            int cost = routers[currentRouter].costs[j];

            if (!visited[neighborRouter] && distances[currentRouter] != INF && distances[currentRouter] + cost < distances[neighborRouter]) 
			{
                distances[neighborRouter] = distances[currentRouter] + cost;
                previous[neighborRouter] = currentRouter;
            }
        }
    }

    // Display the shortest paths from the source router to all other routers
    cout << "Shortest paths from Router " << routers[sourceRouter].id << ":" << endl;
    for (int i = 0; i < numRouters; ++i) 
	{
        if (i != sourceRouter) {
            cout << "Router " << routers[i].id << ": ";
            int j = i;
            while (j != -1) 
			{
                cout << routers[j].id << " <- ";
                j = previous[j];
            }
            cout << "Cost: " << distances[i] << endl;
        }
    }
}

int main() 
{
    int numRouters;
    cout << "Enter the number of routers: ";
    cin >> numRouters;

    vector<Router> routers(numRouters);

    // Initialize routers
    for (int i = 0; i < numRouters; ++i) 
	{
        routers[i].id = i + 1;

        int numNeighbors;
        cout << "Enter the number of neighbors for Router " << routers[i].id << ": ";
        cin >> numNeighbors;

        routers[i].neighbors.resize(numNeighbors);
        routers[i].costs.resize(numNeighbors);

        cout << "Enter the neighbor routers and their costs:" << endl;
        for (int j = 0; j < numNeighbors; ++j) 
		{
            cin >> routers[i].neighbors[j] >> routers[i].costs[j];
        }
    }

    int sourceRouter;
    cout << "Enter the source router: ";
    cin >> sourceRouter;

    // Perform link state routing
    linkStateRouting(routers, sourceRouter - 1);

    return 0;
}

