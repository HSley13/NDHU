#include <array>
#include <iostream>

static const int N = 4;

class SudokuSolver {
  public:
    SudokuSolver(const std::array<std::array<int, N>, N> &initialBoard) {
        board = initialBoard;
    }

    void printBoard() const {
        for (int i{0}; i < N; i++) {
            for (int j{0}; j < N; j++) {
                std::cout << board[i][j];
                if (j < N - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    bool isValid(int row, int col, int num) const {
        for (int x{0}; x < N; x++) {
            if (board[row][x] == num) {
                return false;
            }
        }

        for (int x{0}; x < N; x++) {
            if (board[x][col] == num) {
                return false;
            }
        }

        int startRow = row - row % 2;
        int startCol = col - col % 2;
        for (int i{0}; i < 2; i++) {
            for (int j{0}; j < 2; j++) {
                if (board[i + startRow][j + startCol] == num) {
                    return false;
                }
            }
        }
        return true;
    }

    bool solve() {
        int row = -1, col = -1;
        bool isEmpty = false;

        for (int i{0}; i < N; i++) {
            for (int j{0}; j < N; j++) {
                if (board[i][j] == 0) {
                    row = i;
                    col = j;
                    isEmpty = true;
                    break;
                }
            }
            if (isEmpty) {
                break;
            }
        }

        if (!isEmpty) {
            return true;
        }

        for (int num{1}; num <= N; num++) {
            if (isValid(row, col, num)) {
                board[row][col] = num;
                printBoard();

                if (solve()) {
                    return true;
                }

                board[row][col] = 0;
            }
        }
        return false;
    }

  private:
    std::array<std::array<int, N>, N> board;
};

int main(void) {
    std::array<std::array<int, N>, N> initialBoard;
    for (int i{0}; i < N; i++) {
        for (int j{0}; j < N; j++) {
            std::cin >> initialBoard[i][j];
        }
    }

    SudokuSolver solver(initialBoard);

    if (solver.solve()) {
        solver.printBoard();
    } else {
        std::cout << "No solution exists." << std::endl;
    }
}
