#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

#define SIZE 10

class Node {
  public:
    Node() : row(0), col(0) {}

    Node(int r, int c) : row(r), col(c) {}

    int getRow() {
        return row;
    }

    int getCol() {
        return col;
    }

    void setRow(int r) {
        if (r >= 0 && r < SIZE) {
            row = r;
        }
    }

    void setCol(int c) {
        if (c >= 0 && c < SIZE) {
            col = c;
        }
    }

  private:
    int row, col;
};

class List {
  public:
    List() {
        top = 0;
    }

    void addElement(int r, int c) {
        if (top < SIZE * SIZE) {
            data[top++] = std::make_unique<Node>(r, c);
        }
    }

    void removeElement() {
        if (top == 0) {
            return;
        }
        top--;
    }

    void printList() const {
        for (int i{0}; i < top; i++) {
            std::cout << "(" << data[i]->getRow() << ", " << data[i]->getCol() << ")" << std::endl;
        }
    }

  private:
    std::unique_ptr<Node> data[SIZE * SIZE];
    int top;
};

class Maze {
  public:
    Maze() {
        std::srand(std::time(0));
        initMaze(SIZE);
    }

    void initMaze(int s) {
        maze = std::make_unique<std::unique_ptr<int[]>[]>(s);

        for (int i{0}; i < s; i++) {
            maze[i] = std::make_unique<int[]>(s);
            for (int j{0}; j < s; j++) {
                maze[i][j] = (std::rand() % 100 < 20) ? 1 : 0;
            }
        }

        maze[0][0] = 0;
        maze[s - 1][s - 1] = 0;
    }

    std::unique_ptr<List> getPath() {
        std::unique_ptr<List> path = std::make_unique<List>();
        std::unique_ptr<std::unique_ptr<bool[]>[]> visited{std::make_unique<std::unique_ptr<bool[]>[]>(SIZE)};

        for (int i{0}; i < SIZE; i++) {
            visited[i] = std::make_unique<bool[]>(SIZE);
        }

        if (findPath(0, 0, path.get(), visited)) {
            return path;
        }

        return std::make_unique<List>();
    }

    bool findPath(int r, int c, List *path, std::unique_ptr<std::unique_ptr<bool[]>[]> &visited) {
        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE || maze[r][c] == 1 || visited[r][c]) {
            return false;
        }

        visited[r][c] = true;
        path->addElement(r, c);

        if (r == SIZE - 1 && c == SIZE - 1) {
            return true;
        }

        if (findPath(r, c + 1, path, visited) || findPath(r, c - 1, path, visited) || findPath(r + 1, c, path, visited) || findPath(r - 1, c, path, visited)) {
            return true;
        }

        path->removeElement();
        return false;
    }

    void printMaze() const {
        for (int i{0}; i < SIZE; i++) {
            for (int j{0}; j < SIZE; j++) {
                if (maze[i][j] == 0) {
                    std::cout << " ";
                } else if (maze[i][j] == 1) {
                    std::cout << "*";
                }
            }
            std::cout << std::endl;
        }
    }

  private:
    std::unique_ptr<std::unique_ptr<int[]>[]> maze;
};

int main(void) {
    Maze maze;
    maze.printMaze();
    std::unique_ptr<List> path = maze.getPath();
    path->printList();
}
