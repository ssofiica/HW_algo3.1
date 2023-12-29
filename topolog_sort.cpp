#include "igraph.h"
#include <deque>
#include <vector>

void topologicalSortInternal(const IGraph& graph, const int64_t& vertex, std::vector<bool>& visited, std::deque<uint32_t>& sorted) {
    visited[vertex] = true;

    for (const auto& nextVertex : graph.GetNextVertices(vertex)) {
        if (!visited[nextVertex])
            topologicalSortInternal(graph, nextVertex, visited, sorted);
    }
    sorted.push_front(vertex);
}

std::deque<uint32_t> TopologicalSort(const IGraph& graph) {
    std::deque<uint32_t> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i])
            topologicalSortInternal(graph, i, visited, sorted);
    }
    return sorted;
}