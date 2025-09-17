#include <cstring>
#include <iostream>

#define SIZE 3

class Queue {
  public:
    Queue()
        : top{0}, bot{-1}, count{0} {}

    bool enqueue(int value) {
        if (count == SIZE) {
            return false;
        }

        data[top] = value;
        top = (top + 1) % SIZE;
        count++;
        return true;
    }

    bool dequeue(int &value) {
        if (count == 0) {
            return false;
        }

        bot = (bot + 1) % SIZE;
        value = data[bot];
        count--;
        return true;
    }

  private:
    int data[SIZE];
    int top;
    int bot;
    int count;
};

int main(void) {
    int data{0};
    char command[50]{};
    Queue queue{};

    while (true) {
        std::cout << "Enter command (enqueue, dequeue, exit): ";
        std::cin >> command;

        if (std::strcmp(command, "exit") == 0) {
            break;
        } else if (std::strcmp(command, "enqueue") == 0) {
            std::cout << "Please input an integer: ";
            std::cin >> data;

            if (queue.enqueue(data)) {
                std::cout << "Successfully enqueued " << data << " into the queue." << std::endl;
            } else {
                std::cout << "Queue is full. Failed to enqueue data." << std::endl;
            }
        } else if (std::strcmp(command, "dequeue") == 0) {
            if (queue.dequeue(data)) {
                std::cout << "Dequeued " << data << " from the queue." << std::endl;
            } else {
                std::cout << "Queue is empty. Failed to dequeue data." << std::endl;
            }
        } else {
            std::cout << "Invalid command. Try again." << std::endl;
        }
    }
}
