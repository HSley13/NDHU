#include <algorithm>
#include <climits>
#include <iostream>
#include <list>
#include <vector>

class Graph {
  public:
    Graph();
    void InsertVertex(int v);
    void InsertEdge(int u, int v, int weight = 1);
    bool IsEmpty();
    std::list<std::vector<int>> Adjacent_List(int u);
    void PrintAdjacentMatrix();
    void PrintAdjacentList();
    void PrimMST();

  private:
    int NumberVertices;
    int NumberEdges;
    std::list<int> vertices;
    std::vector<std::vector<int>> adjacent_matrix;
    std::vector<std::list<std::vector<int>>> adjacent_list;

    struct Edge {
        int u;
        int v;
        int weight;
        bool operator<(const Edge &other) const {
            return weight < other.weight;
        }
    };

    std::vector<Edge> GetEdges();
    int Find(std::vector<int> &parent, int vertex);
    void Union(std::vector<int> &parent, std::vector<int> &rank, int u, int v);
};

Graph::Graph() {
    NumberVertices = NumberEdges = 0;
}

bool Graph::IsEmpty() {
    return (vertices.size() == 0);
}

std::list<std::vector<int>> Graph::Adjacent_List(int i) {
    return adjacent_list[i];
}

void Graph::InsertVertex(int v) {
    if (std::find(vertices.begin(), vertices.end(), v) == vertices.end()) {
        vertices.push_back(v);
        NumberVertices++;
    }
}

void Graph::InsertEdge(int u, int v, int weight) {
    if (adjacent_matrix.size() <= u || adjacent_matrix.size() <= v) {
        int max_size = std::max(u, v) + 1;
        adjacent_matrix.resize(max_size, std::vector<int>(max_size, 0));
    }

    if (adjacent_list.size() <= u || adjacent_list.size() <= v) {
        int max_size = std::max(u, v) + 1;
        adjacent_list.resize(max_size);
    }

    adjacent_matrix[u][v] = weight;
    adjacent_matrix[v][u] = weight;
    adjacent_list[u].push_back({v, weight});
    adjacent_list[v].push_back({u, weight});
}

std::vector<Graph::Edge> Graph::GetEdges() {
    std::vector<Edge> edges;
    for (int i{0}; i < NumberVertices; i++) {
        for (int j{i + 1}; j < NumberVertices; j++) {
            if (adjacent_matrix[i][j] != 0) {
                edges.push_back({i, j, adjacent_matrix[i][j]});
            }
        }
    }
    return edges;
}

void Graph::PrimMST() {
    std::vector<int> key(NumberVertices, INT_MAX);
    std::vector<int> parent(NumberVertices, -1);
    std::vector<bool> inMST(NumberVertices, false);

    key[0] = 0;

    for (int count{0}; count < NumberVertices - 1; count++) {
        int u{-1};
        int min_key{INT_MAX};

        for (int v{0}; v < NumberVertices; v++) {
            if (!inMST[v] && key[v] < min_key) {
                min_key = key[v];
                u = v;
            }
        }

        inMST[u] = true;

        for (std::vector<int> &neighbor : adjacent_list[u]) {
            int v{neighbor[0]};
            int weight{neighbor[1]};

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    std::cout << "Minimum Spanning Tree (Prim's Algorithm):" << std::endl;
    for (int i{1}; i < NumberVertices; i++) {
        std::cout << parent[i] << " - " << i << " : " << key[i] << std::endl;
    }
}

void Graph::PrintAdjacentMatrix() {
    for (int i{0}; i < vertices.size(); i++) {
        for (int j{0}; j < vertices.size(); j++) {
            if (adjacent_matrix[i][j])
                std::cout << "(" << i << ", " << j << ", " << adjacent_matrix[i][j] << ")" << std::endl;
        }
    }
}

void Graph::PrintAdjacentList() {
    for (int i{0}; i < vertices.size(); i++) {
        for (std::vector<int> &it : adjacent_list[i]) {
            std::cout << "(" << i << ", " << it[0] << ", " << it[1] << ")" << std::endl;
        }
    }
}

int main(void) {
    int u, v, weight;
    int N, M;

    std::cin >> N >> M;
    Graph g;

    for (int i{0}; i < M; i++) {
        std::cin >> u >> v >> weight;
        g.InsertVertex(u);
        g.InsertVertex(v);
        g.InsertEdge(u, v, weight);
    }

    g.PrimMST();
}
