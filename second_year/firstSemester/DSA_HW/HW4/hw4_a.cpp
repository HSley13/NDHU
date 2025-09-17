#include <iostream>
#include <list>
#include <queue>
#include <stack>
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
    void BFS(int start_vertex);
    void DFS(int start_vertex);

  private:
    int NumberVecterxs;
    int NumberEdges;
    std::list<int> vertexs;
    std::vector<std::vector<int>> adjacent_matrix;
    std::vector<std::list<std::vector<int>>> adjacent_list;
};

Graph::Graph() {
    NumberVecterxs = NumberEdges = 0;
}

bool Graph::IsEmpty() {
    return (vertexs.size() == 0);
}

std::list<std::vector<int>> Graph::Adjacent_List(int i) {
    return adjacent_list[i];
}

void Graph::InsertVertex(int v) {
    vertexs.push_back(v);
    NumberVecterxs++;
}

void Graph::InsertEdge(int u, int v, int weight) {
    if (adjacent_matrix.size() == 0) {
        for (int i{0}; i < vertexs.size(); i++)
            adjacent_matrix.push_back(std::vector<int>(vertexs.size()));
    }

    if (adjacent_list.size() == 0) {
        for (int i{0}; i < vertexs.size(); i++)
            adjacent_list.push_back(std::list<std::vector<int>>());
    }

    adjacent_matrix[u][v] = weight;
    adjacent_list[u].push_back({v, weight});
}

void Graph::PrintAdjacentMatrix() {
    for (int i{0}; i < vertexs.size(); i++) {
        for (int j{0}; j < vertexs.size(); j++) {
            if (adjacent_matrix[i][j])
                std::cout << "(" << i << ", " << j << ", " << adjacent_matrix[i][j] << ")" << std::endl;
        }
    }
}

void Graph::PrintAdjacentList() {
    for (int i{0}; i < vertexs.size(); i++) {
        for (std::vector<int> &it : adjacent_list[i]) {
            std::cout << "(" << i << ", " << it[0] << ", " << it[1] << ")" << std::endl;
        }
    }
}

void Graph::BFS(int start_vertex) {
    std::vector<bool> visited(NumberVecterxs, false);
    std::queue<int> q;

    visited[start_vertex] = true;
    q.push(start_vertex);

    while (!q.empty()) {
        int v = q.front();
        std::cout << v << std::endl;
        q.pop();

        for (std::vector<int> &it : adjacent_list[v]) {
            if (!visited[it[0]]) {
                visited[it[0]] = true;
                q.push(it[0]);
            }
        }
    }
}

void Graph::DFS(int start_vertex) {
    std::vector<bool> visited(NumberVecterxs, false);
    std::stack<int> s;

    s.push(start_vertex);

    while (!s.empty()) {
        int v = s.top();
        s.pop();

        if (!visited[v]) {
            visited[v] = true;
            std::cout << v << std::endl;
        }

        std::list<std::vector<int>> &adj = adjacent_list[v];
        std::vector<std::vector<int>> reversed_adj{adj.rbegin(), adj.rend()};

        for (std::vector<int> &neighbor : reversed_adj) {
            if (!visited[neighbor[0]]) {
                s.push(neighbor[0]);
            }
        }
    }
}

int main(void) {
    int u, v;
    int weight;
    int N;
    int M;

    Graph g;
    std::cin >> N >> M;

    for (int i{0}; i < N; i++) {
        std::cin >> u;
        g.InsertVertex(u);
    }

    for (int j{0}; j < M; j++) {
        std::cin >> u >> v;
        g.InsertEdge(u, v);
    }

    std::cout << "BFS traversal:" << std::endl;
    g.BFS(0);

    std::cout << "DFS traversal:" << std::endl;
    g.DFS(0);
}
