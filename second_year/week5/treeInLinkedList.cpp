#include <iostream>
#include <memory>
#include <vector>

template <class T>
class TreeInLinkedList {
  private:
    class TreeNode {
      public:
        TreeNode(T d, std::shared_ptr<TreeNode> p) : data(d), parent(p) {}

        std::shared_ptr<TreeNode> parent;
        T data;
    };

    std::shared_ptr<std::vector<std::shared_ptr<TreeNode>>> nodeList;

  public:
    TreeInLinkedList() {
        nodeList = std::make_shared<std::vector<std::shared_ptr<TreeNode>>>();
    }

    void addElement(T data) {
        int k{(int)nodeList->size()};
        if (data == 1) {
            nodeList->clear();
            nodeList = std::make_shared<std::vector<std::shared_ptr<TreeNode>>>();
            std::shared_ptr<TreeNode> new_node = std::make_shared<TreeNode>(data, nullptr);
            nodeList->push_back(new_node);
        } else {
            for (int j{0}; j < k; j++) {
                if (data % (*nodeList)[j]->data == 0) {
                    std::shared_ptr<TreeNode> new_node = std::make_shared<TreeNode>(data, (*nodeList)[j]);
                    nodeList->push_back(new_node);
                }
            }
        }
    }

    void displayPreorder() {
        preorderTraversal((*nodeList)[0]);
    }

    void displayPostorder() {
        postorderTraversal((*nodeList)[0]);
    }

  private:
    void preorderTraversal(std::shared_ptr<TreeNode> node) {
        if (!node) {
            return;
        }

        std::cout << node->data << " ";
        for (size_t i{0}; i < nodeList->size(); i++) {
            if ((*nodeList)[i]->parent == node) {
                preorderTraversal((*nodeList)[i]);
            }
        }
    }

    void postorderTraversal(std::shared_ptr<TreeNode> node) {
        if (!node) {
            return;
        }

        for (size_t i{0}; i < nodeList->size(); i++) {
            if ((*nodeList)[i]->parent == node) {
                postorderTraversal((*nodeList)[i]);
            }
        }
        std::cout << node->data << " ";
    }
};

int main(void) {
    std::shared_ptr<TreeInLinkedList<int>> tree = std::make_shared<TreeInLinkedList<int>>();

    int n;
    std::cin >> n;

    for (int j{1}; j <= n; j++) {
        tree->addElement(j);
    }

    tree->displayPreorder();
    std::cout << std::endl;

    tree->displayPostorder();
    std::cout << std::endl;
}
