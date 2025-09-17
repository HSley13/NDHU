#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 1000005

void quickSort(int *arr, int low, int high);
int partition(int *arr, int low, int high);

int main ()
{
    int arr[SIZE] = {0}, n;

    while(scanf("%d", &n) != EOF)
    {
        for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

        quickSort(arr, 0, n - 1);

	    int mid1 = arr[(n - 1)/2];
	    int mid2 = arr[n / 2];
        
        int counter = 0;
        for(int i = 0; i < n; i++)
        {
            if (arr[i] == mid1 || arr[i] == mid2) counter++;
        }
      
        printf("%d %d %d\n", mid1, counter, mid2 - mid1 + 1);
    }
  
    return 0;
}

void quickSort(int *arr, int low, int high)
{
    int p = 0;

    if (low < high)
    {
        p = partition(arr, low, high);

        quickSort(arr, low, p - 1);
        
        quickSort(arr, p + 1, high);
    }
}

int partition(int *arr, int low, int high)
{
    int i = (low - 1);

    for (int j = low; j <= high; j++)
    {
        if (arr[j] < arr[high])
        {
            i++;
          
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    } 
    
    int temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;

    return (i+1);
}
