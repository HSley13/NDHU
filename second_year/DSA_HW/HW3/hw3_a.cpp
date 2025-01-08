#include <iostream>
#include <memory>

template <class T>
class List;

template <class T>
class ListNode {
    friend class List<T>;

  private:
    T data;
    std::shared_ptr<ListNode<T>> link;
};

template <class T>
class List {
  public:
    List() : first(nullptr), last(nullptr) {}
    void Attach(T k);
    bool appearM(T k, int m);
    int replaceAll(T k1, T k2);
    List<T> sublist(int m, int n);
    void rotate(char direction, int m);
    void print() const;

  private:
    std::shared_ptr<ListNode<T>> first;
    std::shared_ptr<ListNode<T>> last;
    int count{0};
};

template <class T>
void List<T>::Attach(T k) {
    std::shared_ptr<ListNode<T>> newNode{std::make_shared<ListNode<T>>()};
    newNode->data = k;
    if (first == nullptr) {
        first = last = newNode;
    } else {
        last->link = newNode;
        last = newNode;
    }
    count++;
}

template <class T>
bool List<T>::appearM(T k, int m) {
    int count{0};
    std::shared_ptr<ListNode<T>> current{first};
    while (current) {
        if (current->data == k) count++;
        if (count >= m) return true;

        current = current->link;
    }
    return false;
}

template <class T>
int List<T>::replaceAll(T k1, T k2) {
    int count{0};
    std::shared_ptr<ListNode<T>> current{first};
    while (current) {
        if (current->data == k1) {
            current->data = k2;
            count++;
        }
        current = current->link;
    }
    return count;
}

template <class T>
void List<T>::rotate(char direction, int m) {
    if (!first || !first->link) return;

    m %= this->count;
    if (m == 0) return;

    if (direction == 'L') {
        for (int i{0}; i < m; i++) {
            std::shared_ptr<ListNode<T>> temp{first};
            first = first->link;
            last->link = temp;
            last = temp;
            last->link = nullptr;
        }
    } else if (direction == 'R') {
        m = this->count - m;
        rotate('L', m);
    } else {
        throw std::invalid_argument("Invalid direction. Use 'L' for left or 'R' for right.");
    }
}

template <class T>
List<T> List<T>::sublist(int m, int n) {
    if (m > n || m < 0) {
        throw std::invalid_argument("Invalid indices for sublist");
    }

    List<T> sub;
    std::shared_ptr<ListNode<T>> current{first};
    int index{0};
    while (current && index <= n) {
        if (index >= m) sub.Attach(current->data);

        index++;
        current = current->link;
    }
    return sub;
}

template <class T>
void List<T>::print() const {
    std::shared_ptr<ListNode<T>> current{first};
    while (current) {
        std::cout << current->data;
        current = current->link;
        if (current) std::cout << " --> ";
    }
    std::cout << std::endl;
}

int main(void) {
    try {
        List<int> myList;

        myList.Attach(10);
        myList.Attach(20);
        myList.Attach(30);
        myList.Attach(20);
        myList.Attach(40);
        myList.Attach(50);
        std::cout << "List after Attach: ";
        myList.print();

        std::cout << "Does 20 Appear at least 2 times? " << (myList.appearM(20, 2) ? "Yes" : "No") << std::endl;

        int replacedCount = myList.replaceAll(20, 99);
        std::cout << "Replaced 20 with 99 " << replacedCount << " times. " << "List after replaceAll: ";
        myList.print();

        myList.rotate('L', 2);
        std::cout << "List after left rotation by 2: ";
        myList.print();

        myList.rotate('R', 2);
        std::cout << "List after right rotation by 2: ";
        myList.print();

        List<int> subList = myList.sublist(1, 4);
        std::cout << "Sublist from index 1 to 4: ";
        subList.print();

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
