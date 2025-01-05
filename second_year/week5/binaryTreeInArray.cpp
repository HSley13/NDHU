#include <cmath>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

template <class T>
class BinaryTreeInArray {
  public:
    BinaryTreeInArray() : height(0), numOfElement(0) {}

    void addElementAsCompleteTree(T data) {
        int cap{(int)pow(2, height) - 1};

        if (numOfElement + 1 > cap) {
            resize((cap + 1) * 2 - 1);
        }

        array[numOfElement] = data;
        numOfElement++;
    }

    void displayInorder() {
        displayInOrderHelper(0);
    }

    void displayPreorder() {
        displayInPreorderHelper(0);
    }

    void displayPostorder() {
        displayInPostorderHelper(0);
    }

  private:
    std::vector<T> array;
    int height;
    int numOfElement;

    void resize(int size) {
        array.resize(size);
        height++;
    }

    void displayInOrderHelper(int index) {
        if (index >= numOfElement) {
            return;
        }

        displayInOrderHelper(2 * index + 1);
        std::cout << array[index] << " ";
        displayInOrderHelper(2 * index + 2);
    }

    void displayInPreorderHelper(int index) {
        if (index >= numOfElement) {
            return;
        }

        std::cout << array[index] << " ";
        displayInPreorderHelper(2 * index + 1);
        displayInPreorderHelper(2 * index + 2);
    }

    void displayInPostorderHelper(int index) {
        if (index >= numOfElement) {
            return;
        }

        displayInPostorderHelper(2 * index + 1);
        displayInPostorderHelper(2 * index + 2);
        std::cout << array[index] << " ";
    }
};

template <class T>
class BinaryTreeInLinkedList {
  public:
    BinaryTreeInLinkedList() : numOfElement(0) {}

    void addElementAsCompleteTree(T data) {
        if (!root) {
            root = std::make_unique<TreeNode>(data);
        } else {
            addHelper(root, data);
        }
        numOfElement++;
    }

    void displayInorder() {
        displayInOrderHelper(root);
    }

    void displayPreorder() {
        displayInPreorderHelper(root);
    }

    void displayPostorder() {
        displayInPostorderHelper(root);
    }

  private:
    class TreeNode {
      public:
        TreeNode(T d) : data(d) {}

        std::unique_ptr<TreeNode> left;
        std::unique_ptr<TreeNode> right;
        T data;
    };

    std::unique_ptr<TreeNode> root;
    int numOfElement;

    void addHelper(std::unique_ptr<TreeNode> &node, T data) {
        std::queue<TreeNode *> q;
        q.push(node.get());

        while (!q.empty()) {
            TreeNode *current = q.front();
            q.pop();

            if (!current->left) {
                current->left = std::make_unique<TreeNode>(data);
                return;
            } else {
                q.push(current->left.get());
            }

            if (!current->right) {
                current->right = std::make_unique<TreeNode>(data);
                return;
            } else {
                q.push(current->right.get());
            }
        }
    }

    void displayInOrderHelper(const std::unique_ptr<TreeNode> &node) {
        if (!node) {
            return;
        }

        displayInOrderHelper(node->left);
        std::cout << node->data << " ";
        displayInOrderHelper(node->right);
    }

    void displayInPreorderHelper(const std::unique_ptr<TreeNode> &node) {
        if (!node) {
            return;
        }

        std::cout << node->data << " ";
        displayInPreorderHelper(node->left);
        displayInPreorderHelper(node->right);
    }

    void displayInPostorderHelper(const std::unique_ptr<TreeNode> &node) {
        if (!node) {
            return;
        }

        displayInPostorderHelper(node->left);
        displayInPostorderHelper(node->right);
        std::cout << node->data << " ";
    }
};

int main(void) {
    std::unique_ptr<BinaryTreeInArray<int>> b = std::make_unique<BinaryTreeInArray<int>>();
    std::unique_ptr<BinaryTreeInLinkedList<int>> tree = std::make_unique<BinaryTreeInLinkedList<int>>();

    int n;
    std::cin >> n;

    for (int j{0}; j < n; j++) {
        b->addElementAsCompleteTree(j);
        tree->addElementAsCompleteTree(j);
    }

    b->displayInorder();
    std::cout << std::endl;

    tree->displayInorder();
    std::cout << std::endl;

    b->displayPreorder();
    std::cout << std::endl;

    tree->displayPreorder();
    std::cout << std::endl;

    b->displayPostorder();
    std::cout << std::endl;

    tree->displayPostorder();
    std::cout << std::endl;
}
