#include <iostream>
#include <vector>

void merge(std::vector<int> &arr, int left, int mid, int right) {
    int n1{mid - left + 1}; // Size of left subarray
    int n2{right - mid};    // Size of right subarray

    // Create temporary arrays
    std::vector<int> L(n1), R(n2);

    // Copy data to temp arrays
    for (int i{0}; i < n1; i++)
        L[i] = arr[left + i];

    for (int j{0}; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[left..right]
    int i{0};    // Initial index of left subarray
    int j{0};    // Initial index of right subarray
    int k{left}; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[] if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[] if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int> &arr, int left, int right) {
    if (left < right) {
        int mid{left + (right - left) / 2};

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
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

    mergeSort(arr, 0, n - 1);

    std::cout << "Sorted array: ";
    printArray(arr);
}
