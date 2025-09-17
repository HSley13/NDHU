#include <algorithm>
#include <iostream>
#include <memory>

template <class T>
class Element {
  public:
    T key;
};

template <class T>
class BSTNode {
  public:
    BSTNode() : LeftChild(nullptr), RightChild(nullptr) {}
    BSTNode(const Element<T> &x) : data(x.key), LeftChild(nullptr), RightChild(nullptr) {}

    int height();
    int weight();
    int heightBF();
    int weightBF();

    std::shared_ptr<BSTNode<T>> LeftChild;
    T data;
    std::shared_ptr<BSTNode<T>> RightChild;
};

template <class T>
class BST {
  public:
    std::shared_ptr<BSTNode<T>> Search(const Element<T> &x);
    std::shared_ptr<BSTNode<T>> Search(std::shared_ptr<BSTNode<T>> b, const Element<T> &x);
    std::shared_ptr<BSTNode<T>> IterSearch(const Element<T> &x);
    void Insert(const Element<T> &x);
    void checkChildrenAndPrint(std::shared_ptr<BSTNode<T>> node);

    void PrintInOrder() const;

    int height();
    int weight();
    int heightBF();
    int weightBF();

  private:
    std::shared_ptr<BSTNode<T>> root;

    void PrintInOrderRecursive(std::shared_ptr<BSTNode<T>> node) const;
};

template <class T>
std::shared_ptr<BSTNode<T>> BST<T>::Search(const Element<T> &x) {
    return Search(root, x);
}

template <class T>
std::shared_ptr<BSTNode<T>> BST<T>::Search(std::shared_ptr<BSTNode<T>> b, const Element<T> &x) {
    if (!b) return nullptr;

    if (x.key == b->data) return b;

    if (x.key < b->data)
        return Search(b->LeftChild, x);

    return Search(b->RightChild, x);
}

template <class T>
std::shared_ptr<BSTNode<T>> BST<T>::IterSearch(const Element<T> &x) {
    std::shared_ptr<BSTNode<T>> t{root};
    while (t) {
        if (x.key == t->data) return t;
        if (x.key < t->data)
            t = t->LeftChild;
        else
            t = t->RightChild;
    }
    return nullptr;
}

template <class T>
void BST<T>::Insert(const Element<T> &x) {
    std::shared_ptr<BSTNode<T>> p{root}, pp{nullptr};
    while (p) {
        pp = p;
        if (x.key < p->data)
            p = p->LeftChild;
        else if (x.key > p->data)
            p = p->RightChild;
        else {
            return;
        }
    }

    p = std::make_shared<BSTNode<T>>(x);

    if (pp) {
        if (x.key < pp->data)
            pp->LeftChild = p;
        else
            pp->RightChild = p;
    } else {
        root = p;
    }
}

template <class T>
int BST<T>::height() {
    if (!root) return -1;
    return root->height();
}

template <class T>
int BST<T>::weight() {
    if (!root) return 0;
    return root->weight();
}

template <class T>
int BST<T>::heightBF() {
    if (!root) return 0;
    return root->heightBF();
}

template <class T>
int BST<T>::weightBF() {
    if (!root) return 0;
    return root->weightBF();
}

template <class T>
int BSTNode<T>::height() {
    int leftHeight{(LeftChild) ? LeftChild->height() : -1};
    int rightHeight{(RightChild) ? RightChild->height() : -1};
    return 1 + std::max(leftHeight, rightHeight);
}

template <class T>
int BSTNode<T>::weight() {
    int leftWeight{(LeftChild) ? LeftChild->weight() : 0};
    int rightWeight{(RightChild) ? RightChild->weight() : 0};
    return 1 + leftWeight + rightWeight;
}

template <class T>
int BSTNode<T>::heightBF() {
    int leftHeight{(LeftChild) ? LeftChild->height() : -1};
    int rightHeight{(RightChild) ? RightChild->height() : -1};

    return leftHeight - rightHeight;
}

template <class T>
int BSTNode<T>::weightBF() {
    int leftWeight{(LeftChild) ? LeftChild->weight() : 0};
    int rightWeight{(RightChild) ? RightChild->weight() : 0};

    return leftWeight - rightWeight;
}

template <class T>
void BST<T>::PrintInOrder() const {
    PrintInOrderRecursive(root);
    std::cout << std::endl;
}

template <class T>
void BST<T>::PrintInOrderRecursive(std::shared_ptr<BSTNode<T>> node) const {
    if (!node) return;

    PrintInOrderRecursive(node->LeftChild);
    std::cout << node->data << " ";
    PrintInOrderRecursive(node->RightChild);
}

template <class T>
void BST<T>::checkChildrenAndPrint(std::shared_ptr<BSTNode<T>> node) {
    if (node) {
        std::cout << std::endl;
        std::cout << "Single Node Check: " << std::endl;
        std::cout << "Node data: " << node->data << std::endl;
        std::cout << "Height of the node: " << node->height() << std::endl;
        std::cout << "Weight of the node: " << node->weight() << std::endl;

        if (node->LeftChild) {
            std::cout << "Left child data: " << node->LeftChild->data << std::endl;
            std::cout << "Height of left child: " << node->LeftChild->height() << std::endl;
            std::cout << "Weight of left child: " << node->LeftChild->weight() << std::endl;
        } else {
            std::cout << "Left child is null" << std::endl;
        }

        if (node->RightChild) {
            std::cout << "Right child data: " << node->RightChild->data << std::endl;
            std::cout << "Height of right child: " << node->RightChild->height() << std::endl;
            std::cout << "Weight of right child: " << node->RightChild->weight() << std::endl;
        } else {
            std::cout << "Right child is null" << std::endl;
        }
    }
}

int main(void) {
    BST<int> tree;

    Element<int> e1{50}, e2{30}, e3{20}, e4{40}, e5{70}, e6{60}, e7{80}, e8{90}, e9{100};
    tree.Insert(e1);
    tree.Insert(e2);
    tree.Insert(e3);
    tree.Insert(e4);
    tree.Insert(e5);
    tree.Insert(e6);
    tree.Insert(e7);
    tree.Insert(e8);
    tree.Insert(e9);

    std::cout << "Height of the tree: " << tree.height() << std::endl;
    std::cout << "Weight of the tree: " << tree.weight() << std::endl;
    std::cout << "Height balance factor of the tree: " << tree.heightBF() << std::endl;
    std::cout << "Weight balance factor of the tree: " << tree.weightBF() << std::endl;

    std::cout << "In-order traversal of the tree: ";
    tree.PrintInOrder();

    std::shared_ptr<BSTNode<int>> searchResult = tree.Search(e5);
    tree.checkChildrenAndPrint(searchResult);
}
