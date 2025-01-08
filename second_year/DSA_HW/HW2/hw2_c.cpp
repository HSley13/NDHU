#include <array>
#include <iostream>
#include <memory>
#include <stdexcept>

constexpr std::size_t CAPACITY{10};

template <typename KeyType>
class QueueStack {
  public:
    bool IsFull() const {
        return size == CAPACITY;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void push(const KeyType &item) {
        if (IsFull()) {
            throw std::runtime_error("QueueStack is full. Cannot push " + std::to_string(item));
        }

        data[size] = item;
        size++;
    }

    std::unique_ptr<KeyType> pop() {
        if (IsEmpty()) {
            throw std::runtime_error("QueueStack is empty. Cannot pop.");
        }

        size--;
        std::unique_ptr<KeyType> x{std::make_unique<KeyType>(data[size])};
        return x;
    }

    void addRear(const KeyType &item) {
        if (IsFull()) {
            throw std::runtime_error("QueueStack is full. Cannot add " + std::to_string(item));
        }

        data[size] = item;
        size++;
    }

    std::unique_ptr<KeyType> deleteFront() {
        if (IsEmpty()) {
            throw std::runtime_error("QueueStack is empty. Cannot delete front.");
        }

        std::unique_ptr<KeyType> x{std::make_unique<KeyType>(data[0])};
        for (std::size_t i{1}; i < size; i++) {
            data[i - 1] = data[i];
        }

        size--;
        return x;
    }

    void print() const {
        for (std::size_t i{0}; i < size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

  private:
    std::array<KeyType, CAPACITY> data{};
    std::size_t size{0};
};

int main(void) {
    try {
        QueueStack<int> qstack;
        std::cout << "Initial QueueStack (empty): ";
        qstack.print();

        // Test push (stack behavior)
        std::cout << "\n--- Testing Stack Operations ---" << std::endl;
        qstack.push(10);
        qstack.push(20);
        qstack.push(30);
        qstack.print();

        std::unique_ptr<int> poppedValue{qstack.pop()};
        if (poppedValue) {
            std::cout << "Popped: " << *poppedValue << std::endl;
        }
        qstack.print();

        // Test addRear (queue behavior)
        std::cout << "\n--- Testing Queue Operations ---" << std::endl;
        qstack.addRear(40);
        qstack.addRear(50);
        qstack.print();

        std::unique_ptr<int> deletedValue{qstack.deleteFront()};
        if (deletedValue) {
            std::cout << "Deleted Front: " << *deletedValue << std::endl;
        }
        qstack.print();

        // Mixed operations
        std::cout << "\n--- Testing Mixed Operations ---" << std::endl;
        qstack.push(60);
        qstack.addRear(70);
        qstack.print();

        poppedValue = qstack.pop();
        if (poppedValue) {
            std::cout << "Popped: " << *poppedValue << std::endl;
        }
        qstack.print();

        deletedValue = qstack.deleteFront();
        if (deletedValue) {
            std::cout << "Deleted Front: " << *deletedValue << std::endl;
        }
        qstack.print();

        std::cout << "Is QueueStack empty? " << (qstack.IsEmpty() ? "Yes" : "No") << std::endl;

        std::cout << "\n--- Testing Capacity Limit ---" << std::endl;
        for (int i{0}; i < CAPACITY + 2; i++) {
            try {
                qstack.addRear(i);
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
        qstack.print();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
