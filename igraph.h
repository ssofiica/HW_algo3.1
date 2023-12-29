#pragma once
#include <vector>

// Абстрактный класс
struct IGraph {
    virtual ~IGraph() = default;

    virtual void AddEdge(const int64_t& from, const int64_t& to) = 0;

    virtual uint32_t VerticesCount() const = 0;

    virtual std::vector<uint32_t> GetNextVertices(const int64_t& vertex) const = 0;

    virtual std::vector<uint32_t> GetPrevVertices(const int64_t& vertex) const = 0;
};