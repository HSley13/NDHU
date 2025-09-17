#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

// Bottom-up DP implementation
int knapsack_bottom_up(int W, const std::vector<int> &wt, const std::vector<int> &val, int n) {
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (wt[i - 1] <= w) {
                dp[i][w] = std::max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][W];
}

// Top-down DP with memoization
int knapsack_top_down_util(int W, const std::vector<int> &wt, const std::vector<int> &val, int n, std::vector<std::vector<int>> &memo) {
    if (n == 0 || W == 0) return 0;
    if (memo[n][W] != -1) return memo[n][W];

    if (wt[n - 1] > W) {
        memo[n][W] = knapsack_top_down_util(W, wt, val, n - 1, memo);
    } else {
        memo[n][W] = std::max(
            val[n - 1] + knapsack_top_down_util(W - wt[n - 1], wt, val, n - 1, memo),
            knapsack_top_down_util(W, wt, val, n - 1, memo));
    }
    return memo[n][W];
}

int knapsack_top_down(int W, const std::vector<int> &wt, const std::vector<int> &val, int n) {
    std::vector<std::vector<int>> memo(n + 1, std::vector<int>(W + 1, -1));
    return knapsack_top_down_util(W, wt, val, n, memo);
}

// Greedy approach based on value/weight ratio
int knapsack_greedy(int W, const std::vector<int> &wt, const std::vector<int> &val, int n) {
    std::vector<std::pair<double, int>> items;
    for (int i = 0; i < n; i++) {
        items.push_back({(double)val[i] / wt[i], i});
    }

    sort(items.rbegin(), items.rend()); // Sort descending by value/weight ratio

    int total_value = 0;
    int remaining = W;

    for (const std::pair<double, int> &item : items) {
        int idx = item.second;
        if (wt[idx] <= remaining) {
            total_value += val[idx];
            remaining -= wt[idx];
        }
        if (remaining == 0) break;
    }
    return total_value;
}

// Helper function to generate test cases
void generate_test_case(int n, int min_w, int max_w, double correlation, std::vector<int> &weights, std::vector<int> &values) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> weight_dist(min_w, max_w);
    std::normal_distribution<> noise_dist(0, max_w / 10.0);

    weights.resize(n);
    values.resize(n);

    for (int i = 0; i < n; i++) {
        weights[i] = weight_dist(gen);
        // Values correlated with weights plus some noise
        values[i] = std::max(1, (int)(weights[i] * correlation + abs(noise_dist(gen))));
    }
}

// Function to run and time a knapsack algorithm
template <typename Func>
void run_test(const std::string &name, Func knapsack_func, int W, const std::vector<int> &wt, const std::vector<int> &val, int n) {
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    int result = knapsack_func(W, wt, val, n);
    std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << std::setw(15) << name << ": "
              << std::setw(10) << result << " | Time: "
              << std::setw(8) << duration.count() << " μs" << std::endl;
}

int main(void) {
    std::vector<std::tuple<int, int, int, double, int>> test_cases = {
        {10, 1, 10, 0.7, 30},     // Small problem, small weights
        {20, 1, 10, 0.7, 50},     // Medium problem, small weights
        {30, 1, 10, 0.7, 75},     // Larger problem, small weights
        {20, 1, 100, 0.5, 200},   // Medium problem, medium weights
        {20, 1, 1000, 0.3, 2000}, // Medium problem, large weights
        {15, 10, 10, 0.9, 75}     // All weights equal
    };

    std::cout << "Knapsack Problem Algorithm Comparison\n";
    std::cout << "====================================\n\n";

    for (const auto &test_case : test_cases) {
        int n = std::get<0>(test_case);
        int min_w = std::get<1>(test_case);
        int max_w = std::get<2>(test_case);
        double corr = std::get<3>(test_case);
        int W = std::get<4>(test_case);

        std::vector<int> weights, values;
        generate_test_case(n, min_w, max_w, corr, weights, values);

        std::cout << "\nTest Case: n=" << n
                  << ", weight_range=[" << min_w << "-" << max_w << "]"
                  << ", correlation=" << corr
                  << ", W=" << W << "\n";
        std::cout << std::string(60, '-') << "\n";

        // Run all algorithms
        run_test("Bottom-up DP", knapsack_bottom_up, W, weights, values, n);
        run_test("Top-down DP", knapsack_top_down, W, weights, values, n);
        run_test("Greedy", knapsack_greedy, W, weights, values, n);

        // Calculate approximation ratio
        int dp_result = knapsack_bottom_up(W, weights, values, n);
        int greedy_result = knapsack_greedy(W, weights, values, n);
        double approx_ratio = (dp_result == 0) ? 1.0 : (double)dp_result / greedy_result;

        std::cout << "\nApproximation Ratio (DP/Greedy): " << std::fixed << std::setprecision(2) << approx_ratio << "\n";
    }
}
