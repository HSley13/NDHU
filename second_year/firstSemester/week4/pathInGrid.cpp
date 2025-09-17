#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Grid {
  public:
    Grid() : state(0), visited(false) {
        for (int i{0}; i < 4; i++) {
            dir[i] = nullptr;
        }
    }

    explicit Grid(int s) : state(s), visited(false) {
        for (int i{0}; i < 4; i++) {
            dir[i] = nullptr;
        }
    }

    Grid(const Grid &) = delete;
    Grid &operator=(const Grid &) = delete;

    std::shared_ptr<Grid> getDir(int d) const {
        return dir[d];
    }

    int getState() const {
        return state;
    }

    void setDir(int d, std::shared_ptr<Grid> g) {
        dir[d] = g;
    }

    void setState(int s) {
        state = s;
    }

    bool isVisited() const {
        return visited;
    }

    void setVisited(bool v) {
        visited = v;
    }

  private:
    std::shared_ptr<Grid> dir[4];
    int state;
    bool visited;
};

class List {
  public:
    List() : top(0) {}

    void addElement(std::shared_ptr<Grid> g) {
        if (top < SIZE * SIZE) {
            data[top++] = g;
        }
    }

    std::shared_ptr<Grid> removeElement() {
        if (top == 0) {
            return nullptr;
        }
        return data[--top];
    }

    void printPath() const {
        for (int j = 1; j < top; j++) {
            if (data[j] == data[j - 1]->getDir(UP)) {
                std::cout << "UP" << std::endl;
            } else if (data[j] == data[j - 1]->getDir(DOWN)) {
                std::cout << "DOWN" << std::endl;
            } else if (data[j] == data[j - 1]->getDir(LEFT)) {
                std::cout << "LEFT" << std::endl;
            } else if (data[j] == data[j - 1]->getDir(RIGHT)) {
                std::cout << "RIGHT" << std::endl;
            }
        }
    }

  private:
    std::shared_ptr<Grid> data[SIZE * SIZE];
    int top;
};

class Maze {
  public:
    Maze() {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        initMaze(SIZE);
    }

    void initMaze(int s) {
        maze = std::make_shared<Grid>(0);
        std::shared_ptr<Grid> currentRow = maze;

        for (int i{0}; i < s; i++) {
            std::shared_ptr<Grid> current = currentRow;
            for (int j{0}; j < s; j++) {
                if (i == 0 && j == 0)
                    continue;

                std::shared_ptr<Grid> newGrid = std::make_shared<Grid>(0);

                if (std::rand() % 100 < 20 && !(i == s - 1 && j == s - 1)) {
                    newGrid->setState(1);
                }

                if (j > 0) {
                    current->setDir(RIGHT, newGrid);
                    newGrid->setDir(LEFT, current);
                }
                current = newGrid;
            }

            if (i < s - 1) {
                std::shared_ptr<Grid> newRow = std::make_shared<Grid>(0);

                currentRow->setDir(DOWN, newRow);
                newRow->setDir(UP, currentRow);

                currentRow = newRow;
            }
        }
    }

    bool findPath(std::shared_ptr<Grid> current, std::shared_ptr<List> path) {
        if (!current || current->getState() == 1 || current->isVisited())
            return false;

        current->setVisited(true);
        path->addElement(current);

        if (!current->getDir(DOWN) && !current->getDir(RIGHT) && !current->getDir(LEFT) && !current->getDir(UP))
            return true;

        if (findPath(current->getDir(RIGHT), path) ||
            findPath(current->getDir(DOWN), path) ||
            findPath(current->getDir(LEFT), path) ||
            findPath(current->getDir(UP), path)) {
            return true;
        }

        path->removeElement();
        return false;
    }

    std::shared_ptr<List> getPath() {
        std::shared_ptr<List> path = std::make_shared<List>();
        if (findPath(maze, path)) {
            return path;
        }
        return std::make_shared<List>();
    }

    void printMaze() const {
        std::shared_ptr<Grid> row{maze};
        std::shared_ptr<Grid> col;

        while (row) {
            col = row;
            while (col) {
                std::cout << (col->getState() == 1 ? "#" : ".");
                col = col->getDir(RIGHT);
            }
            std::cout << std::endl;
            row = row->getDir(DOWN);
        }
    }

  private:
    std::shared_ptr<Grid> maze;
};

int main(void) {
    std::shared_ptr<Maze> maze{std::make_shared<Maze>()};
    maze->printMaze();

    std::shared_ptr<List> path{maze->getPath()};
    if (path->removeElement()) {
        std::cout << "Path found:" << std::endl;
        path->printPath();
    } else {
        std::cout << "No path found." << std::endl;
    }
}
