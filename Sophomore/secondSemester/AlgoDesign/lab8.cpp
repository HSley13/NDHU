#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

// ----------------- FIBONACCI ------------------
std::map<int, long long> memo;

long long fib_memoization(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (memo.count(n)) return memo[n];
    memo[n] = fib_memoization(n - 1) + fib_memoization(n - 2);
    return memo[n];
}

long long fib_tabulation(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    std::vector<long long> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; ++i)
        dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}

// ----------------- CLIMBING STAIRS (1,2,3 steps) ------------------
long long count_ways_to_climb(int n) {
    if (n < 0) return 0;
    std::vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        if (i >= 1) dp[i] += dp[i - 1];
        if (i >= 2) dp[i] += dp[i - 2];
        if (i >= 3) dp[i] += dp[i - 3];
    }
    return dp[n];
}

// ----------------- LONGEST INCREASING SUBSEQUENCE ------------------
int longest_increasing_subsequence(const std::vector<int> &nums) {
    int n = nums.size();
    if (n == 0) return 0;
    std::vector<int> dp(n, 1);
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
    }
    return *std::max_element(dp.begin(), dp.end());
}

// ----------------- MAIN FUNCTION TO TEST EVERYTHING ------------------
int main() {
    using namespace std;
    cout << "--- Fibonacci Tests ---" << endl;
    cout << "fib_tabulation(7): " << fib_tabulation(7) << endl; // Expected: 13
    memo.clear();
    cout << "fib_memoization(7): " << fib_memoization(7) << endl; // Expected: 13

    cout << "\n--- Climbing Stairs (1,2,3 steps) Tests ---" << endl;
    for (int i = 0; i <= 5; ++i) {
        cout << "Ways to climb " << i << " stairs: " << count_ways_to_climb(i) << endl;
    }

    cout << "\n--- LIS Tests ---" << endl;
    vector<vector<int>> test_cases = {
        {10, 9, 2, 5, 3, 7, 101, 18},
        {0, 1, 0, 3, 2, 3},
        {7, 7, 7, 7, 7},
        {3, 10, 2, 1, 20},
        {}};
    for (const auto &tc : test_cases) {
        cout << "LIS length for { ";
        for (int x : tc) cout << x << " ";
        cout << "}: " << longest_increasing_subsequence(tc) << endl;
    }
    return 0;
}
