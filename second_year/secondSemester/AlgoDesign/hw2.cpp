#include <algorithm>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

typedef double DataType;
std::vector<DataType> given;

struct DataSet {
    size_t begin;
    size_t count;
};

// Function to find top 3 elements (sorted in descending order)
std::vector<DataType> findTopThree(DataSet input) {
    // Base case: return sorted elements if count <= 3
    if (input.count <= 3) {
        std::vector<DataType> result(given.begin() + input.begin,
                                     given.begin() + input.begin + input.count);
        std::sort(result.begin(), result.end(), std::greater<DataType>());
        return result;
    }

    // Divide into 2 subproblems
    const size_t half{input.count / 2};
    DataSet left{input.begin, half};
    DataSet right{input.begin + half, input.count - half};

    // Solve subproblems
    std::vector<DataType> leftTop{findTopThree(left)};
    std::vector<DataType> rightTop{findTopThree(right)};

    // Merge results (only keep top 3)
    std::vector<DataType> combined{};
    combined.reserve(6); // Maximum possible size after merge

    // Merge the two sorted lists (like in merge sort)
    size_t i = 0, j = 0;
    while (i < leftTop.size() && j < rightTop.size() && combined.size() < 3) {
        if (leftTop[i] >= rightTop[j]) {
            combined.push_back(leftTop[i++]);
        } else {
            combined.push_back(rightTop[j++]);
        }
    }

    // Add remaining elements if we don't have 3 yet
    if (combined.size() < 3) {
        while (i < leftTop.size() && combined.size() < 3) {
            combined.push_back(leftTop[i++]);
        }
        while (j < rightTop.size() && combined.size() < 3) {
            combined.push_back(rightTop[j++]);
        }
    }

    return combined;
}

DataType findThirdLargest(DataSet input) {
    if (input.count < 3) {
        throw std::runtime_error("Input must have at least 3 elements");
    }
    std::vector<DataType> topThree{findTopThree(input)};
    return topThree[2];
}

// Function to count element frequencies
std::unordered_map<DataType, int> countFrequencies(DataSet input) {
    std::unordered_map<DataType, int> result{};

    // Base case: single element
    if (input.count == 1) {
        result[given[input.begin]] = 1;
        return result;
    }

    // Base case: empty input
    if (input.count == 0) {
        return result;
    }

    // Divide into 2 subproblems
    const size_t half{input.count / 2};
    DataSet left{input.begin, half};
    DataSet right{input.begin + half, input.count - half};

    // Solve subproblems
    std::unordered_map<DataType, int> leftCounts{countFrequencies(left)};
    std::unordered_map<DataType, int> rightCounts{countFrequencies(right)};

    // Merge results
    for (const std::pair<DataType, int> &pair : rightCounts) {
        leftCounts[pair.first] += pair.second;
    }

    return leftCounts;
}

std::vector<std::pair<DataType, int>> getSortedFrequencies(DataSet input) {
    std::unordered_map<DataType, int> freqMap{countFrequencies(input)};

    std::vector<std::pair<DataType, int>> result(freqMap.begin(), freqMap.end());
    std::sort(result.begin(), result.end());

    return result;
}

// Test function for findThirdLargest
void testThirdLargest() {
    std::cout << "Testing findThirdLargest:\n";
    std::vector<std::vector<DataType>> testCases{{
        {5, 3, 9, 1, 8, 6, 4, 2, 7}, // Normal case
        {9, 9, 8, 8, 7, 7},          // Duplicates
        {1.5, 3.2, 5.7, 2.1},        // Floating point
        {10, 20, 30},                // Exactly 3 elements
    }};

    for (size_t i{0}; i < testCases.size(); i++) {
        given = testCases[i];
        DataSet input{0, given.size()};
        try {
            DataType third{findThirdLargest(input)};
            std::cout << "Test " << i + 1 << ": [";
            for (size_t j{0}; j < given.size(); j++) {
                if (j > 0) std::cout << ", ";
                std::cout << given[j];
            }
            std::cout << "] => 3rd largest = " << third << "\n";
        } catch (const std::exception &e) {
            std::cout << "Test " << i + 1 << " failed: " << e.what() << "\n";
        }
    }
    std::cout << "\n";
}

// Test function for frequency count
void testFrequencyCount() {
    std::cout << "Testing frequency count:\n";
    std::vector<std::vector<DataType>> testCases = {
        {3, 2, 3, 5, 2, 3, 4, 5, 6, 22}, // Original test case
        {1, 1, 1, 1},                    // All same
        {1.1, 2.2, 1.1, 3.3, 2.2},       // Floating point
        {},                              // Empty
        {5}                              // Single element
    };

    for (size_t i{0}; i < testCases.size(); i++) {
        given = testCases[i];
        DataSet input{0, given.size()};
        auto frequencies = getSortedFrequencies(input);

        std::cout << "Test " << i + 1 << ": [";
        for (size_t j{0}; j < given.size(); j++) {
            if (j > 0) std::cout << ", ";
            std::cout << given[j];
        }
        std::cout << "]\n";

        std::cout << "Frequencies:\n";
        for (const std::pair<DataType, int> &pair : frequencies) {
            std::cout << "  " << std::fixed << std::setprecision(2) << pair.first
                      << ": " << pair.second << "\n";
        }
        std::cout << "\n";
    }
}

int main(void) {
    testThirdLargest();
    testFrequencyCount();
}
