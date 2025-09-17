#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <memory>

template <class T>
class BinaryThreadedTreeNode {
  public:
    T data;
    std::shared_ptr<BinaryThreadedTreeNode> left{nullptr}, right{nullptr};
    bool isThread;

    BinaryThreadedTreeNode(T d)
        : data(d), left(nullptr), right(nullptr), isThread(false) {}
};

template <class T>
class BinarySearchThreadedTree {
  public:
    BinarySearchThreadedTree() : root(nullptr) {}

    void insert(T d) {
        if (!root) {
            root = std::make_shared<BinaryThreadedTreeNode<T>>(d);
            return;
        }

        std::function<void(std::shared_ptr<BinaryThreadedTreeNode<T>>, T)> insertHelper = [&](std::shared_ptr<BinaryThreadedTreeNode<T>> node, T value) {
            if (value < node->data) {
                if (node->left) {
                    insertHelper(node->left, value);
                } else {
                    node->left = std::make_shared<BinaryThreadedTreeNode<T>>(value);
                }
            } else if (value > node->data) {
                if (node->right) {
                    insertHelper(node->right, value);
                } else {
                    node->right = std::make_shared<BinaryThreadedTreeNode<T>>(value);
                }
            }
        };

        insertHelper(root, d);
    }

    void createThreads() {
        std::shared_ptr<BinaryThreadedTreeNode<T>> lastVisited{nullptr};

        std::function<void(std::shared_ptr<BinaryThreadedTreeNode<T>>)> createThreadsHelper = [&](std::shared_ptr<BinaryThreadedTreeNode<T>> node) {
            if (!node) {
                return;
            }

            createThreadsHelper(node->left);

            if (lastVisited && !lastVisited->right) {
                lastVisited->right = node;
                lastVisited->isThread = true;
            }

            lastVisited = node;

            if (!node->isThread) {
                createThreadsHelper(node->right);
            }
        };

        createThreadsHelper(root);
    }

    void print() {
        createThreads();

        std::shared_ptr<BinaryThreadedTreeNode<T>> node{leftmost(root)};
        while (node) {
            std::cout << node->data << " ";
            if (node->isThread) {
                node = node->right;
            } else {
                node = leftmost(node->right);
            }
        }
        std::cout << std::endl;
    }

    void printTree() {
        if (!root) {
            std::cout << "Tree is empty." << std::endl;
            return;
        }

        std::function<void(std::shared_ptr<BinaryThreadedTreeNode<T>>, const std::string &, bool)> printTreeHelper = [&](std::shared_ptr<BinaryThreadedTreeNode<T>> node, const std::string &prefix, bool isLeft) {
            if (node) {
                std::cout << prefix;
                std::cout << (isLeft ? "├── " : "└── ");
                std::cout << node->data << (node->isThread ? " [T]" : "") << std::endl;

                printTreeHelper(node->left, prefix + (isLeft ? "│   " : "    "), true);
                if (!node->isThread) {
                    printTreeHelper(node->right, prefix + (isLeft ? "│   " : "    "), false);
                }
            }
        };

        printTreeHelper(root, "", true);
    }

  private:
    std::shared_ptr<BinaryThreadedTreeNode<T>> root;

    std::shared_ptr<BinaryThreadedTreeNode<T>> leftmost(std::shared_ptr<BinaryThreadedTreeNode<T>> node) const {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }
};

int main(void) {
    BinarySearchThreadedTree<int> bstt;

    // Test Case 1: Insert a predefined set of numbers
    std::cout << "Inserting values into the tree...\n";
    std::vector<int> values{15, 10, 20, 8, 12, 18, 25, 5, 9, 11, 13, 17, 19};
    for (int value : values) {
        bstt.insert(value);
    }

    // Test Case 2: Print the in-order traversal
    std::cout << "In-order traversal of the threaded binary tree:\n";
    bstt.print();
    bstt.printTree();

    // Test Case 3: Insert additional values
    std::cout << "\nInserting additional values (30 and 1):\n";
    bstt.insert(30);
    bstt.insert(1);
    std::cout << "In-order traversal after inserting additional values:\n";
    bstt.print();
    bstt.printTree();

    // Test Case 4: Randomized insertion
    std::cout << "\nTesting randomized insertion:\n";
    BinarySearchThreadedTree<int> randomTree;
    std::srand(std::time(nullptr));
    for (int i{0}; i < 10; i++) {
        int randomValue = std::rand() % 50;
        randomTree.insert(randomValue);
        std::cout << "Inserted: " << randomValue << std::endl;
    }
    std::cout << "In-order traversal of the randomly generated tree:\n";
    randomTree.print();
    randomTree.printTree();

    // Test Case 5: Single-node tree
    std::cout << "\nTesting a single-node tree:\n";
    BinarySearchThreadedTree<int> singleNodeTree;
    singleNodeTree.insert(42);
    std::cout << "In-order traversal of the single-node tree:\n";
    singleNodeTree.print();
    singleNodeTree.printTree();

    // Test Case 6: Empty tree
    std::cout << "\nTesting an empty tree:\n";
    BinarySearchThreadedTree<int> emptyTree;
    std::cout << "In-order traversal of the empty tree:\n";
    emptyTree.print();
    emptyTree.printTree();

    std::cout << "\nAll test cases completed successfully.\n";
}
