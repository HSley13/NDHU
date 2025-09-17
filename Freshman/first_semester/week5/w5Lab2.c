#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int sortingArr(int *arr, int Length)
{
    int temp, counter = 0;

    for (int i = 0; i < Length; i++)
    {
        for (int j = i + 1; j < Length; j++)
        {   
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                counter++;
            }
        }
    }
    
    return counter;
}

int main(void)
{
    int N, Length;
    int arr[50];
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &Length);

        for (int j = 0; j < Length; j++)
        {
            scanf("%d", &arr[j]);
        }

        printf("Optimal train swapping takes %d swaps.\n", sortingArr(arr, Length));
    }

}