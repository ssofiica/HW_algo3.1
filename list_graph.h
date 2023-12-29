#pragma once

#include <vector>
#include <cassert>

struct ListGraph : public IGraph {
public:
    ListGraph(const uint32_t& size) : adjacencyLists(size) {}

    ListGraph(const IGraph& graph) : adjacencyLists(graph.VerticesCount()) {
        for (int from = 0; from < graph.VerticesCount(); from++) {
            for (const auto& to : graph.GetNextVertices(from)) {
                adjacencyLists[from].push_back(to);
            }
        }
    }

    ~ListGraph() override = default;

    void AddEdge(const int64_t& from, const int64_t& to) override {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        // Для неориентированного графа добавить:
        // adjacencyLists[to].push_back(from);
        adjacencyLists[from].push_back(to);
    }

    uint32_t VerticesCount() const override {
        return adjacencyLists.size();
    }

    std::vector<uint32_t> GetNextVertices(const int64_t& vertex) const override {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }

    std::vector<uint32_t> GetPrevVertices(const int64_t& vertex) const override {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        std::vector<uint32_t> prevVertices;

        for (int from = 0; from < adjacencyLists.size(); from++) {
            for (const auto& to : adjacencyLists[from]) {
                if (to == vertex) {
                    prevVertices.push_back(from);
                    break;
                }
            }
        }
        return prevVertices;
    }

private:
    std::vector<std::vector<uint32_t>> adjacencyLists;
};


