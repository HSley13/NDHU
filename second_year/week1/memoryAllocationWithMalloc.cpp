#include <stdio.h>
#include <stdlib.h>

void allocArray(int ***p, int m, int n) {
    *p = (int **)malloc(m * sizeof(int *));

    (*p)[0] = (int *)malloc(m * n * sizeof(int));

    for (int i = 0; i < m; i++)
        (*p)[i] = (*p)[0] + i * n;
}

int main(void) {
    int **array;

    allocArray(&array, 5, 10);

    for (int j = 0; j < 5; j++) {
        for (int k = 0; k < 10; k++)
            array[j][k] = j * 10 + k;
    }

    for (int j = 0; j < 5; j++) {
        for (int k = 0; k < 10; k++)
            printf("%p ", (void *)&(array[j][k]));
    }

    free(array[0]);
    free(array);
}
