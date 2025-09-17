#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

void generateMagicSquare(int size) {
    if (size < 1 || size >= 51 || size % 2 == 0) {
        throw std::runtime_error("Error!.. size out of range or even!");
    }

    std::vector<std::vector<int>> magicSquare(size, std::vector<int>(size, 0));
    int row = 0;
    int col = size / 2;
    int num = 1;

    while (num <= size * size) {
        magicSquare[row][col] = num;
        num++;

        int nextRow = (row == 0) ? size - 1 : row - 1;
        int nextCol = (col == 0) ? size - 1 : col - 1;

        if (magicSquare[nextRow][nextCol] != 0) {
            row = (row + 1) % size;
        } else {
            row = nextRow;
            col = nextCol;
        }
    }

    std::cout << "Magic Square of size " << size << ":\n";
    for (const std::vector<int> &rowData : magicSquare) {
        std::copy(rowData.begin(), rowData.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
}

double measureExecutionTime(int size, int iterations) {
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < iterations; i++) {
        generateMagicSquare(size);
    }

    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(endTime - startTime).count();
}

void performMagicSquareAnalysis() {
    std::ofstream analysisFile("magic_square_analysis.txt"), csvFile("magic_square_data.csv");
    analysisFile << "Magic Square Analysis\n";
    csvFile << "Size,Iterations,Total Time (s),Average Time (s)\n";

    std::array<int, 5> sizes{11, 21, 31, 41, 51};
    for (const int &size : sizes) {
        analysisFile << "Size: " << size << "\nIterations\tTotal Time (s)\tAverage Time (s)\n";
        for (int iterations = 10; iterations <= 100; iterations += 10) {
            double totalTime = measureExecutionTime(size, iterations);
            double averageTime = totalTime / iterations;
            analysisFile << iterations << "\t" << totalTime << "\t" << averageTime << "\n";
            csvFile << size << "," << iterations << "," << totalTime << "," << averageTime << "\n";
        }
    }
}

void displayAnalysisResults() {
    std::ifstream analysisFile("magic_square_analysis.txt");
    if (!analysisFile) {
        throw std::runtime_error("Analysis file not found");
    }

    std::cout << analysisFile.rdbuf();
}

int main(void) {
    try {
        performMagicSquareAnalysis();
        displayAnalysisResults();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
