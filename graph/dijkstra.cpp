#include <iostream>
#include <vector>
#include <unordered_set>
#include <list>

void printPathFromPrev(std::vector<int> prev, int src, int dst)
{
    if (src == dst) {
        std::cout << "Path: " << src << std::endl;
        return;
    }

    std::list<int> path;
    path.push_front(dst);
    int current = prev[dst];
    while (current != src)
    {
        path.push_front(current);
        current = prev[current];
    }
    path.push_front(src);

    std::string s = "";
    for (auto it = path.begin(); it != path.end(); ++it)
    {
        s += std::to_string(*it);
        s += "->";
    }
    s = s.substr(0, s.length() - 2);
    std::cout << "Path: " << s << std::endl;
}

/// @brief
/// @param graph
/// @param src
/// @param dst
/// @return shortest distance
int dijkstra(std::vector<std::vector<int>> graph, int src, int dst)
{
    if (dst == src)
    {
        return 0;
    }

    int V = graph.size();

    std::vector<int> distances;
    for (int i = 0; i < V; ++i)
    {
        distances.push_back(INT_MAX);
    }
    std::unordered_set<int> unexplored;
    for (int i = 0; i < V; ++i)
    {
        unexplored.insert(i);
    }
    std::vector<int> prev;
    for (int i = 0; i < V; ++i)
    {
        prev.push_back(-1);
    }
    distances[src] = 0;
    while (!unexplored.empty())
    {
        // Find the unexplored node with min distance
        int min_node;
        int min_distance = INT_MAX;
        for (int u : unexplored)
        {
            if (distances[u] < min_distance)
            {
                min_node = u;
                min_distance = distances[u];
            }
        }

        // std::cout << "now explore node: " << min_node << std::endl;
        // for (int i = 0; i < distances.size(); ++i)
        // {
        //     std::cout << i << ", " << distances[i] << std::endl;
        // }

        // explore the node
        unexplored.erase(min_node);

        for (int i = 0; i < V; ++i)
        {
            if (graph[min_node][i] == 0)
            {
                continue;
            }
            int total = distances[min_node] + graph[min_node][i];
            if (total < distances[i])
            {
                distances[i] = total;
                prev[i] = min_node;
            }
        }
    }

    // std::cout << "prev: " << std::endl;
    // for (int i = 0; i < V; ++i)
    // {
    //     std::string stop = ((i == V - 1) ? "" : ", ");
    //     std::cout << prev[i] << stop;
    // }
    // std::cout << std::endl;

    for (int i = 0; i < V; ++i)
    {
        printPathFromPrev(prev, src, i);
        std::cout << "Min distance: " << distances[i] << std::endl;
    }

    return distances[dst];
}

int main()
{
    std::cout << "C++ version: " << __cplusplus << std::endl;

    std::vector<std::vector<int>> graph = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                                           {4, 0, 8, 0, 0, 0, 0, 11, 0},
                                           {0, 8, 0, 7, 0, 4, 0, 0, 2},
                                           {0, 0, 7, 0, 9, 14, 0, 0, 0},
                                           {0, 0, 0, 9, 0, 10, 0, 0, 0},
                                           {0, 0, 4, 14, 10, 0, 2, 0, 0},
                                           {0, 0, 0, 0, 0, 2, 0, 1, 6},
                                           {8, 11, 0, 0, 0, 0, 1, 0, 7},
                                           {0, 0, 2, 0, 0, 0, 6, 7, 0}};

    int from = 0;
    int to = 8;
    int answer = dijkstra(graph, from, to);
    std::cout << "Min distance from " << from << " to " << to << ": " << answer << std::endl;
}