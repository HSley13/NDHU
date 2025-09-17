#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define size 100
int matrix[size][size] = {{0}};
int visited[size][size] = {{0}};

bool is_valid(int x, int y, int row, int column)
{
    return (x >= 0 && x < row && y >= 0 && y < column && !visited[x][y]);
}

void clockwise_spiral_order(int row, int column)
{
    int x = 0, y = 0;
    int direction = 6; 
    // 6 for right; 8 for down; 4 for left and 2 for up

    for (int i = 0; i < row * column; i++)
    {
        printf("%d ", matrix[x][y]);
        visited[x][y] = 1;

        switch (direction)
        {
            case 6:
            if (is_valid(x, y + 1, row, column)) y++;
            else 
            {
                direction = 8;
                x++;
            }
            break;

            case 8:
            if (is_valid(x + 1, y, row, column)) x++;
            else 
            {
                direction = 4;
                y--;
            }
            break;

            case 4:
            if (is_valid(x, y - 1, row, column)) y--;
            else 
            {
                direction = 2;                 
                x--;
            }
            break;

            case 2:
            if (is_valid(x - 1, y, row, column)) x--;
            else 
            {
                direction = 6;
                y++;
            }
            break;
        }
    }  
}

int main(void)
{
    int rows, columns;
    scanf("%d %d", &rows, &columns);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++) scanf("%d", &matrix[i][j]);
    }

    clockwise_spiral_order(rows, columns);
}