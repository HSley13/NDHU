#include <iostream>

template <class T>
class Memory {
  public:
    static T **allocArray(int m, int n) {
        T **p = new T *[m];

        T *block = new T[m * n];

        for (int i{0}; i < m; i++)
            p[i] = block + i * n;

        return p;
    }
};

int main(void) {
    int **array = Memory<int>::allocArray(5, 10);

    for (int j{0}; j < 5; j++) {
        for (int k{0}; k < 10; k++)
            array[j][k] = j * 10 + k;
    }

    for (int j{0}; j < 5; j++) {
        for (int k{0}; k < 10; k++)
            std::cout << array[j][k] << " ";
    }

    delete[] array[0];
    delete[] array;
}
