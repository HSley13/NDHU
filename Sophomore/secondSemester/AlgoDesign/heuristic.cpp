#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

struct Node {
    int x, y; // Coordinates
    bool walkable;
    double g{std::numeric_limits<double>::infinity()}; // Cost from start
    double f{std::numeric_limits<double>::infinity()}; // Total cost (g + h)
    Node *parent{nullptr};

    Node(int x = 0, int y = 0, bool walkable = true) : x{x}, y{y}, walkable{walkable} {}
};

struct CompareNode {
    bool operator()(const Node *a, const Node *b) {
        return a->f > b->f;
    }
};

double heuristic(const Node &a, const Node &b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

std::vector<Node *> aStar(Node *start, Node *goal, std::vector<std::vector<Node>> &grid) {
    std::priority_queue<Node *, std::vector<Node *>, CompareNode> openSet{};
    std::unordered_map<Node *, bool> closedSet{};

    start->g = 0;
    start->f = heuristic(*start, *goal);
    openSet.push(start);

    while (!openSet.empty()) {
        Node *current = openSet.top();
        openSet.pop();

        if (current == goal) {
            std::vector<Node *> path{};
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        closedSet[current] = true;

        std::vector<std::pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        for (const std::pair<int, int> &dir : directions) {
            int nx = current->x + dir.first;
            int ny = current->y + dir.second;

            if (nx < 0 || nx >= static_cast<int>(grid.size()) ||
                ny < 0 || ny >= static_cast<int>(grid[0].size())) {
                continue;
            }

            Node *neighbor = &grid[nx][ny];

            if (!neighbor->walkable || closedSet.count(neighbor)) {
                continue;
            }

            double tentative_g = current->g + 1;

            if (tentative_g < neighbor->g) {
                neighbor->parent = current;
                neighbor->g = tentative_g;
                neighbor->f = neighbor->g + heuristic(*neighbor, *goal);
                openSet.push(neighbor);
            }
        }
    }

    return {};
}

int main(void) {
    std::vector<std::vector<Node>> grid(5, std::vector<Node>(5));
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            grid[i][j] = Node{i, j};
        }
    }

    grid[1][1].walkable = false;
    grid[2][2].walkable = false;
    grid[3][1].walkable = false;

    Node *start = &grid[0][0];
    Node *goal = &grid[4][4];

    std::vector<Node *> path = aStar(start, goal, grid);

    std::cout << "Path found (" << path.size() << " steps):\n";
    for (Node *node : path) {
        std::cout << "(" << node->x << "," << node->y << ") ";
    }
    std::cout << "\n";
}
