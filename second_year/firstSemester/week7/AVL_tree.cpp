#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>

template <class T>
class BinaryTreeNode {
  public:
    T data;
    std::shared_ptr<BinaryTreeNode<T>> left;
    std::shared_ptr<BinaryTreeNode<T>> right;
    int height;

    BinaryTreeNode(T d) : data(d), left(nullptr), right(nullptr), height(1) {}

    bool operator>(BinaryTreeNode<T> &n) {
        return data > n.data;
    }

    bool operator==(BinaryTreeNode<T> &n) {
        return data == n.data;
    }
};

template <class T>
class AVLTree {
  public:
    AVLTree() : root(nullptr) {}

    void insert(T data) {
        root = insert(root, data);
    }

    void inorder() {
        inorder(root, 0);
    }

  private:
    std::shared_ptr<BinaryTreeNode<T>> root;

    int height(std::shared_ptr<BinaryTreeNode<T>> node) {
        if (!node) {
            return 0;
        }
        return node->height;
    }

    int getBalance(std::shared_ptr<BinaryTreeNode<T>> node) {
        if (!node) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    std::shared_ptr<BinaryTreeNode<T>> rightRotate(std::shared_ptr<BinaryTreeNode<T>> y) {
        std::shared_ptr<BinaryTreeNode<T>> x{y->left};
        std::shared_ptr<BinaryTreeNode<T>> T2{x->right};

        x->right = y;
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    std::shared_ptr<BinaryTreeNode<T>> leftRotate(std::shared_ptr<BinaryTreeNode<T>> x) {
        std::shared_ptr<BinaryTreeNode<T>> y{x->right};
        std::shared_ptr<BinaryTreeNode<T>> T2{y->left};

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    std::shared_ptr<BinaryTreeNode<T>> insert(std::shared_ptr<BinaryTreeNode<T>> node, T data) {
        if (!node) {
            return std::make_shared<BinaryTreeNode<T>>(data);
        }

        if (data < node->data) {
            node->left = insert(node->left, data);
        } else if (data > node->data) {
            node->right = insert(node->right, data);
        } else {
            return node;
        }

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance{getBalance(node)};

        if (balance > 1 && data < node->left->data) {
            return rightRotate(node);
        }

        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && data > node->right->data) {
            return leftRotate(node);
        }

        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder(std::shared_ptr<BinaryTreeNode<T>> node, int n) {
        if (!node) {
            return;
        }

        inorder(node->right, n + 1);
        for (int j{0}; j < n; j++) {
            std::cout << "  ";
        }
        std::cout << node->data << std::endl;
        inorder(node->left, n + 1);
    }
};

int main(void) {
    AVLTree<int> tree;

    std::cout << "Inserting elements: 10, 20, 30, 15, 25, 5, 6" << std::endl;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);
    tree.insert(6);

    std::cout << std::endl
              << "Inorder Traversal of the AVL Tree after insertions:" << std::endl;
    tree.inorder();

    std::cout << std::endl
              << "Inserting elements: 35, 50, 40, 45" << std::endl;
    tree.insert(35);
    tree.insert(50);
    tree.insert(40);
    tree.insert(45);

    std::cout << std::endl
              << "Inorder Traversal of the AVL Tree after more insertions:" << std::endl;
    tree.inorder();
}
