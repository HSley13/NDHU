#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int find_min_small(const std::vector<int> &arr, int low, int high);

int find_min_dc(const std::vector<int> &arr, int low, int high) {
    // Base case: when range size <= 3, call the provided function
    const int THRESHOLD{3};
    if (high - low + 1 <= THRESHOLD) {
        return find_min_small(arr, low, high);
    }

    // Divide: calculate the midpoint
    int mid{low + (high - low) / 2};

    // Conquer: recursively find the minimum in left and right sub-ranges
    int min_left{find_min_dc(arr, low, mid)};
    int min_right{find_min_dc(arr, mid + 1, high)};

    // Combine: compare the minimums from left and right
    return std::min(min_left, min_right);
}

// Implementation of the helper function
int find_min_small(const std::vector<int> &arr, int low, int high) {
    if (low > high) {
        return std::numeric_limits<int>::max();
    }

    int min_val{arr[low]};
    for (int i{low + 1}; i <= high; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}

int main(void) {
    int n;
    std::cin >> n;

    // Read array elements
    std::vector<int> arr(n);
    for (int i{0}; i < n; i++) {
        std::cin >> arr[i];
    }

    // Query the minimum of the entire array
    int low_query{0};
    int high_query{n - 1};

    if (n > 0) {
        int overall_min{find_min_dc(arr, low_query, high_query)};
        std::cout << overall_min << std::endl;
    } else {
        std::cout << std::endl;
    }
}
