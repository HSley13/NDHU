#include <iostream>
#include <memory>
#include <string>

template <class T>
class BinarySearchTree {
  private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node(T d) : data(d), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> root;

    void inorder(const std::unique_ptr<Node> &cur) const {
        if (!cur) {
            return;
        }

        inorder(cur->left);
        std::cout << cur->data << " ";
        inorder(cur->right);
    }

    void insertElement(std::unique_ptr<Node> &cur, T d) {
        if (!cur) {
            cur = std::make_unique<Node>(d);
        } else if (d < cur->data) {
            insertElement(cur->left, d);
        } else if (d > cur->data) {
            insertElement(cur->right, d);
        }
    }

    bool search(const std::unique_ptr<Node> &cur, T d) const {
        if (!cur) {
            return false;
        }

        if (cur->data == d) {
            return true;
        }

        if (d < cur->data) {
            return search(cur->left, d);
        }

        return search(cur->right, d);
    }

    int height(const std::unique_ptr<Node> &cur) const {
        if (!cur) {
            return 0;
        }

        int leftHeight{height(cur->left)};
        int rightHeight{height(cur->right)};

        return 1 + std::max(rightHeight, leftHeight);
    }

  public:
    BinarySearchTree() : root(nullptr) {}

    void insertElement(T d) {
        insertElement(root, d);
    }

    void print() const {
        inorder(root);
        std::cout << std::endl;
    }

    bool search(T d) const {
        return search(root, d);
    }

    int height() const {
        return height(root);
    }
};

int main(void) {
    int data;
    std::string command;

    std::unique_ptr<BinarySearchTree<int>> bst = std::make_unique<BinarySearchTree<int>>();

    while (true) {
        std::cin >> command;
        if (command == "insert") {
            std::cin >> data;
            bst->insertElement(data);
        } else if (command == "search") {
            std::cin >> data;
            if (bst->search(data)) {
                std::cout << "true" << std::endl;
            } else {
                std::cout << "false" << std::endl;
            }
        } else if (command == "height") {
            std::cout << bst->height() << std::endl;
        } else if (command == "print") {
            bst->print();
        } else if (command == "exit") {
            break;
        }
    }
}
