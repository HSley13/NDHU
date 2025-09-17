#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define size 100

int main(void)
{
    int arr[size][size] = {{0}};

    int rows, columns, nonZeroVal;
    scanf("%d %d %d", &rows, &columns, &nonZeroVal);

    int row, col, val;
    for(int i = 0; i < nonZeroVal; i++)
    {
        scanf("%d %d %d", &row, &col, &val);
        arr[row][col] = val;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++) printf("%d ", arr[i][j]);
        
        printf("\n");
    }
}