#include "igraph.h"
#include <queue>
#include <vector>
#include <cassert>
#include <functional>

void bfsInternal(const IGraph& graph, const int& vertex,
    std::vector<bool>& visited, std::function<void(uint32_t)>& func) {
    assert(0 <= vertex && vertex < graph.VerticesCount());
    std::queue<uint32_t> q;
    q.push(vertex);
    visited[vertex] = true;

    while (!q.empty()) {
        uint32_t currentVertex = q.front();
        q.pop();

        func(currentVertex);

        for (const auto& nextVertex : graph.GetNextVertices(currentVertex)) {
            if (!visited[nextVertex]) {
                visited[nextVertex] = true;
                q.push(nextVertex);
            }
        }
    }
}

void BFS(const IGraph& graph, std::function<void(uint32_t)> func) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i])
            bfsInternal(graph, i, visited, func);
    }
}