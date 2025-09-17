#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <unordered_map>

template <class T>
class Node {
  public:
    Node() : data(std::make_shared<T>()) {}

    Node(T d) : data(std::make_shared<T>(d)) {}

    Node &operator=(T d) {
        *data = d;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const Node &n) {
        out << *(n.data);
        return out;
    }

    void setData(T d) {
        *data = d;
    }

    T &getData() const {
        return *data;
    }

  protected:
    std::shared_ptr<T> data;
};

template <class T>
class ListNode : public Node<T> {
  public:
    ListNode() : Node<T>(), prev(nullptr), next(nullptr) {}

    ListNode(T d) : Node<T>(d), prev(nullptr), next(nullptr) {}

    std::shared_ptr<ListNode> getNext() const {
        return next;
    }

    std::shared_ptr<ListNode> getPrev() const {
        return prev;
    }

    void setNext(std::shared_ptr<ListNode> n) {
        next = n;
    }

    void setPrev(std::shared_ptr<ListNode> p) {
        prev = p;
    }

  private:
    std::shared_ptr<ListNode> prev, next;
};

template <class T>
class LinkList {
  public:
    void addFromHead(T d) {
        std::shared_ptr<ListNode<T>> node{std::make_shared<ListNode<T>>(d)};
        if (head) {
            head->setPrev(node);
        }

        node->setNext(head);
        head = node;
        if (!tail) {
            tail = node;
        }
    }

    std::shared_ptr<ListNode<T>> getHead() const {
        return head;
    }

  private:
    std::shared_ptr<ListNode<T>> head, tail;
};

template <class T>
class GraphNode : public Node<T> {
  public:
    GraphNode(T d) : Node<T>(d), list(std::make_shared<LinkList<std::shared_ptr<GraphNode<T>>>>()) {}

    void addLink(std::shared_ptr<GraphNode<T>> node) {
        list->addFromHead(node);
    }

    std::shared_ptr<LinkList<std::shared_ptr<GraphNode<T>>>> getLinks() const {
        return list;
    }

  private:
    std::shared_ptr<LinkList<std::shared_ptr<GraphNode<T>>>> list;
};

template <class T>
class Graph {
  public:
    Graph() : count(0) {}

    std::shared_ptr<GraphNode<T>> addVertex(T d) {
        std::shared_ptr<GraphNode<T>> node{std::make_shared<GraphNode<T>>(d)};
        vertex[d] = node;
        count++;
        return node;
    }

    void addLink(T node1, T node2) {
        vertex[node1]->addLink(vertex[node2]);
        vertex[node2]->addLink(vertex[node1]);
    }

    bool isForest() {
        std::unordered_map<T, bool> visited;
        for (const std::pair<T, std::shared_ptr<GraphNode<T>>> &pair : vertex) {
            visited[pair.first] = false;
        }

        for (const std::pair<T, std::shared_ptr<GraphNode<T>>> &pair : vertex) {
            if (!visited[pair.first] && hasCycle(pair.second, nullptr, visited)) {
                return false;
            }
        }
        return true;
    }

  private:
    std::unordered_map<T, std::shared_ptr<GraphNode<T>>> vertex;
    int count;

    bool hasCycle(std::shared_ptr<GraphNode<T>> node, std::shared_ptr<GraphNode<T>> parent, std::unordered_map<T, bool> &visited) {
        visited[node->getData()] = true;

        std::shared_ptr<ListNode<std::shared_ptr<GraphNode<T>>>> current{node->getLinks()->getHead()};
        while (current) {
            std::shared_ptr<GraphNode<T>> neighbor{current->getData()};

            if (!visited[neighbor->getData()] && hasCycle(neighbor, node, visited)) {
                return true;
            } else if (neighbor != parent) {
                return true;
            }

            current = current->getNext();
        }
        return false;
    }
};

void runTest(const std::vector<std::pair<char, char>> &edges, int vertexCount, const std::string &testName) {
    std::cout << "Running Test: " << testName << std::endl;

    std::shared_ptr<Graph<char>> g{std::make_shared<Graph<char>>()};

    for (int i{0}; i < vertexCount; i++) {
        g->addVertex(i + 'A');
    }

    for (const std::pair<char, char> &edge : edges) {
        g->addLink(edge.first, edge.second);
    }

    bool result{g->isForest()};

    std::cout << "Graph Vertices: ";
    for (int i{0}; i < vertexCount; i++) {
        std::cout << static_cast<char>(i + 'A') << " ";
    }
    std::cout << std::endl;

    std::cout << "Graph Edges: ";
    for (const std::pair<char, char> &edge : edges) {
        std::cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    std::cout << std::endl;

    std::cout << "Is Forest: " << (result ? "YES" : "NO") << std::endl
              << std::endl;
}

// My main function to run the tests
int main(void) {
    // Test 1: Simple Tree (A - B, B - C)
    runTest({{'A', 'B'}, {'B', 'C'}}, 3, "Simple Tree");

    // Test 2: Graph with a cycle (A - B, B - C, C - A)
    runTest({{'A', 'B'}, {'B', 'C'}, {'C', 'A'}}, 3, "Graph with a Cycle");

    // Test 3: Disconnected Trees (A - B, D - E)
    runTest({{'A', 'B'}, {'D', 'E'}}, 5, "Disconnected Trees");

    // Test 4: Single Node Graph (A)
    runTest({}, 1, "Single Node Graph");

    // Test 5: Graph with Multiple Connected Components (A - B, B - C, D - E, F - G, G - H, H - F)
    runTest({{'A', 'B'}, {'B', 'C'}, {'D', 'E'}, {'F', 'G'}, {'G', 'H'}, {'H', 'F'}}, 8, "Multiple Connected Components");

    // Test 6: Large Tree Structure (A - B, B - C, C - D, D - E)
    runTest({{'A', 'B'}, {'B', 'C'}, {'C', 'D'}, {'D', 'E'}}, 5, "Large Tree Structure");
}

/*
 * OJ main function
 * int main(void){
 *     int m, n;
    std::cin >> m >> n;

    std::shared_ptr<Graph<char>> g{std::make_shared<Graph<char>>()};

    // Add vertices A, B, C, ...
    for (int i{0}; i < m; i++) {
        g->addVertex(i + 'A');
    }

    std::cout << "Enter the edges in the format 's d' where s and d are vertex labels (e.g., A B): " << std::endl;
    for (int j{0}; j < n; j++) {
        char s, d;
        std::cin >> s >> d;
        g->addLink(s, d);
    }

    bool result{g->isForest()};
    std::cout << "Is Forest: " << (result ? "YES" : "NO") << std::endl;

 * }*/
