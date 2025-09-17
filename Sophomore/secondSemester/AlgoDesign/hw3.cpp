#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct Item {
    int weight;
    int value;
};

struct Node {
    int level;
    int profit;
    int weight;
    float bound;

    bool operator<(const Node &other) const {
        return bound < other.bound;
    }
};

float calculate_bound(const Node &u, int capacity, const std::vector<Item> &items) {
    if (u.weight >= capacity) {
        return 0.0f;
    }

    float profit_bound = static_cast<float>(u.profit);
    int total_weight = u.weight;
    int index = u.level + 1;
    int n = static_cast<int>(items.size());

    while (index < n && total_weight + items[index].weight <= capacity) {
        total_weight += items[index].weight;
        profit_bound += items[index].value;
        ++index;
    }

    if (index < n) {
        profit_bound += (capacity - total_weight) *
                        static_cast<float>(items[index].value) / items[index].weight;
    }

    return profit_bound;
}

void DFS_Helper(int i, int profit, int weight, int &max_profit, int &nodes_visited, int capacity, const std::vector<Item> &items) {
    ++nodes_visited;

    if (weight > capacity) return;

    if (profit > max_profit) {
        max_profit = profit;
    }

    if (i == static_cast<int>(items.size())) return;

    float upper_bound = profit;
    int total_weight = weight;
    for (int j = i; j < static_cast<int>(items.size()); ++j) {
        if (total_weight + items[j].weight <= capacity) {
            total_weight += items[j].weight;
            upper_bound += items[j].value;
        } else {
            upper_bound += (capacity - total_weight) *
                           static_cast<float>(items[j].value) / items[j].weight;
            break;
        }
    }

    if (upper_bound < max_profit) return;

    DFS_Helper(i + 1, profit + items[i].value, weight + items[i].weight, max_profit, nodes_visited, capacity, items);
    DFS_Helper(i + 1, profit, weight, max_profit, nodes_visited, capacity, items);
}

void DFS_Knapsack(int capacity, const std::vector<Item> &items) {
    int max_profit = 0;
    int nodes_visited = 0;

    DFS_Helper(0, 0, 0, max_profit, nodes_visited, capacity, items);

    std::cout << "[DFS] Max Profit: " << max_profit
              << ", Nodes Visited: " << nodes_visited << "\n";
}

void BFS_Knapsack(int capacity, const std::vector<Item> &items) {
    int max_profit = 0;
    int nodes_visited = 0;
    int n = static_cast<int>(items.size());
    std::queue<Node> Q;

    Q.push({-1, 0, 0, 0.0f});

    while (!Q.empty()) {
        Node u = Q.front();
        Q.pop();
        ++nodes_visited;

        if (u.level == n - 1) continue;

        Node v;
        v.level = u.level + 1;

        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;
        if (v.weight <= capacity && v.profit > max_profit) {
            max_profit = v.profit;
        }
        Q.push(v);

        v.weight = u.weight;
        v.profit = u.profit;
        Q.push(v);
    }

    std::cout << "[BFS] Max Profit: " << max_profit
              << ", Nodes Visited: " << nodes_visited << "\n";
}

void BestFirst_Knapsack(int capacity, const std::vector<Item> &items) {
    int max_profit = 0;
    int nodes_visited = 0;
    int n = static_cast<int>(items.size());
    std::priority_queue<Node> PQ;

    Node root{-1, 0, 0, 0.0f};
    root.bound = calculate_bound(root, capacity, items);
    PQ.push(root);

    while (!PQ.empty()) {
        Node u = PQ.top();
        PQ.pop();
        ++nodes_visited;

        if (u.bound <= max_profit) continue;

        Node v;
        v.level = u.level + 1;

        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;
        v.bound = calculate_bound(v, capacity, items);
        if (v.weight <= capacity && v.profit > max_profit) {
            max_profit = v.profit;
        }
        if (v.bound > max_profit) {
            PQ.push(v);
        }

        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = calculate_bound(v, capacity, items);
        if (v.bound > max_profit) {
            PQ.push(v);
        }
    }

    std::cout << "[Best-First] Max Profit: " << max_profit
              << ", Nodes Visited: " << nodes_visited << "\n";
}

int main(void) {
    std::vector<Item> items = {
        {12, 4}, {2, 2}, {1, 2}, {1, 1}, {4, 10}};
    int capacity = 15;

    std::sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
        return static_cast<float>(a.value) / a.weight >
               static_cast<float>(b.value) / b.weight;
    });

    DFS_Knapsack(capacity, items);
    BFS_Knapsack(capacity, items);
    BestFirst_Knapsack(capacity, items);
}
