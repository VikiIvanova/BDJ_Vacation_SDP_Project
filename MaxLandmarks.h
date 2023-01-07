#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

// struct Landmark
// {
//     std::string name;
//     // int time;
// };

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

    // for (int i = 0; i < numLandmarks; ++i)
    // {
    //     Landmark landmark;
    //     file >> landmark.name >> landmark.time;
    //     city.landmarks.push_back(landmark);
    // }

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

std::unordered_map<std::string, std::unordered_map<std::string, int>> graphBuild(const City &city)
{
    std::unordered_map<std::string, std::unordered_map<std::string, int>> graph;
    for (const auto &route : city.routes)
    {
        graph[route.start][route.end] = route.time;
        graph[route.end][route.start] = route.time;
    }
    return graph;
}

std::vector<std::string> findRoute(const City &city)
{
    std::unordered_map<std::string, std::unordered_map<std::string, int>> graph = graphBuild(city);
    std::unordered_map<std::string, int> times;
    std::unordered_map<std::string, std::string> previous;
    std::priority_queue<std::pair<int, std::string>> pq;

    // Initialize times and previous values
    for (const auto &landmark : city.landmarks)
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
        auto current = pq.top();
        pq.pop();

        // If the current landmark is the end landmark, we have found the shortest route
        // if (current.second == city.end)
        // {
        //     break;
        // }

        // Update times and previous values for neighboring landmarks
        for (const auto &neighbor : graph[current.second])
        {
            auto alt = times[current.second] + neighbor.second;
            if (alt < times[neighbor.first])
            {
                times[neighbor.first] = alt;
                previous[neighbor.first] = current.second;
                pq.push({times[neighbor.first], neighbor.first});
            }
        }
    }

    // Construct the shortest route by following the
    std::vector<std::string> route;
    for (std::string landmark = "Railstation"; landmark != ""; landmark = previous[landmark])
    {
        route.push_back(landmark);
    }
    std::reverse(route.begin(), route.end());

    return route;
}
