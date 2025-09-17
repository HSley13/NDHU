#include <ctime>
#include <iostream>
#include <vector>

int partition(std::vector<int> &arr, int low, int high) {
    // Generate random index between low and high
    srand(time(NULL));
    int random = low + rand() % (high - low);
    std::swap(arr[random], arr[high]); // Swap random element to the end
    int pivot = arr[high];

    int i{low - 1}; // Index of smaller element

    for (int j{low}; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int> &arr, int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi{partition(arr, low, high)};

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(const std::vector<int> &arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main(void) {
    // Generate random array
    std::vector<int> arr;
    for (int i{0}; i < 20; i++) {
        arr.push_back(rand() % 100);
    }

    size_t n{arr.size()};

    std::cout << "Original array: ";
    printArray(arr);

    quickSort(arr, 0, n - 1);

    std::cout << "Sorted array: ";
    printArray(arr);
}
