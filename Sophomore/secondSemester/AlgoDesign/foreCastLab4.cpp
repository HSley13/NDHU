#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>

typedef int WeightType;

struct Edge {
    int u, v;
    WeightType w;
    bool operator>(const Edge &other) const { return w > other.w; }
};

struct Graph {
    Graph(int n) : E(n) {}
    std::vector<std::list<Edge>> E;

    void add_edge(int u, int v, WeightType w) {
        E[u].push_back({u, v, w});
        E[v].push_back({v, u, w});
    }

    int n() const { return E.size(); }

    int m() const {
        int res{0};
        for (const std::list<Edge> &list : E)
            res += list.size();
        return res / 2;
    }
};

// Prim's MST Algorithm
Graph primMST(const Graph &G) {
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
    Graph MST(G.n());
    std::vector<bool> visited(G.n(), false);

    // Start with vertex 0
    visited[0] = true;
    for (const Edge &e : G.E[0])
        pq.push(e);

    while (!pq.empty()) {
        Edge e{pq.top()};
        pq.pop();

        if (visited[e.u] && visited[e.v])
            continue;

        int new_vertex{visited[e.u] ? e.v : e.u};
        visited[new_vertex] = true;
        MST.add_edge(e.u, e.v, e.w);

        for (const Edge &edge : G.E[new_vertex]) {
            if (!visited[edge.v])
                pq.push(edge);
        }
    }

    return MST;
}

// Disjoint Set Union for Kruskal's
class DSU {
    std::vector<int> parent;
    std::vector<int> rank;

  public:
    DSU(int n) : parent(n), rank(n, 0) {
        for (int i{0}; i < n; i++)
            parent[i] = i;
    }

    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    bool unite(int u, int v) {
        int root_u{find(u)};
        int root_v{find(v)};

        if (root_u == root_v)
            return false; // Useless edge

        if (rank[root_u] < rank[root_v])
            parent[root_u] = root_v;
        else if (rank[root_u] > rank[root_v])
            parent[root_v] = root_u;
        else {
            parent[root_v] = root_u;
            rank[root_u]++;
        }
        return true; // Safe edge
    }
};

// Kruskal's MST Algorithm
Graph kruskalMST(const Graph &G) {
    Graph MST(G.n());
    DSU dsu(G.n());
    std::vector<Edge> edges;

    // Collect all edges
    for (int u{0}; u < G.n(); u++)
        for (const Edge &e : G.E[u])
            if (e.u < e.v) // Avoid duplicates
                edges.push_back(e);

    // Sort edges by weight
    std::sort(edges.begin(), edges.end(),
              [](const Edge &a, const Edge &b) { return a.w < b.w; });

    // Process edges in order
    for (const Edge &e : edges) {
        if (dsu.unite(e.u, e.v)) { // Only add if not useless
            MST.add_edge(e.u, e.v, e.w);
        }
    }

    return MST;
}

// Prim's for disconnected graphs (Forest)
std::pair<Graph, int> primForest(const Graph &G) {
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
    Graph MST(G.n());
    std::vector<bool> visited(G.n(), false);
    int tree_count{0};

    for (int start{0}; start < G.n(); ++start) {
        if (!visited[start]) {
            tree_count++;
            visited[start] = true;

            for (const Edge &e : G.E[start])
                pq.push(e);

            while (!pq.empty()) {
                Edge e{pq.top()};
                pq.pop();

                if (visited[e.u] && visited[e.v])
                    continue;

                int new_vertex{visited[e.u] ? e.v : e.u};
                visited[new_vertex] = true;
                MST.add_edge(e.u, e.v, e.w);

                for (const Edge &edge : G.E[new_vertex]) {
                    if (!visited[edge.v])
                        pq.push(edge);
                }
            }
        }
    }

    return {MST, tree_count};
}

// Path cost in tree
WeightType pathCost(const Graph &T, int root, int target) {
    std::vector<WeightType> dist(T.n(), -1);
    std::vector<int> parent(T.n(), -1);
    std::stack<int> s;

    dist[root] = 0;
    s.push(root);

    while (!s.empty()) {
        int u{s.top()};
        s.pop();

        for (const Edge &e : T.E[u]) {
            if (e.v != parent[u]) {
                parent[e.v] = u;
                dist[e.v] = dist[u] + e.w;
                if (e.v == target) return dist[target];
                s.push(e.v);
            }
        }
    }

    return -1; // Not reachable
}

// Helper function to print graph
void printGraph(const Graph &G) {
    std::cout << "Graph with " << G.n() << " vertices and " << G.m() << " edges:\n";
    for (int u{0}; u < G.n(); u++) {
        for (const Edge &e : G.E[u]) {
            if (e.u <= e.v)
                std::cout << e.u << " --" << e.w << "-- " << e.v << "\n";
        }
    }
}

// Test cases
void testPrim() {
    std::cout << "\n=== Testing Prim's Algorithm ===\n";
    Graph G(4);
    G.add_edge(0, 1, 10);
    G.add_edge(0, 2, 6);
    G.add_edge(0, 3, 5);
    G.add_edge(1, 3, 15);
    G.add_edge(2, 3, 4);

    Graph MST = primMST(G);
    printGraph(MST);
    std::cout << "Expected MST weight: 19 (0-3-5, 0-1-10, 2-3-4)\n";
}

void testKruskal() {
    std::cout << "\n=== Testing Kruskal's Algorithm ===\n";
    Graph G(4);
    G.add_edge(0, 1, 10);
    G.add_edge(0, 2, 6);
    G.add_edge(0, 3, 5);
    G.add_edge(1, 3, 15);
    G.add_edge(2, 3, 4);

    Graph MST = kruskalMST(G);
    printGraph(MST);
    std::cout << "Expected MST weight: 19 (same as Prim's)\n";
}

void testForest() {
    std::cout << "\n=== Testing Forest Algorithm ===\n";
    Graph G(6); // Disconnected graph
    G.add_edge(0, 1, 4);
    G.add_edge(0, 2, 3);
    G.add_edge(1, 2, 1);
    G.add_edge(3, 4, 2);
    G.add_edge(4, 5, 3);
    G.add_edge(3, 5, 4);

    auto [MST, count] = primForest(G);
    printGraph(MST);
    std::cout << "Number of trees: " << count << "\n";
    std::cout << "Expected MST forest with 2 trees, total weight 11\n";
}

void testPathCost() {
    std::cout << "\n=== Testing Path Cost ===\n";
    Graph T(5); // Tree structure
    T.add_edge(0, 1, 2);
    T.add_edge(0, 2, 3);
    T.add_edge(1, 3, 1);
    T.add_edge(1, 4, 5);

    int cost = pathCost(T, 0, 4);
    std::cout << "Path cost from 0 to 4: " << cost << "\n";
    std::cout << "Expected cost: 7 (0-1-2 + 1-4-5)\n";
}

void testUselessEdge() {
    std::cout << "\n=== Testing Useless Edge Detection ===\n";
    Graph G(4);
    G.add_edge(0, 1, 1); // Safe
    G.add_edge(1, 2, 2); // Safe
    G.add_edge(2, 3, 3); // Safe
    G.add_edge(0, 2, 4); // Useless (0-1-2 already connected)
    G.add_edge(1, 3, 5); // Useless (1-2-3 already connected)

    Graph MST = kruskalMST(G);
    printGraph(MST);
    std::cout << "Expected MST edges: 0-1, 1-2, 2-3\n";
}

int main(void) {
    testPrim();
    testKruskal();
    testForest();
    testPathCost();
    testUselessEdge();

    std::cout << "\n=== A* Algorithm Explanation ===\n";
    std::cout << "A* is an informed search algorithm that uses a heuristic to find\n";
    std::cout << "the shortest path. It's optimal when the heuristic is admissible\n";
    std::cout << "(never overestimates) and consistent (satisfies triangle inequality).\n";
}
