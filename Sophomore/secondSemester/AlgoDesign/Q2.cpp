#include <algorithm>
#include <iostream>
#include <vector>

int maxProfit(std::vector<int> &prices) {
    int n = prices.size();
    if (n <= 1) return 0;

    std::vector<int> hold(n, 0);
    std::vector<int> sold(n, 0);
    std::vector<int> rest(n, 0);

    hold[0] = -prices[0];
    sold[0] = -1; // Represents an impossible state initially
    rest[0] = 0;

    for (int i = 1; i < n; ++i) {
        hold[i] = std::max(hold[i - 1], rest[i - 1] - prices[i]);
        sold[i] = hold[i - 1] + prices[i];
        rest[i] = std::max(rest[i - 1], sold[i - 1]);
    }

    return std::max(sold[n - 1], rest[n - 1]);
}

int main(void) {
    int N;
    std::cin >> N; // Read the number of days

    std::vector<int> prices(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> prices[i]; // Read the stock prices for each day
    }

    std::cout << maxProfit(prices) << std::endl; // Compute and print the maximum profit
}
