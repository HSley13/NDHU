#include <iostream>
#include <unordered_set>
#include <vector>

// 1. Naive Recursive Fibonacci
int fib_recursive(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

// 2. Top-Down DP with Memoization
int fib_memo(int n, std::vector<int> &memo) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (memo[n] != -1) return memo[n];
    memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo);
    return memo[n];
}

int fib_top_down(int n) {
    std::vector<int> memo(n + 1, -1);
    return fib_memo(n, memo);
}

// 3. Bottom-Up DP
int fib_bottom_up(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    std::vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;

    for (int i{2}; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

// 4. Space-Optimized DP
int fib_optimized(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    int a{0}, b{1}, c;
    for (int i{2}; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// Fixed Basketball Points
int basketball_points(int n) {
    if (n <= 1) return 0;

    std::vector<int> dp(n + 1, 0);
    dp[0] = 1; // Base case

    for (int i{2}; i <= n; ++i) {
        if (i >= 2) dp[i] += dp[i - 2];
        if (i >= 3) dp[i] += dp[i - 3];
    }

    return dp[n];
}

// Fixed Broken Stairs
int climb_stairs_broken(int n, const std::vector<int> &broken) {
    std::unordered_set<int> broken_steps{broken.begin(), broken.end()};

    if (broken_steps.count(0) || broken_steps.count(1)) return 0;

    std::vector<int> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = 1;

    for (int i{2}; i <= n; ++i) {
        if (broken_steps.count(i)) {
            dp[i] = 0;
            continue;
        }
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

// Question 5: Coin Change with Rolling Table
int coin_change_rolling(const std::vector<int> &C, int m) {
    std::vector<std::vector<int>> dp(2, std::vector<int>(m + 1, 0));

    dp[0][0] = 1;
    dp[1][0] = 1;

    for (int im{1}; im <= m; ++im) {
        dp[0][im] = (im % C[0] == 0) ? 1 : 0;
    }

    for (int ik{1}; ik < C.size(); ++ik) {
        int curr{ik % 2};
        int prev{(ik - 1) % 2};

        for (int im{1}; im <= m; ++im) {
            dp[curr][im] = dp[prev][im];
            if (im >= C[ik]) {
                dp[curr][im] += dp[curr][im - C[ik]];
            }
        }
    }

    return dp[(C.size() - 1) % 2][m];
}

// Optimized Coin Change
int coin_change_optimized(const std::vector<int> &C, int m) {
    std::vector<int> dp(m + 1, 0);
    dp[0] = 1;

    for (int coin : C) {
        for (int im{coin}; im <= m; ++im) {
            dp[im] += dp[im - coin];
        }
    }

    return dp[m];
}

int main(void) {
    // Test Fibonacci implementations
    std::cout << "=== Fibonacci Tests ===" << std::endl;
    std::cout << "Recursive F(10): " << fib_recursive(10) << std::endl;
    std::cout << "Top-Down F(10): " << fib_top_down(10) << std::endl;
    std::cout << "Bottom-Up F(10): " << fib_bottom_up(10) << std::endl;
    std::cout << "Optimized F(10): " << fib_optimized(10) << std::endl;

    // Test Basketball Points
    std::cout << "\n=== Basketball Points Tests ===" << std::endl;
    std::cout << "Ways to score 5 points: " << basketball_points(5) << " (Expected: 2)" << std::endl;
    std::cout << "Ways to score 6 points: " << basketball_points(6) << " (Expected: 3)" << std::endl;
    std::cout << "Ways to score 10 points: " << basketball_points(10) << " (Expected: 7)" << std::endl;

    // Test Broken Stairs
    std::cout << "\n=== Broken Stairs Tests ===" << std::endl;
    std::vector<int> broken1{2, 4};
    std::cout << "Ways to climb 5 stairs with [2,4] broken: "
              << climb_stairs_broken(5, broken1) << " (Expected: 2)" << std::endl;

    std::vector<int> broken2{1};
    std::cout << "Ways to climb 5 stairs with [1] broken: "
              << climb_stairs_broken(5, broken2) << " (Expected: 0)" << std::endl;

    // Test Coin Change
    std::cout << "\n=== Coin Change Tests ===" << std::endl;
    std::vector<int> coins1{1, 2, 5};
    std::cout << "Ways to make 5 with [1,2,5]: "
              << coin_change_rolling(coins1, 5) << " (Expected: 4)" << std::endl;
    std::cout << "Optimized version: "
              << coin_change_optimized(coins1, 5) << " (Expected: 4)" << std::endl;

    std::vector<int> coins2{2, 3, 5};
    std::cout << "Ways to make 8 with [2,3,5]: "
              << coin_change_rolling(coins2, 8) << " (Expected: 3)" << std::endl;
    std::cout << "Optimized version: "
              << coin_change_optimized(coins2, 8) << " (Expected: 3)" << std::endl;
}
