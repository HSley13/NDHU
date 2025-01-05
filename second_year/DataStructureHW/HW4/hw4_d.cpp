#include <climits>
#include <iostream>
#include <list>
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
    void DijkstraShortestPath(int start_vertex);

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
            adjacent_matrix.push_back(std::vector<int>(vertexs.size(), INT_MAX));
    }

    if (adjacent_list.size() == 0) {
        for (int i{0}; i < vertexs.size(); i++)
            adjacent_list.push_back(std::list<std::vector<int>>());
    }

    adjacent_matrix[u][v] = weight;
    adjacent_list[u].push_back({v, weight});
}

void Graph::DijkstraShortestPath(int start_vertex) {
    std::vector<int> dist(NumberVecterxs, INT_MAX);
    std::vector<int> parent(NumberVecterxs, -1);
    std::vector<bool> s(NumberVecterxs, false);

    dist[start_vertex] = 0;

    for (int i{0}; i < NumberVecterxs - 1; i++) {
        int u{-1};
        int minDist = INT_MAX;

        for (int v{0}; v < NumberVecterxs; v++) {
            if (!s[v] && dist[v] < minDist) {
                minDist = dist[v];
                u = v;
            }
        }

        if (u == -1)
            break;

        s[u] = true;

        for (std::vector<int> &neighbor : adjacent_list[u]) {
            int v{neighbor[0]};
            int weight{neighbor[1]};

            if (!s[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    for (int i{0}; i < NumberVecterxs; i++) {
        if (i == start_vertex)
            continue;

        if (dist[i] == INT_MAX) {
            std::cout << "No path from " << start_vertex << " to " << i << "\n";
            continue;
        }

        std::cout << "Path from " << start_vertex << " to " << i << ": ";
        std::stack<int> path;
        int current{i};

        while (current != -1) {
            path.push(current);
            current = parent[current];
        }

        while (!path.empty()) {
            std::cout << path.top();
            path.pop();

            if (!path.empty())
                std::cout << " ";
        }

        std::cout << " (Cost: " << dist[i] << ")\n";
    }
}

int main(void) {
    int u, v, weight;
    int N;
    int M;

    Graph g;
    std::cin >> N >> M;

    for (int i{0}; i < N; i++) {
        std::cin >> u;
        g.InsertVertex(u);
    }

    for (int j{0}; j < M; j++) {
        std::cin >> u >> v >> weight;
        g.InsertEdge(u, v, weight);
    }

    int start_vertex{0};
    std::cout << "Shortest paths from vertex " << start_vertex << ":\n";
    g.DijkstraShortestPath(start_vertex);
}
