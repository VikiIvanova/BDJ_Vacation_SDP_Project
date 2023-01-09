#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

struct Route
{
    std::string start;
    std::string end;
    int time;
};

struct City
{
    std::set<std::string> landmarks;
    std::vector<Route> routes;
    int timeAvailable;
};

// Read information for city
City readCity(const std::string &filename)
{
    City city;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return city;
    }

    int numLandmarks, numRoutes;
    file >> numLandmarks >> numRoutes;
    for (int i = 0; i < numRoutes; ++i)
    {
        Route route;
        file >> route.start >> route.end >> route.time;
        city.routes.push_back(route);
        city.landmarks.insert(route.start);
        city.landmarks.insert(route.end);
    }

    return city;
}

// Create graph
std::unordered_map<std::string, std::unordered_map<std::string, int>> graphBuild(const City &city)
{
    std::unordered_map<std::string, std::unordered_map<std::string, int>> graph;
    for (const Route &route : city.routes)
    {
        graph[route.start][route.end] = route.time;
        graph[route.end][route.start] = route.time;
    }
    return graph;
}

// Find the shortest path to a given city
std::vector<std::string> findRoute(const City &city, std::string destination)
{
    std::unordered_map<std::string, std::unordered_map<std::string, int>> graph = graphBuild(city);
    std::unordered_map<std::string, int> times;
    std::unordered_map<std::string, std::string> previous;
    std::priority_queue<std::pair<int, std::string>> pq;

    // Initialize times and previous values
    for (const std::string &landmark : city.landmarks)
    {
        times[landmark] = std::numeric_limits<int>::max();
        previous[landmark] = "";
    }
    times["Railstation"] = 0;
    pq.push({0, "Railstation"});

    // Implement Dijkstra's algorithm
    while (!pq.empty())
    {
        // Find the landmark with the smallest time
        std::pair<int, std::string> current = pq.top();
        pq.pop();

        // Update times and previous values for neighboring landmarks
        for (const std::pair<const std::string, int> &neighbor : graph[current.second])
        {
            int alt = times[current.second] + neighbor.second;
            if (alt < times[neighbor.first])
            {
                times[neighbor.first] = alt;
                previous[neighbor.first] = current.second;
                pq.push({times[neighbor.first], neighbor.first});
            }
        }
    }

    // Construct the shortest route
    std::vector<std::string> route;
    std::string landmark = destination;
    route.push_back(landmark);
    while (previous[landmark] != "Railstation")
    {
        route.push_back(previous[landmark]);
        landmark = previous[landmark];
    }
    route.push_back("Railstation");
    std::reverse(route.begin(), route.end());

    return route;
}
