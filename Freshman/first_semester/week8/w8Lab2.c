#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define size 100
int matrix[size][size] = {{0}};
int visited[size][size] ={{0}};

bool is_valid(int x, int y, int n)
{
    return (x >= 0 && x < n && y >= 0 && y < n && matrix[x][y] == 0 && !visited[x][y]);
}

int depth_first_search(int x, int y, int n)
{
    visited[x][y] = 1;

    if (x == n - 1 && y == n - 1) return 1;

    if (is_valid(x - 1, y, n) && depth_first_search(x - 1, y, n)) return 1;
    if (is_valid(x + 1, y, n) && depth_first_search(x + 1, y, n)) return 1;
    if (is_valid(x, y - 1, n) && depth_first_search(x, y - 1, n)) return 1;
    if (is_valid(x, y + 1, n) && depth_first_search(x, y + 1, n)) return 1;

    return 0;
}

int main(void)
{
    int n; 
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) scanf("%d", &matrix[i][j]);
    }

    if (depth_first_search(0, 0, n)) printf("Yes\n");
    
    else printf("No\n");
}