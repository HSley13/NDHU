#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

template <typename KeyType>
class Stack {
  public:
    void push(const KeyType &x) {
        data.push_back(x);
    }

    void pop() {
        if (data.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        data.pop_back();
    }

    KeyType top() const {
        if (data.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return data.back();
    }

    bool empty() const {
        return data.empty();
    }

    void moveToTop(const KeyType &x) {
        auto it{std::find(data.begin(), data.end(), x)};
        if (it != data.end()) {
            KeyType value{*it};
            data.erase(it);
            data.push_back(value);
        } else {
            throw std::invalid_argument("Element not found in stack");
        }
    }

    void print() const {
        for (auto it{data.rbegin()}; it != data.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

  private:
    std::vector<KeyType> data;
};

template <typename KeyType>
class Queue {
  public:
    void enqueue(const KeyType &x) {
        data.push_back(x);
    }

    void dequeue() {
        if (data.empty()) {
            throw std::out_of_range("Queue is empty");
        }
        data.erase(data.begin());
    }

    KeyType front() const {
        if (data.empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return data.front();
    }

    KeyType rear() const {
        if (data.empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return data.back();
    }

    bool empty() const {
        return data.empty();
    }

    void moveToFront(const KeyType &x) {
        auto it{std::find(data.begin(), data.end(), x)};
        if (it != data.end()) {
            KeyType value{*it};
            data.erase(it);
            data.insert(data.begin(), value);
        } else {
            throw std::invalid_argument("Element not found in queue");
        }
    }

    void moveToRear(const KeyType &x) {
        auto it{std::find(data.begin(), data.end(), x)};
        if (it != data.end()) {
            KeyType value{*it};
            data.erase(it);
            data.push_back(value);
        } else {
            throw std::invalid_argument("Element not found in queue");
        }
    }

    void print() const {
        for (const auto &item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

  private:
    std::vector<KeyType> data;
};

int main(void) {
    try {
        // **Test for Stack**
        std::cout << "----- Testing Stack -----" << std::endl;
        Stack<int> stack;
        stack.push(10);
        stack.push(20);
        stack.push(30);
        stack.push(40);
        std::cout << "Initial stack: ";
        stack.print();

        std::cout << "Move 20 to top" << std::endl;
        stack.moveToTop(20);
        stack.print();

        std::cout << "Move 50 to top (not present, should throw exception)" << std::endl;
        stack.moveToTop(50);
        stack.print();

        // **Test for Queue**
        std::cout << "\n----- Testing Queue -----" << std::endl;
        Queue<int> queue;
        queue.enqueue(10);
        queue.enqueue(20);
        queue.enqueue(30);
        queue.enqueue(40);
        std::cout << "Initial queue: ";
        queue.print();

        std::cout << "Move 30 to front" << std::endl;
        queue.moveToFront(30);
        queue.print();

        std::cout << "Move 40 to rear" << std::endl;
        queue.moveToRear(40);
        queue.print();

        std::cout << "Move 50 to front (not present, should throw exception)" << std::endl;
        queue.moveToFront(50);
        queue.print();

        std::cout << "Move 10 to rear" << std::endl;
        queue.moveToRear(10);
        queue.print();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
