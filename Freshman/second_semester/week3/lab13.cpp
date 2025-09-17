#include <iostream>
#include <vector>
#include <algorithm>

class matrix
{
private:
    std::vector<std::vector<int>> matrix;

    int dimension = 0;

public:
    void scan();

    void right();

    void left();

    void print();
};

void matrix::scan()
{
    std::cin >> dimension;

    matrix.resize(dimension, std::vector<int>(dimension));

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
            std::cin >> matrix[i][j];
    }
}

void matrix::right()
{
    if (dimension == 0)
    {
        std::cout << "No element in matrix can be rotated.\n";
        return;
    }

    std::vector<std::vector<int>> tmp;

    tmp.resize(dimension, std::vector<int>(dimension));

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            tmp[i][j] = matrix[dimension - 1 - j][i];
        }
    }
    matrix = tmp;
}

void matrix::left()
{
    if (dimension == 0)
    {
        std::cout << "No element in matrix can be rotated.\n";
        return;
    }

    std::vector<std::vector<int>> tmp;

    tmp.resize(dimension, std::vector<int>(dimension));

    for (int t = 0; t < 3; t++)
    {
        for (int i = 0; i < dimension; i++)
        {
            for (int j = 0; j < dimension; j++)
                tmp[i][j] = matrix[dimension - 1 - j][i];
        }

        matrix = tmp;
    }
}

void matrix::print()
{
    if (dimension == 0)
    {
        std::cout << "No element in matrix can be printed.\n";
        return;
    }

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
            std::cout << matrix[i][j] << " ";

        std::cout << std::endl;
    }

    std::cout << "\n";
}

int main(void)
{
    std::string str;

    matrix _matrix;

    while (true)
    {
        std::cin >> str;

        if (str == "stop")
            return 0;

        else if (str == "rotate")
        {
            std::string str2;

            std::cin >> str2;

            if (str2 == "left")
                _matrix.left();

            else if (str2 == "right")
                _matrix.right();

            else
                std::cout << "unknown\n";
        }

        else if (str == "print")
            _matrix.print();

        else if (str == "scan")
            _matrix.scan();

        else
            std::cout << "unknown\n";
    }
}