#ifndef HEAP_INCLUDE_GRAPH_H
#define HEAP_INCLUDE_GRAPH_H

#define EPSILON 1e-10
#define INF 1e9

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

#include "FibonacciHeap.h"

struct Node {
    double distance;
    int vertex;
};

struct NodeComparator {
    bool operator()(const Node& n1, const Node& n2) const {
        return n1.distance < n2.distance;
    }
};

enum class Color { White, Black, Grey };

template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Vertex from;
        Vertex to;
        Distance distance;
    };

private:
    std::vector<Vertex> _vertices;
    std::unordered_map<Vertex, std::vector<Edge>> _edges;

    void dfs_helper(const Vertex& start_vertex, std::unordered_map<Vertex, Color>& colors,
        std::function<void(const Vertex&)> action, std::vector<Vertex>& result) const {
        colors[start_vertex] = Color::Grey;
        action(start_vertex);
        result.push_back(start_vertex);
        for (const Edge& edge : _edges.at(start_vertex))
            if (colors[edge.to] == Color::White)
                dfs_helper(edge.to, colors, action, result);
        colors[start_vertex] = Color::Black;
    }

public:
    bool has_vertex(const Vertex& v) const {
        return std::find(_vertices.begin(), _vertices.end(), v) != _vertices.end();
    }

    bool add_vertex(const Vertex& v) {
        if (has_vertex(v))
            return false;
        _vertices.push_back(v);
        _edges[v] = {};
        return true;
    }

    bool remove_vertex(const Vertex& v) {
        auto it = std::find(_vertices.begin(), _vertices.end(), v);
        if (it == _vertices.end())
            return false;
        _vertices.erase(it);
        _edges.erase(v);
        for (auto& vertex : _vertices) {
            auto& edges = _edges.at(vertex);
            edges.erase(std::remove_if(edges.begin(), edges.end(), [v](const Edge& edge) {return edge.to == v; }), edges.end());
        }
        return true;
    }

    const std::vector<Vertex>& vertices() const {
        return _vertices;
    }

    bool add_edge(const Vertex& from, const Vertex& to, const Distance& distance) {
        if (has_edge({ from, to, distance }))
            return false;
        _edges[from].push_back({ from, to, distance });
        return true;
    }

    bool remove_edge(const Vertex& from, const Vertex& to) {
        if (!has_edge(from, to))
            return false;
        auto& edges = _edges.at(from);
        edges.erase(std::remove_if(edges.begin(), edges.end(), [to](const Edge& edge) {return edge.to == to; }), edges.end());
        return true;
    }

    bool remove_edge(const Edge& e) {
        if (!has_edge({ e.from, e.to, e.distance }))
            return false;
        auto& edges = _edges.at(e.from);
        edges.erase(std::remove_if(edges.begin(), edges.end(), [e](const Edge& edge) {return edge.to == e.to && abs(edge.distance - e.distance) < EPSILON; }), edges.end());
        return true;
    }

    bool has_edge(const Vertex& from, const Vertex& to) const {
        if (std::find(_vertices.begin(), _vertices.end(), from) == _vertices.end())
            return false;
        if (std::find(_vertices.begin(), _vertices.end(), to) == _vertices.end())
            return false;
        for (const Edge& edge : _edges.at(from))
            if (edge.to == to)
                return true;
        return false;
    }

    bool has_edge(const Edge& e) const {
        if (std::find(_vertices.begin(), _vertices.end(), e.from) == _vertices.end())
            return false;
        if (std::find(_vertices.begin(), _vertices.end(), e.to) == _vertices.end())
            return false;
        for (const Edge& edge : _edges.at(e.from))
            if (edge.to == e.to && abs(edge.distance - e.distance) < EPSILON)
                return true;
        return false;
    }

    const std::vector<Edge>& edges(const Vertex& vertex) {
        if (!has_vertex(vertex))
            throw std::invalid_argument("vertex is not found");
        return _edges[vertex];
    }

    size_t order() const {
        return _vertices.size();
    }

    size_t degree(const Vertex& v) const {
        if (!has_vertex(v))
            throw std::invalid_argument("vertex is not found");
        size_t deg_out = _edges.at(v).size();
        size_t deg_in = 0;
        for (auto& vertex : _vertices) {
            for (auto& edge : _edges.at(vertex)) {
                if (edge.to == v) {
                    ++deg_in;
                }
            }
        }
        return deg_in + deg_out;
    }

    void print() const {
        for (const auto& v : _vertices) {
            std::cout << v << " : ";
            for (const auto& e : _edges.at(v)) {
                std::cout << "(" << e.to << ", " << e.distance << "),  ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {
        if (!has_vertex(from) || !has_vertex(to))
            return {};

        for (const Vertex& vertex : _vertices) {
            for (const Edge& edge : _edges.at(vertex)) {
                if (edge.distance < 0) {
                    throw std::runtime_error("The graph contains negative weights");
                }
                if (edge.to == vertex) {
                    throw std::runtime_error("There are cycles in the graph");
                }
            }
        }

        std::unordered_map<Vertex, Distance> distances;
        std::unordered_map<Vertex, Vertex> prev;

        for (const auto& vertex : _vertices)
            distances[vertex] = INF;
        distances[from] = 0;

        std::priority_queue<std::pair<Distance, Vertex>, std::vector<std::pair<Distance, Vertex>>, std::greater<std::pair<Distance, Vertex>>> pq;
        pq.push({ 0, from });

        while (!pq.empty()) {
            Vertex u = pq.top().second;
            pq.pop();

            if (u == to) {
                std::vector<Edge> path;
                Vertex current = to;
                while (current != from) {
                    for (const auto& edge : _edges.at(prev[current])) {
                        if (edge.to == current) {
                            path.push_back(edge);
                            break;
                        }
                    }
                    current = prev[current];
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            if (distances[u] < INF) {
                for (const auto& edge : _edges.at(u)) {
                    Distance alt = distances[u] + edge.distance;
                    if (alt < distances[edge.to]) {
                        distances[edge.to] = alt;
                        prev[edge.to] = u;
                        pq.push({ alt, edge.to });
                    }
                }
            }
        }
        return {};
    }

    std::vector<Edge> shortest_path_with_heap(const Vertex& from, const Vertex& to) const {
        if (!has_vertex(from) || !has_vertex(to))
            return {};

        for (const Vertex& vertex : _vertices) {
            for (const Edge& edge : _edges.at(vertex)) {
                if (edge.distance < 0) {
                    throw std::runtime_error("The graph contains negative weights");
                }
                if (edge.to == vertex) {
                    throw std::runtime_error("There are cycles in the graph");
                }
            }
        }

        std::unordered_map<Vertex, Distance> distances;
        std::unordered_map<Vertex, Vertex> prev;

        for (const auto& vertex : _vertices)
            distances[vertex] = INF;
        distances[from] = 0;

        FibonacciHeap<Node, NodeComparator> pq;
        pq.insert(Node{ 0, from });

        while (!pq.isEmpty()) {
            Vertex u = (*pq.extractMin()).vertex;

            if (u == to) {
                std::vector<Edge> path;
                Vertex current = to;
                while (current != from) {
                    for (const auto& edge : _edges.at(prev[current])) {
                        if (edge.to == current) {
                            path.push_back(edge);
                            break;
                        }
                    }
                    current = prev[current];
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            if (distances[u] < INF) {
                for (const auto& edge : _edges.at(u)) {
                    Distance alt = distances[u] + edge.distance;
                    if (alt < distances[edge.to]) {
                        distances[edge.to] = alt;
                        prev[edge.to] = u;
                        pq.insert(Node{ alt, edge.to });
                    }
                }
            }
        }
        return {};
    }

    void dfs(const Vertex& start_vertex, std::function<void(const Vertex&)> action) const {
        std::unordered_map<Vertex, Color> colors;
        std::vector<Vertex> result;
        for (const Vertex& vertex : _vertices)
            colors[vertex] = Color::White;
        dfs_helper(start_vertex, colors, action, result);
    }
};

#endif