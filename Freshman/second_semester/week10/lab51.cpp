#include <iostream>
#include <vector>

class Grid {
    std::vector<std::vector<char>> _grid;
    int _row, _col;

  public:
    Grid() : _row(0), _col(0) {}

    void set_size(int heigh, int width);

    void get_input();

    bool is_valid(int row, int col, int side_len);

    int get_dimension();
};

void Grid::set_size(int heigh, int width) {
    this->_row = heigh;
    this->_col = width;
    this->_grid.assign(this->_row, std::vector<char>(this->_col));
}

void Grid::get_input() {
    for (int i = 0; i < this->_row; i++)
        for (int j = 0; j < this->_col; j++)
            std::cin >> this->_grid[i][j];
}

bool Grid::is_valid(int row, int col, int side_len) {
    char ch = this->_grid[row][col];
    int half = side_len / 2;

    for (int i = row - half; i <= row + half; i++) {
        for (int j = col - half; j <= col + half; j++) {
            if (i < 0 || i >= this->_row || j < 0 || j >= this->_col || this->_grid[i][j] != ch)
                return false;
        }
    }

    return true;
}

int Grid::get_dimension() {
    int row, col;
    std::cin >> row >> col;

    int max_length = 1;
    int side_length = 1;

    while (true) {
        int half = side_length / 2;

        if (row - half < 0 || row + half >= this->_row || col - half < 0 || col + half >= this->_col || !is_valid(row, col, side_length))
            break;

        max_length = side_length;
        side_length += 2;
    }

    return max_length;
}

int main(void) {
    int test_case, heigh, width, Q;

    std::cin >> test_case;

    while (test_case--) {
        std::cin >> heigh >> width >> Q;
        Grid grid;

        grid.set_size(heigh, width);
        grid.get_input();

        std::cout << heigh << " " << width << " " << Q << std::endl;

        while (Q--)
            std::cout << grid.get_dimension() << std::endl;
    }
}
