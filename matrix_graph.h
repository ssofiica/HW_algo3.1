#pragma once

#include <vector>
#include <cassert>


class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(const uint32_t& size) : matrix(size, std::vector<bool>(size, false)) {}

    MatrixGraph(const IGraph& graph) :
        matrix(graph.VerticesCount(), std::vector<bool>(graph.VerticesCount(), false)) {
        for (int from = 0; from < graph.VerticesCount(); ++from) {
            for (const auto& to : graph.GetNextVertices(from)) {
                matrix[from][to] = true;
            }
        }
    }

    ~MatrixGraph() override = default;

    void AddEdge(const int64_t& from, const int64_t& to) override {
        assert(0 <= from && from < matrix.size());
        assert(0 <= to && to < matrix.size());
        matrix[from][to] = true;
    }

    uint32_t VerticesCount() const override {
        return static_cast<uint32_t>(matrix.size());
    }

    std::vector<uint32_t> GetNextVertices(const int64_t& vertex) const override {
        assert(0 <= vertex && vertex < matrix.size());
        std::vector<uint32_t> nextVertices;
        std::vector<bool> row(matrix[vertex]);
        for (int i = 0; i < matrix.size(); ++i) {
            if (row[i]) nextVertices.push_back(i);
        }
        return nextVertices;
    }

    std::vector<uint32_t> GetPrevVertices(const int64_t& vertex) const override {
        assert(0 <= vertex && vertex < matrix.size());
        std::vector<uint32_t> prevVertices;
        for (int i = 0; i < matrix.size(); ++i) {
            if (matrix[i][vertex]) prevVertices.push_back(i);
        }
        return prevVertices;
    }

private:
    std::vector<std::vector<bool>> matrix;
};