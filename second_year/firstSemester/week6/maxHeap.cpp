#include <iostream>
#include <stdexcept>
#include <vector>

template <class T>
class MaxHeap {
  public:
    MaxHeap() : heap() {}

    void insert(T value) {
        heap.push_back(value);
        siftUp(heap.size() - 1);
    }

    T extract() {
        if (heap.empty()) {
            throw std::runtime_error("Heap is empty");
        }

        T root_value{heap[0]};
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0);

        return root_value;
    }

    int count() {
        return heap.size();
    }

  private:
    std::vector<T> heap;

    void siftUp(int index) {
        while (index > 0) {
            int parentIndex{(index - 1) / 2};
            if (heap[index] <= heap[parentIndex]) {
                break;
            }

            std::swap(heap[index], heap[parentIndex]);
            index = parentIndex;
        }
    }

    void siftDown(int index) {
        while (true) {
            int leftChildIndex{2 * index + 1};
            int rightChildIndex{2 * index + 2};
            int largestIndex{index};

            if (leftChildIndex < heap.size() && heap[leftChildIndex] > heap[largestIndex]) {
                largestIndex = leftChildIndex;
            }

            if (rightChildIndex < heap.size() && heap[rightChildIndex] > heap[largestIndex]) {
                largestIndex = rightChildIndex;
            }

            if (largestIndex == index) {
                break;
            }

            std::swap(heap[index], heap[largestIndex]);
            index = largestIndex;
        }
    }
};

int main(void) {
    try {
        MaxHeap<int> maxHeap;

        maxHeap.insert(10);
        maxHeap.insert(20);
        maxHeap.insert(5);
        maxHeap.insert(30);
        maxHeap.insert(15);

        // MaxHeap<std::string> maxHeap;
        //
        //   // Insert values into the heap.
        //   maxHeap.insert("banana");
        //   maxHeap.insert("apple");
        //   maxHeap.insert("grape");
        //   maxHeap.insert("orange");
        //   maxHeap.insert("kiwi");

        std::cout << "MaxHeap elements extracted in order:\n";

        while (maxHeap.count() > 0) {
            std::cout << maxHeap.extract() << " ";
        }
        std::cout << std::endl;
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}
