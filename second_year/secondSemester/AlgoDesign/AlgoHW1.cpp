#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

// Insertion sort for small subarrays
void insertion_sort(std::vector<int> &arr, int left, int right) {
    for (int i{left + 1}; i <= right; i++) {
        int key{arr[i]};
        int j{i - 1};
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge function for merge sort
void merge(std::vector<int> &arr, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i{left}, j{mid + 1}, k{0};

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int p{0}; p < k; p++) {
        arr[left + p] = temp[p];
    }
}

// Merge sort with configurable threshold
void merge_sort(std::vector<int> &arr, int left, int right, int threshold) {
    if (right - left + 1 <= threshold) {
        insertion_sort(arr, left, right);
        return;
    }

    int mid{left + (right - left) / 2};
    merge_sort(arr, left, mid, threshold);
    merge_sort(arr, mid + 1, right, threshold);
    merge(arr, left, mid, right);
}

// Partition function for quick sort
int partition(std::vector<int> &arr, int left, int right) {
    int pivot{arr[right]};
    int i{left - 1};

    for (int j{left}; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[right]);
    return i + 1;
}

// Quick sort with configurable threshold
void quick_sort(std::vector<int> &arr, int left, int right, int threshold) {
    if (right - left + 1 <= threshold) {
        insertion_sort(arr, left, right);
        return;
    }

    if (left < right) {
        int p{partition(arr, left, right)};
        quick_sort(arr, left, p - 1, threshold);
        quick_sort(arr, p + 1, right, threshold);
    }
}

// Generate different types of arrays
enum class ArrayType { RANDOM,
                       SORTED,
                       REVERSE_SORTED,
                       PARTIALLY_SORTED };

std::vector<int> generate_array(int size, ArrayType type) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, size * 10);

    // Generate base array
    for (int i{0}; i < size; i++) {
        arr[i] = dis(gen);
    }

    // Modify based on type
    switch (type) {
    case ArrayType::SORTED:
        std::sort(arr.begin(), arr.end());
        break;
    case ArrayType::REVERSE_SORTED:
        std::sort(arr.begin(), arr.end(), std::greater<int>());
        break;
    case ArrayType::PARTIALLY_SORTED:
        std::sort(arr.begin(), arr.begin() + (size * 9 / 10));
        break;
    case ArrayType::RANDOM:
    default:
        break;
    }

    return arr;
}

// Verify if array is sorted
bool is_sorted(const std::vector<int> &arr) {
    for (size_t i{1}; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

// Test function with verification
void test_sort(const std::string &name,
               void (*sort_func)(std::vector<int> &, int, int, int),
               std::vector<int> arr,
               int threshold,
               const std::string &array_type) {
    auto start = std::chrono::high_resolution_clock::now();
    sort_func(arr, 0, arr.size() - 1, threshold);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    bool sorted{is_sorted(arr)};

    std::cout << std::setw(12) << name << " | "
              << std::setw(15) << array_type << " | "
              << "Threshold: " << std::setw(3) << threshold << " | "
              << "Time: " << std::setw(8) << duration.count() << " μs | "
              << "Sorted: " << (sorted ? "Yes" : "No") << std::endl;
}

int main(void) {
    std::vector<int> sizes{{1000, 10000, 100000, 1000000}};
    std::vector<int> thresholds{{5, 10, 20, 50}};
    std::vector<std::pair<ArrayType, std::string>> array_types = {
        {ArrayType::RANDOM, "Random"},
        {ArrayType::SORTED, "Sorted"},
        {ArrayType::REVERSE_SORTED, "Reverse Sorted"},
        {ArrayType::PARTIALLY_SORTED, "90% Sorted"}};

    std::cout << "Sorting Algorithm Comparison\n";
    std::cout << "===========================\n\n";

    for (int size : sizes) {
        std::cout << "\nTesting with array size: " << size << "\n";
        std::cout << "------------------------------------------------------------\n";

        for (const auto &[type, type_name] : array_types) {
            std::vector<int> arr{generate_array(size, type)};

            // Test standard sort for comparison
            std::vector<int> arr_std{arr};
            auto start = std::chrono::high_resolution_clock::now();
            std::sort(arr_std.begin(), arr_std.end());
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            std::cout << std::setw(12) << "std::sort" << " | "
                      << std::setw(15) << type_name << " | "
                      << "Threshold: " << std::setw(3) << "N/A" << " | "
                      << "Time: " << std::setw(8) << duration.count() << " μs | "
                      << "Sorted: Yes" << std::endl;

            for (int threshold : thresholds) {
                std::vector<int> arr_merge{arr};
                std::vector<int> arr_quick{arr};

                test_sort("Merge Sort", merge_sort, arr_merge, threshold, type_name);
                test_sort("Quick Sort", quick_sort, arr_quick, threshold, type_name);
            }
            std::cout << "------------------------------------------------------------\n";
        }
    }
}
