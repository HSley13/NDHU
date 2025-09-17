#include <iostream>
#include <vector>

class MineSweeper {
    std::vector<std::vector<char>> _map;
    int _row, _col;

  public:
    MineSweeper() : _row(0), _col(0) {}

    void set_size(int m, int n);

    void get_input();

    int move_and_check(int y, int x);

    void display(int cases);

    bool is_valid(int i, int j) { return i >= 0 && i < _row && j >= 0 && j < _col; }
};

void MineSweeper::set_size(int m, int n) {
    _row = m;
    _col = n;
    _map.assign(_row, std::vector<char>(_col));
}

void MineSweeper::get_input() {
    for (int i = 0; i < _row; i++) {
        for (int j = 0; j < _col; j++)
            std::cin >> _map[i][j];
    }
}

int MineSweeper::move_and_check(int y, int x) {
    int count = 0;
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            if (is_valid(i, j) && _map[i][j] == '*')
                count++;
        }
    }

    return count;
}

void MineSweeper::display(int cases) {
    if (cases > 1)
        std::cout << std::endl;

    std::cout << "Field #" << cases << ":" << std::endl;

    for (int i = 0; i < _row; i++) {
        for (int j = 0; j < _col; j++) {
            if (_map[i][j] == '*')
                std::cout << '*';
            else
                std::cout << move_and_check(i, j);
        }

        std::cout << std::endl;
    }
}

int main(void) {
    MineSweeper sweeper;
    int n, m, cases = 0;

    while (std::cin >> n >> m && (n + m)) {
        sweeper.set_size(n, m);
        sweeper.get_input();
        sweeper.display(++cases);
    }
}
