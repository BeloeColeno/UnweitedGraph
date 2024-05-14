#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>

using namespace std;

// ќбъ€вление класса Edge
class Edge {
public:
    int u; // вершина "откуда"
    int v; // вершина "куда"

    Edge(int u, int v) : u(u), v(v) {}

    Edge reversed() const {
        return Edge(v, u);
    }
};

// ќбъ€вление класса Graph
template<typename V, typename E>
class Graph {
protected:
    vector<V> vertices;
    unordered_map<int, vector<E>> edges;

public:
    Graph() {}

    Graph(vector<V> vertices) : vertices(vertices) {
        for (int i = 0; i < vertices.size(); ++i) {
            edges[i] = vector<E>();
        }
    }

    int getVertexCount() const {
        return vertices.size();
    }

    int getEdgeCount() const {
        int count = 0;
        for (const auto& pair : edges) {
            count += pair.second.size();
        }
        return count;
    }

    int addVertex(V vertex) {
        vertices.push_back(vertex);
        edges[vertices.size() - 1] = vector<E>();
        return vertices.size() - 1;
    }

    V vertexAt(int index) const {
        return vertices[index];
    }

    int indexOf(V vertex) const {
        auto it = find(vertices.begin(), vertices.end(), vertex);
        if (it != vertices.end()) {
            return distance(vertices.begin(), it);
        }
        return -1;
    }

    vector<V> neighborsOf(int index) const {
        vector<V> neighbors;
        auto it = edges.find(index);
        if (it != edges.end()) {
            for (const auto& edge : it->second) {
                neighbors.push_back(vertexAt(edge.v));
            }
        }
        return neighbors;
    }

    vector<V> neighborsOf(V vertex) const {
        return neighborsOf(indexOf(vertex));
    }

    vector<E> edgesOf(int index) const {
        auto it = edges.find(index);
        if (it != edges.end()) {
            return it->second;
        }
        return vector<E>();
    }

    vector<E> edgesOf(V vertex) const {
        return edgesOf(indexOf(vertex));
    }

    string toString() const {
        stringstream ss;
        for (int i = 0; i < vertices.size(); ++i) {
            ss << vertexAt(i) << " -> [";
            vector<V> neighbors = neighborsOf(i);
            for (int j = 0; j < neighbors.size(); ++j) {
                ss << neighbors[j];
                if (j != neighbors.size() - 1) {
                    ss << ", ";
                }
            }
            ss << "]" << endl;
        }
        return ss.str();
    }
};

// ќбъ€вление класса UnweightedGraph
template<typename V>
class UnweightedGraph : public Graph<V, Edge> {
public:
    UnweightedGraph(vector<V> vertices) : Graph<V, Edge>(vertices) {}

    void addEdge(Edge edge) {
        this->edges[edge.u].push_back(edge);
        this->edges[edge.v].push_back(edge.reversed());
    }

    void addEdge(int u, int v) {
        addEdge(Edge(u, v));
    }

    void addEdge(V first, V second) {
        addEdge(Edge(this->indexOf(first), this->indexOf(second)));
    }
};

int main() {
    UnweightedGraph<string> cityGraph({ "Seattle", "San Francisco", "Los Angeles", "Riverside",
                                        "Phoenix", "Chicago", "Boston", "New York", "Atlanta",
                                        "Miami", "Dallas", "Houston", "Detroit", "Philadelphia",
                                        "Washington" });

    cityGraph.addEdge("Seattle", "Chicago");
    cityGraph.addEdge("Seattle", "San Francisco");
    cityGraph.addEdge("San Francisco", "Riverside");
    cityGraph.addEdge("San Francisco", "Los Angeles");
    cityGraph.addEdge("Los Angeles", "Riverside");
    cityGraph.addEdge("Los Angeles", "Phoenix");
    cityGraph.addEdge("Riverside", "Phoenix");
    cityGraph.addEdge("Riverside", "Chicago");
    cityGraph.addEdge("Phoenix", "Dallas");
    cityGraph.addEdge("Phoenix", "Houston");
    cityGraph.addEdge("Dallas", "Chicago");
    cityGraph.addEdge("Dallas", "Atlanta");
    cityGraph.addEdge("Dallas", "Houston");
    cityGraph.addEdge("Houston", "Atlanta");
    cityGraph.addEdge("Houston", "Miami");
    cityGraph.addEdge("Atlanta", "Chicago");
    cityGraph.addEdge("Atlanta", "Washington");
    cityGraph.addEdge("Atlanta", "Miami");
    cityGraph.addEdge("Miami", "Washington");
    cityGraph.addEdge("Chicago", "Detroit");
    cityGraph.addEdge("Detroit", "Boston");
    cityGraph.addEdge("Detroit", "Washington");
    cityGraph.addEdge("Detroit", "New York");
    cityGraph.addEdge("Boston", "New York");
    cityGraph.addEdge("New York", "Philadelphia");
    cityGraph.addEdge("Philadelphia", "Washington");

    cout << cityGraph.toString() << endl;

    return 0;
}