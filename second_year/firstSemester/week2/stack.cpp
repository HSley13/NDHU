#include <cstring>
#include <iostream>

#define SIZE 3

class Stack {
  public:
    Stack()
        : top{0} {}

    bool push(int value) {
        if (top == SIZE) {
            return false;
        }

        data[top] = value;
        top++;
        return true;
    }

    bool pop(int &value) {
        if (top == 0) {
            return false;
        }

        top--;
        value = data[top];
        return true;
    }

  private:
    int data[SIZE];
    int top;
};

int main(void) {
    int data{0};
    char command[50]{};
    Stack stack{};

    while (true) {
        std::cout << "Enter command (push, pop, exit): ";
        std::cin >> command;

        if (std::strcmp(command, "exit") == 0) {
            break;
        } else if (std::strcmp(command, "push") == 0) {
            std::cout << "Please input an integer: ";
            std::cin >> data;

            if (stack.push(data)) {
                std::cout << "Successfully pushed " << data << " into the stack." << std::endl;
            } else {
                std::cout << "Stack is full. Failed to push data." << std::endl;
            }
        } else if (std::strcmp(command, "pop") == 0) {
            if (stack.pop(data)) {
                std::cout << "Popped " << data << " from the stack." << std::endl;
            } else {
                std::cout << "Stack is empty. Failed to pop data." << std::endl;
            }
        } else {
            std::cout << "Invalid command. Try again." << std::endl;
        }
    }
}
