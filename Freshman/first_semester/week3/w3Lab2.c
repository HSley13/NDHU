#include <stdio.h>

int main(void)
{
    int arr[4];
    scanf("%d %d %d %d", &arr[0], &arr[1], &arr[2], &arr[3]);

    int max = arr[0];
    for (int i = 1; i < 4; i++)
    {
        if (arr[i] > max) max = arr[i];
    }

    printf("%d", max); 
}