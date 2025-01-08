#include <algorithm>
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
    void KruskalMST();

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

int Graph::Find(std::vector<int> &parent, int vertex) {
    if (parent[vertex] != vertex) {
        parent[vertex] = Find(parent, parent[vertex]);
    }
    return parent[vertex];
}

void Graph::Union(std::vector<int> &parent, std::vector<int> &rank, int u, int v) {
    int root_u{Find(parent, u)};
    int root_v{Find(parent, v)};
    if (rank[root_u] < rank[root_v]) {
        parent[root_u] = root_v;
    } else if (rank[root_u] > rank[root_v]) {
        parent[root_v] = root_u;
    } else {
        parent[root_v] = root_u;
        rank[root_u]++;
    }
}

void Graph::KruskalMST() {
    std::vector<Edge> edges{GetEdges()};
    std::sort(edges.begin(), edges.end());

    std::vector<int> parent(NumberVertices);
    std::vector<int> rank(NumberVertices, 0);

    for (int i{0}; i < NumberVertices; i++) {
        parent[i] = i;
    }

    std::vector<Edge> mst;
    for (const Edge &edge : edges) {
        if (Find(parent, edge.u) != Find(parent, edge.v)) {
            mst.push_back(edge);
            Union(parent, rank, edge.u, edge.v);
        }
    }

    std::cout << "Minimum Spanning Tree (Kruskal's Algorithm):" << std::endl;
    for (const Edge &edge : mst) {
        std::cout << edge.u << " - " << edge.v << " : " << edge.weight << std::endl;
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

    g.KruskalMST();
}
