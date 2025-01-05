#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

class Node {
  public:
    Node()
        : data{0}, next{nullptr}, pre{nullptr} {}

    Node(int n)
        : data{n}, next{nullptr}, pre{nullptr} {}

    int getData() {
        return data;
    }

    std::shared_ptr<Node> getNext() {
        return next;
    }

    std::shared_ptr<Node> getPre() {
        return pre;
    }

    void setData(int d) {
        data = d;
    }

    void setNext(std::shared_ptr<Node> n) {
        next = n;
    }

    void setPre(std::shared_ptr<Node> p) {
        pre = p;
    }

  private:
    int data;
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> pre;
};

class List {
  public:
    List()
        : list{nullptr} {}

    List(int n) {
        generate(n);
    }

    void generate(int n) {
        list = nullptr;

        for (int j{0}; j < n; j++) {
            generate();
        }
    }

    void generate() {
        std::shared_ptr<Node> buf{std::make_shared<Node>(rand() % 10)};

        buf->setNext(list);

        if (list != nullptr) {
            list->setPre(buf);
        }

        list = buf;
    }

    void bubbleSort() {
        if (list == nullptr || list->getNext() == nullptr) {
            return;
        }

        bool swap{true};
        while (swap) {
            std::shared_ptr<Node> current{list};
            swap = false;
            while (current->getNext() != nullptr) {
                if (current->getData() > current->getNext()->getData()) {
                    int temp{current->getData()};
                    current->setData(current->getNext()->getData());
                    current->getNext()->setData(temp);
                    swap = true;
                }
                current = current->getNext();
            }
        }
    }

    void selectionSort() {
        if (list == nullptr || list->getNext() == nullptr) {
            return;
        }

        std::shared_ptr<Node> current{list};

        while (current != nullptr) {
            std::shared_ptr<Node> min{current};
            std::shared_ptr<Node> next{current->getNext()};

            while (next != nullptr) {
                if (min->getData() > next->getData()) {
                    min = next;
                }

                next = next->getNext();
            }

            if (min != current) {
                int temp{current->getData()};
                current->setData(min->getData());
                min->setData(temp);
            }
            current = current->getNext();
        }
    }

    void insertionSort() {
        if (list == nullptr || list->getNext() == nullptr) {
            return;
        }

        std::shared_ptr<Node> sorted{std::make_shared<Node>(0)};
        std::shared_ptr<Node> current{list};

        while (current != nullptr) {
            std::shared_ptr<Node> next{current->getNext()};

            std::shared_ptr<Node> temp{sorted};
            while (temp->getNext() != nullptr && temp->getNext()->getData() < current->getData()) {
                temp = temp->getNext();
            }

            if (current->getPre()) {
                current->getPre()->setNext(current->getNext());
            }

            if (current->getNext()) {
                current->getNext()->setPre(current->getPre());
            }

            current->setPre(temp);
            if (temp->getNext()) {
                temp->getNext()->setPre(current);
            }
            current->setNext(temp->getNext());
            temp->setNext(current);

            current = next;
        }

        list = sorted->getNext();
        if (list != nullptr) {
            list->setPre(nullptr);
        }
    }

    void print() {
        std::shared_ptr<Node> cur{list};

        while (cur != nullptr) {
            std::cout << cur->getData() << " ";
            cur = cur->getNext();
        }

        std::cout << std::endl;
    }

  private:
    std::shared_ptr<Node> list;
};

int main(void) {
    srand(time(nullptr));

    std::shared_ptr<List> l{std::make_shared<List>(10)};

    l->print();
    l->bubbleSort();
    l->print();
    std::cout << std::endl;

    l = std::make_shared<List>(10);
    l->print();
    l->insertionSort();
    l->print();
    std::cout << std::endl;

    l = std::make_shared<List>(10);
    l->print();
    l->selectionSort();
    l->print();
}
