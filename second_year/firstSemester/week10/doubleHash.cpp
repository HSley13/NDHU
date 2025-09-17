#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

template <class T>
class Node {
  public:
    Node() : data(std::make_unique<T>()) {}

    Node(T d) : data(std::make_unique<T>(d)) {}

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

  private:
    std::unique_ptr<T> data;
};

template <class T>
class ListNode : public Node<T> {
  public:
    ListNode() : Node<T>(), prev(nullptr), next(nullptr) {}

    ListNode(T d) : Node<T>(d), prev(nullptr), next(nullptr) {}

    ListNode(std::shared_ptr<ListNode<T>> p, std::shared_ptr<ListNode<T>> n)
        : Node<T>(), prev(p), next(n) {}

    ListNode(T d, std::shared_ptr<ListNode<T>> p, std::shared_ptr<ListNode<T>> n)
        : Node<T>(d), prev(p), next(n) {}

    std::shared_ptr<ListNode<T>> getNext() const {
        return next;
    }

    std::shared_ptr<ListNode<T>> getPrev() const {
        return prev;
    }

    void setNext(std::shared_ptr<ListNode<T>> n) {
        next = n;
    }

    void setPrev(std::shared_ptr<ListNode<T>> p) {
        prev = p;
    }

  private:
    std::shared_ptr<ListNode<T>> prev;
    std::shared_ptr<ListNode<T>> next;
};

template <class T>
class LinkList {
  public:
    LinkList() : head(nullptr), tail(nullptr) {}

    void addFromHead(T d) {
        std::shared_ptr<ListNode<T>> node{std::make_shared<ListNode<T>>(d)};
        if (head != nullptr) {
            head->setPrev(node);
        }

        node->setNext(head);
        head = node;
        if (tail == nullptr) {
            tail = head;
        }
    }

    void addFromTail(T d) {
        std::shared_ptr<ListNode<T>> node{std::make_shared<ListNode<T>>(d)};
        if (tail != nullptr) {
            tail->setNext(node);
        }

        node->setPrev(tail);
        tail = node;
        if (head == nullptr) {
            head = tail;
        }
    }

    void addAfter(std::shared_ptr<ListNode<T>> node, T d) {
        if (!exist(node)) {
            return;
        }

        std::shared_ptr<ListNode<T>> newNode{std::make_shared<ListNode<T>>(d)};
        if (node->getNext() != nullptr)
            node->getNext()->setPrev(newNode);

        newNode->setNext(node->getNext());
        node->setNext(newNode);
        newNode->setPrev(node);

        if (newNode->getNext() == nullptr)
            tail = newNode;
    }

    std::shared_ptr<ListNode<T>> removeFromHead() {
        std::shared_ptr<ListNode<T>> node{head};
        if (head != nullptr) {
            head = head->getNext();
            if (head != nullptr)
                head->setPrev(nullptr);
            else
                tail = nullptr;
            node->setNext(nullptr);
        }
        return node;
    }

    std::shared_ptr<ListNode<T>> removeFromTail() {
        std::shared_ptr<ListNode<T>> node{tail};
        if (tail != nullptr) {
            tail = tail->getPrev();

            if (tail != nullptr)
                tail->setNext(nullptr);
            else
                head = nullptr;
            node->setPrev(nullptr);
        }
        return node;
    }

    std::shared_ptr<ListNode<T>> remove(std::shared_ptr<ListNode<T>> node) {
        if (!exist(node)) {
            return nullptr;
        }

        if (node == head) {
            return removeFromHead();
        } else if (node == tail) {
            return removeFromTail();
        } else {
            node->getPrev()->setNext(node->getNext());
            node->getNext()->setPrev(node->getPrev());
            node->setPrev(nullptr);
            node->setNext(nullptr);
            return node;
        }
    }

    bool exist(std::shared_ptr<ListNode<T>> node) {
        for (std::shared_ptr<ListNode<T>> j{head}; j != nullptr; j = j->getNext()) {
            if (j == node) {
                return true;
            }
        }
        return false;
    }

    std::shared_ptr<ListNode<T>> exist(T d) {
        for (std::shared_ptr<ListNode<T>> j{head}; j != nullptr; j = j->getNext()) {
            if (j->getData() == d) {
                return j;
            }
        }
        return nullptr;
    }

    std::shared_ptr<const ListNode<T>> &operator[](int n) {
        std::shared_ptr<ListNode<T>> j{head};
        for (int i{0}; i < n; i++) {
            if (j == nullptr) {
                throw std::out_of_range("Index out of range");
            }
            j = j->getNext();
        }
        return j;
    }

    void print() const {
        std::shared_ptr<ListNode<T>> j{head};
        while (j != nullptr) {
            std::cout << *j << " ";
            j = j->getNext();
        }
        std::cout << std::endl;
    }

    std::shared_ptr<ListNode<T>> head;
    std::shared_ptr<ListNode<T>> tail;
};

template <class T1, class T2>
class Hash {
  public:
    struct Pair {
        T1 key;
        T2 value;

        Pair() {}

        Pair(T1 k, const T2 &v) : key(k), value(v) {}

        Pair(const Pair &other) : key(other.key), value(other.value) {}

        Pair(Pair &&other) : key(std::move(other.key)), value(std::move(other.value)) {}
    };

    Hash() {
        secondTable = nullptr;
    }

    bool insert(std::shared_ptr<Pair> p) {
        unsigned int hash{HashFunction(p->key)};

        if (table[hash] == nullptr) {
            table[hash] = std::make_shared<LinkList<Pair>>();
            table[hash]->addFromTail(*p);
        } else {
            if (secondTable == nullptr) {
                secondTable = std::make_shared<Hash<T1, T2>>();
            }

            secondTable->insert(p);
        }

        return true;
    }

    std::shared_ptr<Pair> search(T1 key) {
        unsigned int hash{HashFunction(key)};
        if (table[hash] != nullptr) {
            for (std::shared_ptr<ListNode<Pair>> current{table[hash]->head}; current != nullptr; current = current->getNext()) {
                if (current->getData().key == key) {
                    return std::make_shared<Pair>(current->getData());
                }
            }
        }

        if (secondTable != nullptr) {
            return secondTable->search(key);
        }

        return nullptr;
    }

  private:
    std::shared_ptr<LinkList<Pair>> table[100];
    std::shared_ptr<Hash> secondTable;

    unsigned int HashFunction(T1 key) {
        unsigned int size{sizeof(T1)};

        char *keyChar = reinterpret_cast<char *>(&key);
        unsigned int hash{0};
        for (int i{0}; i < size; i++) {
            if (i % 2) {
                hash ^= *keyChar;
            } else {
                hash += *keyChar;
            }
            keyChar++;
        }

        return hash % 100;
    }
};

int main(void) {
    std::shared_ptr<Hash<int, std::string>> hash{std::make_shared<Hash<int, std::string>>()};

    for (int j{1000}; j < 1024; j++) {
        std::shared_ptr<Hash<int, std::string>::Pair> p{std::make_shared<Hash<int, std::string>::Pair>(j, std::to_string(j))};
        hash->insert(p);
    }

    for (int j{1000}; j < 1100; j++) {
        std::shared_ptr<Hash<int, std::string>::Pair> p(hash->search(j));
        if (p) {
            std::cout << p->value << std::endl;
        } else {
            std::cout << "miss" << std::endl;
        }
    }
}
