#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

#define SIZE 100

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

    void swapNodes(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2) {
        if (node1 == node2) {
            return;
        }

        std::shared_ptr<Node> prev1{node1->getPre()};
        std::shared_ptr<Node> next1{node1->getNext()};
        std::shared_ptr<Node> prev2{node2->getPre()};
        std::shared_ptr<Node> next2{node2->getNext()};

        if (node1->getNext() == node2) {
            node1->setNext(next2);
            node1->setPre(node2);
            node2->setNext(node1);
            node2->setPre(prev1);

            if (prev1 != nullptr) {
                prev1->setNext(node2);
            } else {
                list = node2;
            }

            if (next2 != nullptr) {
                next2->setPre(node1);
            }
        } else if (node2->getNext() == node1) {
            node2->setNext(next1);
            node2->setPre(node1);
            node1->setNext(node2);
            node1->setPre(prev2);

            if (prev2 != nullptr) {
                prev2->setNext(node1);
            } else {
                list = node1;
            }

            if (next1 != nullptr) {
                next1->setPre(node2);
            }
        } else {
            if (prev1 != nullptr) {
                prev1->setNext(node2);
            } else {
                list = node2;
            }

            if (prev2 != nullptr) {
                prev2->setNext(node1);
            } else {
                list = node1;
            }

            if (next1 != nullptr) {
                next1->setPre(node2);
            }

            if (next2 != nullptr) {
                next2->setPre(node1);
            }

            node1->setNext(next2);
            node1->setPre(prev2);
            node2->setNext(next1);
            node2->setPre(prev1);
        }
    }

    void bubbleSort() {
        if (list == nullptr || list->getNext() == nullptr) {
            return;
        }

        bool swap{true};
        while (swap) {
            std::shared_ptr<Node> current{list};
            swap = false;
            while (current != nullptr && current->getNext() != nullptr) {
                if (current->getData() > current->getNext()->getData()) {
                    swapNodes(current, current->getNext());
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
                if (next->getData() < min->getData()) {
                    min = next;
                }

                next = next->getNext();
            }

            if (min != current) {
                swapNodes(min, current);
                std::shared_ptr<Node> temp{current};
                current = min;
                min = temp;
            }
            current = current->getNext();
        }
    }

    void insertionSort() {
        if (list == nullptr || list->getNext() == nullptr) {
            return;
        }

        std::shared_ptr<Node> current{list->getNext()};

        while (current != nullptr) {
            std::shared_ptr<Node> next{current->getNext()};
            std::shared_ptr<Node> search{list};

            while (search != current && search->getData() < current->getData()) {
                search = search->getNext();
            }

            if (search != current) {
                std::shared_ptr<Node> prev{current->getPre()};
                std::shared_ptr<Node> nextCurrent{current->getNext()};

                if (prev != nullptr) {
                    prev->setNext(nextCurrent);
                }

                if (nextCurrent != nullptr) {
                    nextCurrent->setPre(prev);
                }

                std::shared_ptr<Node> searchPrev{search->getPre()};

                current->setNext(search);
                current->setPre(searchPrev);

                if (searchPrev != nullptr) {
                    searchPrev->setNext(current);
                } else {
                    list = current;
                }
                search->setPre(current);
            }
            current = next;
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
    l->selectionSort();
    l->print();
    std::cout << std::endl;

    l = std::make_shared<List>(10);
    l->print();
    l->insertionSort();
    l->print();
}
