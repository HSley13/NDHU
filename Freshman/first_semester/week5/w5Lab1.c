#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

void sortingArr(int *arr, int N, int M)
{
    for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                int modi = arr[i] % M;
                int modj = arr[j] % M;
                int temp, odd, even;

                if (modi > modj)
                {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }

                else if (modi == modj)
                {
                    if (((arr[i] % 2) && !(arr[j] % 2)) || !(arr[i] % 2) && (arr[j] % 2))
                    {
                        if (arr[i] % 2)
                        {
                            odd = arr[i];
                            even = arr[j];
                        }
                        else 
                        {
                            odd = arr[j];
                            even = arr[i];   
                        }

                        arr[i] = odd;
                        arr[j] = even;
                    }
                    
                    else if ((arr[i] % 2) && (arr[j] % 2))
                    {
                        if (arr[i] < arr[j])
                        {
                            temp = arr[i];
                            arr[i] = arr[j];
                            arr[j] = temp;
                        }
                    }

                    else
                    {
                         if (arr[i] > arr[j])
                        {
                            temp = arr[i];
                            arr[i] = arr[j];
                            arr[j] = temp;
                        }
                    }
                }
            }
        }
}

int main(void)
{
    int N, M;
    
    while (1)
    {   
        scanf("%d %d", &N, &M);
        if (!N && !M)
        {
            break;
        }

        int arr[N];
        for (int i = 0; i < N; i++)
        {
            scanf("%d", &arr[i]);
        }

        sortingArr(arr, N, M);
        
        printf("%d %d\n", N, M);
        for (int i = 0; i < N; i++)
        {
            printf("%d\n", arr[i]);
        }
    }

    printf("%d %d", N, M);
}