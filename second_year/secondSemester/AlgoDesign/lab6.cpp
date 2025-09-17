#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

// 0/1 Knapsack - Space Optimized
int knapsack01(int n, int W, const std::vector<int> &weights, const std::vector<int> &values) {
    std::vector<int> dp(W + 1, 0);

    for (int i{1}; i <= n; i++) {
        for (int w{W}; w >= weights[i - 1]; --w) {
            dp[w] = std::max(dp[w], dp[w - weights[i - 1]] + values[i - 1]);
        }
    }

    return dp[W];
}

// Unbounded Knapsack with reconstruction
std::pair<int, std::vector<int>> unboundedKnapsack(int n, int W, const std::vector<int> &weights, const std::vector<int> &values) {
    std::vector<int> dp(W + 1, 0);

    for (int w{1}; w <= W; w++) {
        for (int i{0}; i < n; i++) {
            if (weights[i] <= w) {
                dp[w] = std::max(dp[w], dp[w - weights[i]] + values[i]);
            }
        }
    }

    // Reconstruction
    std::vector<int> items(n, 0);
    int remaining{W};
    while (remaining > 0) {
        bool found{false};
        for (int i{0}; i < n; i++) {
            if (weights[i] <= remaining &&
                dp[remaining] == dp[remaining - weights[i]] + values[i]) {
                items[i]++;
                remaining -= weights[i];
                found = true;
                break;
            }
        }
        if (!found) break;
    }

    return {dp[W], items};
}

// Bounded Knapsack with binary optimization
int boundedKnapsack(int n, int W, const std::vector<int> &weights, const std::vector<int> &values, const std::vector<int> &counts) {
    std::vector<int> dp(W + 1, 0);

    for (int i{0}; i < n; i++) {
        int w{weights[i]};
        int v{values[i]};
        int c{counts[i]};

        // Binary optimization
        int k{1};
        while (k <= c) {
            int current_weight{k * w};
            int current_value{k * v};
            for (int w_curr{W}; w_curr >= current_weight; w_curr--) {
                dp[w_curr] = std::max(dp[w_curr], dp[w_curr - current_weight] + current_value);
            }
            c -= k;
            k *= 2;
        }

        // Handle remaining count
        if (c > 0) {
            int current_weight{c * w};
            int current_value{c * v};
            for (int w_curr{W}; w_curr >= current_weight; --w_curr) {
                dp[w_curr] = std::max(dp[w_curr], dp[w_curr - current_weight] + current_value);
            }
        }
    }

    return dp[W];
}

int main(void) {
    std::cout << "=== 0/1 Knapsack Test Cases ===" << std::endl;
    {
        std::vector<int> weights{1, 3, 4, 5};
        std::vector<int> values{1, 4, 5, 7};
        int W{7};
        int n{static_cast<int>(weights.size())};

        int result{knapsack01(n, W, weights, values)};
        std::cout << "Test Case 1 - Expected: 9, Actual: " << result << std::endl;
    }
    {
        std::vector<int> weights{10, 20, 30};
        std::vector<int> values{60, 100, 120};
        int W{50};
        int n{static_cast<int>(weights.size())};

        int result{knapsack01(n, W, weights, values)};
        std::cout << "Test Case 2 - Expected: 220, Actual: " << result << std::endl;
    }

    std::cout << "\n=== Unbounded Knapsack Test Cases ===" << std::endl;
    {
        std::vector<int> weights{1, 3, 4, 5};
        std::vector<int> values{10, 40, 50, 70};
        int W{8};
        int n{static_cast<int>(weights.size())};

        auto result{unboundedKnapsack(n, W, weights, values)};
        std::cout << "Test Case 1 - Max Value: " << result.first << std::endl;
        std::cout << "Item counts: ";
        for (int count : result.second) {
            std::cout << count << " ";
        }
        std::cout << std::endl;
    }
    {
        std::vector<int> weights{2, 3, 5};
        std::vector<int> values{50, 100, 140};
        int W{17};
        int n{static_cast<int>(weights.size())};

        auto result{unboundedKnapsack(n, W, weights, values)};
        std::cout << "Test Case 2 - Max Value: " << result.first << std::endl;
        std::cout << "Item counts: ";
        for (int count : result.second) {
            std::cout << count << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\n=== Bounded Knapsack Test Cases ===" << std::endl;
    {
        std::vector<int> weights{1, 3, 4, 5};
        std::vector<int> values{1, 4, 5, 7};
        std::vector<int> counts{2, 1, 3, 2};
        int W{7};
        int n{static_cast<int>(weights.size())};

        int result{boundedKnapsack(n, W, weights, values, counts)};
        std::cout << "Test Case 1 - Expected: 9, Actual: " << result << std::endl;
    }
    {
        std::vector<int> weights{10, 20, 30};
        std::vector<int> values{60, 100, 120};
        std::vector<int> counts{2, 3, 1};
        int W{50};
        int n{static_cast<int>(weights.size())};

        int result{boundedKnapsack(n, W, weights, values, counts)};
        std::cout << "Test Case 2 - Expected: 300, Actual: " << result << std::endl;
    }
}
