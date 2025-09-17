#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_ROWS 100
#define MAX_COLS 100

int rows = 0, cols = 0;

bool in_range(int new_row, int new_column)
{
  return (new_row >= 0 && new_row < rows && new_column >= 0 && new_column < cols);
}

void simulated_round(char matrix[MAX_ROWS][MAX_COLS], char new_matrix[MAX_ROWS][MAX_COLS])
{
    int directions[8][2] =
    {
        {-1, -1},{-1, 0}, {-1, 1},        
        {0, -1},          {0, 1},
        {1, -1}, {1, 0},  {1, 1}
    };

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int live_neighbors = 0;

            for (int k = 0; k < 8; k++)
            {
                int new_row = i + directions[k][0];
                int new_column = j + directions[k][1];

                if (in_range(new_row, new_column) && matrix[new_row][new_column] == '1') live_neighbors++;
            }

            if (matrix[i][j] == '1')
            {
                if (live_neighbors < 2 || live_neighbors > 3) new_matrix[i][j] = '0';

                else new_matrix[i][j] = '1';
            }

            else 
            {
                if (live_neighbors == 3) new_matrix[i][j] = '1';

                else new_matrix[i][j] = '0';
            }
        }
    }
}

void print_matrix(char matrix[MAX_ROWS][MAX_COLS])
{
    for (int i = 0; i < rows; i++) printf("%s\n", matrix[i]);
}

int main(void)
{
    int rounds;
    char matrix[MAX_ROWS][MAX_COLS];

    scanf("%d", &rounds);

    while (scanf("%s", matrix[rows]) != EOF) rows++;

    cols = strlen(matrix[0]);

    while(rounds--)
    {
        char new_matrix[MAX_ROWS][MAX_COLS];
        
        simulated_round(matrix, new_matrix);

        for (int i = 0; i < rows; i++) strcpy(matrix[i], new_matrix[i]);
    }

    print_matrix(matrix);
}