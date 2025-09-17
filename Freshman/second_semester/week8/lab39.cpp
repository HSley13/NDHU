#include <algorithm>
#include <iostream>
#include <vector>

class train_manager {
  private:
    std::vector<int> weights;

  public:
    void car_weight(int N);

    int longest_train() const;

    void reset() { weights.clear(); }
};

void train_manager::car_weight(int N) {
    weights.resize(N);

    for (int i = 0; i < weights.size(); i++)
        std::cin >> weights[i];
}

int train_manager::longest_train() const {
    if (weights.size() == 0)
        return 0;

    std::vector<int> LIS, LDS;
    int max_len = 0;

    for (int i = weights.size() - 1; i >= 0; --i) {
        int LDS_length, LIS_length;

        std::vector<int>::iterator it = std::lower_bound(LDS.begin(), LDS.end(), weights[i]);

        if (it == LDS.end()) {
            LDS.push_back(weights[i]);

            LIS_length = LDS.size();
        } else {
            *it = weights[i];
            LIS_length = it - LDS.begin() + 1;
        }

        it = std::lower_bound(LIS.begin(), LIS.end(), -weights[i]);
        if (it == LIS.end()) {
            LIS.push_back(-weights[i]);

            LDS_length = LIS.size();
        } else {
            *it = -weights[i];
            LDS_length = it - LIS.begin() + 1;
        }

        max_len = std::max(max_len, LDS_length + LIS_length - 1);
    }

    return max_len;
}

int main(void) {
    train_manager manager;
    int test_cases = 0;

    std::cin >> test_cases;

    while (--test_cases >= 0) {
        int N;
        std::cin >> N;

        manager.car_weight(N);

        std::cout << manager.longest_train() << std::endl;
        manager.reset();
    }
}
