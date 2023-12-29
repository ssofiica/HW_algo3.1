#include "igraph.h"
#include <vector>
#include <cassert>
#include <functional>

void dfsInternal(const IGraph& graph, const int64_t& vertex,
    std::vector<bool>& visited, std::function<void(uint32_t)>& func)
{
    assert(0 <= vertex && vertex < graph.VerticesCount());
    visited[vertex] = true;
    func(vertex);

    for (const auto& nextVertex : graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
            dfsInternal(graph, nextVertex, visited, func);
    }
}

void DFS(const IGraph& graph, std::function<void(uint32_t)> func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        if (!visited[i])
            dfsInternal(graph, i, visited, func);
    }
}