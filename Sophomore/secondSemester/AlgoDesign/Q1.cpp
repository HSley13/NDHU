#include <algorithm>
#include <iostream>
#include <vector>

int calculateMinPathSum(const std::vector<std::vector<int>> &triangle) {
    int N = triangle.size();
    if (N == 0) return 0;

    std::vector<std::vector<int>> dp(N, std::vector<int>(N, 0));
    dp[0][0] = triangle[0][0];

    for (int i{1}; i < N; i++) {
        // Left edge
        dp[i][0] = dp[i - 1][0] + triangle[i][0];

        // Middle elements
        for (int j{1}; j < i; j++) {
            dp[i][j] = std::min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
        }

        // Right edge
        dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
    }

    return *std::min_element(dp.back().begin(), dp.back().end());
}

int main(void) {
    int N;
    std::cin >> N;

    std::vector<std::vector<int>> triangle(N);
    for (int i{0}; i < N; i++) {
        triangle[i].resize(i + 1);
        for (int j{0}; j <= i; j++) {
            std::cin >> triangle[i][j];
        }
    }

    std::cout << calculateMinPathSum(triangle) << std::endl;
}
