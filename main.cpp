// Дан базовый интерфейс для представления ориентированного графа.
// Необходимо написать несколько реализаций интерфейса:
// ListGraph, хранящий граф в виде массива списков смежности,
// MatrixGraph, хранящий граф в виде матрицы смежности,
// SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
// ArcGraph, хранящий граф в виде одного массива пар {from, to}.
// Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен скопировать переданный граф в создаваемый объект.
// Для каждого класса создавайте отдельные h и cpp файлы.
// Число вершин графа задается в конструкторе каждой реализации.

// Нужно продемонстрировать работу конструктора копирования, проинициализировав
// графы разных классов друг от друга. Далее, показать, что вершины и ребра
// успешно скопированы: число вершин осталось прежним, произвести BFS и DFS.
// ArcGraph arcGraph(listGraph);
// MatrixGraph matrixGraph(arcGraph);
// SetGraph setGraph(matrixGraph);

#include <iostream>
#include <utility>
#include <deque>
#include <functional>
#include "igraph.h"
#include "list_graph.h"
#include "arc_graph.h"
#include "matrix_graph.h"
#include "set_graph.h"

void BFS(const IGraph& graph, std::function<void(uint32_t)> func);
void DFS(const IGraph& graph, std::function<void(uint32_t)> func);

std::deque<uint32_t> TopologicalSort(const IGraph& graph);

int main(int argc, const char* argv[]) {
    std::cout << "ListGraph" << std::endl;
    ListGraph listGraph(8);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 2);
    listGraph.AddEdge(0, 3);
    listGraph.AddEdge(0, 6);
    listGraph.AddEdge(0, 7);
    listGraph.AddEdge(1, 4);
    listGraph.AddEdge(2, 3);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(4, 6);
    listGraph.AddEdge(4, 5);
    listGraph.AddEdge(5, 6);
    listGraph.AddEdge(6, 7);

    std::cout << "BFS: ";
    BFS(listGraph, [](const int64_t& vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "DFS: ";
    DFS(listGraph, [](const int64_t& vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "Sort:";
    for (const auto& vertex : TopologicalSort(listGraph)) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl << std::endl;

    // ArcGraph
    ArcGraph arcGraph(listGraph);
    std::cout << "ArcGraph" << std::endl;

    std::cout << "BFS: ";
    BFS(arcGraph, [](const int64_t& vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "DFS: ";
    DFS(arcGraph, [](const int64_t& vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "Sort:";
    for (const auto& vertex : TopologicalSort(arcGraph)) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl << std::endl;

    // MatrixGraph
    MatrixGraph matrixGraph(arcGraph);
    std::cout << "MatrixGraph" << std::endl;

    std::cout << "BFS: ";
    BFS(matrixGraph, [](const int64_t& vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "DFS: ";
    DFS(matrixGraph, [](const int64_t& vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "Sort:";
    for (const auto& vertex : TopologicalSort(matrixGraph)) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl << std::endl;

    // SetGraph
    SetGraph setGraph(matrixGraph);
    std::cout << "SetGraph" << std::endl;

    std::cout << "BFS: ";
    BFS(setGraph, [](const int64_t& vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "DFS: ";
    DFS(setGraph, [](const int64_t& vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "Sort:";
    for (const auto& vertex : TopologicalSort(setGraph)) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl << std::endl;

    // ListGraph
    ListGraph lGraph(setGraph);
    std::cout << "ListGraph" << std::endl;

    std::cout << "BFS: ";
    BFS(lGraph, [](const int64_t& vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "DFS: ";
    DFS(lGraph, [](const int64_t& vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "Sort:";
    for (const auto& vertex : TopologicalSort(lGraph)) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl << std::endl;

    return 0;
}