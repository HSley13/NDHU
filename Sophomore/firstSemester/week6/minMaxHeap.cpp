#include <iostream>
#include <stdexcept>
#include <vector>

template <class T>
class MinMaxHeap {
  public:
    MinMaxHeap() {}

    void insert(T value) {
        heap.push_back(value);
        bubbleUp(heap.size() - 1);
    }

    T getMin() const {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap[0];
    }

    T getMax() const {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }

        if (heap.size() == 1) {
            return heap[0];
        } else if (heap.size() == 2) {
            return heap[1];
        } else {
            return std::max(heap[1], heap[2]);
        }
    }

    void deleteMin() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }

        heap[0] = heap.back();
        heap.pop_back();

        trickleDown(0);
    }

    void deleteMax() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }

        if (heap.size() == 1) {
            heap.pop_back();
        } else {
            int maxIndex{(heap.size() > 2 && heap[2] > heap[1]) ? 2 : 1};
            heap[maxIndex] = heap.back();
            heap.pop_back();

            trickleDown(maxIndex);
        }
    }

  private:
    std::vector<T> heap;

    bool isMinLevel(int index) const {
        int level{0};
        while (index > 0) {
            index = (index - 1) / 2;
            level++;
        }
        return (level % 2 == 0);
    }

    void bubbleUp(int index) {
        if (!index) {
            return;
        }

        int parentIndex{(index - 1) / 2};
        if (isMinLevel(index)) {
            if (heap[index] > heap[parentIndex]) {
                std::swap(heap[index], heap[parentIndex]);
                bubbleUpHelper(parentIndex, false);
            } else {
                bubbleUpHelper(index, true);
            }
        } else {
            if (heap[index] < heap[parentIndex]) {
                std::swap(heap[index], heap[parentIndex]);
                bubbleUpHelper(parentIndex, true);
            } else {
                bubbleUpHelper(index, false);
            }
        }
    }

    void bubbleUpHelper(int index, bool isMin) {
        if (index < 3) {
            return;
        }

        int grandparentIndex{(index - 3) / 4};
        if ((isMin && heap[index] < heap[grandparentIndex]) || (!isMin && heap[index] > heap[grandparentIndex])) {
            std::swap(heap[index], heap[grandparentIndex]);
            bubbleUpHelper(grandparentIndex, isMin);
        }
    }

    void trickleDown(int index) {
        bool isMin{isMinLevel(index)};
        int extremumIndex{getExtremumChildOrGrandchild(index, isMin)};
        if (extremumIndex != -1) {
            if (extremumIndex > index * 2 + 1 && ((isMin && heap[extremumIndex] < heap[index]) || (!isMin && heap[extremumIndex] > heap[index]))) {
                std::swap(heap[index], heap[extremumIndex]);

                int parentIndex{(extremumIndex - 1) / 2};
                if ((isMin && heap[extremumIndex] > heap[parentIndex]) || (!isMin && heap[extremumIndex] < heap[parentIndex])) {
                    std::swap(heap[extremumIndex], heap[parentIndex]);
                }

                trickleDown(extremumIndex);
            } else if ((isMin && heap[extremumIndex] < heap[index]) || (!isMin && heap[extremumIndex] > heap[index])) {
                std::swap(heap[index], heap[extremumIndex]);
            }
        }
    }

    int getExtremumChildOrGrandchild(int index, bool findMin) const {
        int leftChild{2 * index + 1};
        int rightChild{2 * index + 2};
        int extremumIndex{-1};

        if (leftChild < heap.size()) {
            extremumIndex = leftChild;
        }

        if (rightChild < heap.size() && ((findMin && heap[rightChild] < heap[extremumIndex]) || (!findMin && heap[rightChild] > heap[extremumIndex]))) {
            extremumIndex = rightChild;
        }

        for (int i{0}; i < 4; i++) {
            int grandChild{4 * index + 3 + i};
            if (grandChild < heap.size() && ((findMin && heap[grandChild] < heap[extremumIndex]) || (!findMin && heap[grandChild] > heap[extremumIndex]))) {
                extremumIndex = grandChild;
            }
        }
        return extremumIndex;
    }
};

int main(void) {
    MinMaxHeap<int> mmHeap;
    srand(time(NULL));

    for (int j{0}; j < 10; j++) {
        mmHeap.insert(rand() % 100);
    }

    while (true) {
        try {
            std::cout << mmHeap.getMin() << " ";
            mmHeap.deleteMin();
        } catch (std::exception &) {
            break;
        }
    }

    std::cout << std::endl;

    for (int j{0}; j < 10; j++) {
        mmHeap.insert(rand() % 100);
    }

    while (true) {
        try {
            std::cout << mmHeap.getMax() << " ";
            mmHeap.deleteMax();
        } catch (std::exception &) {
            break;
        }
    }
}
