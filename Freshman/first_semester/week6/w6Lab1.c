#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_prime_number(int number) 
{ 
    for (int i = 2; i <= number / 2; i++) if (!(number % i)) return 0; 

    return 1; 
} 

void sorting_arr(int *arr, int n)
{   
    int prime, notPrime, temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if ((is_prime_number(arr[i]) && (!is_prime_number(arr[j]))) || ((!is_prime_number(arr[i])) && is_prime_number(arr[j])))
            {
                if (is_prime_number(arr[i]))
                {
                    prime = arr[i];
                    notPrime = arr[j];
                }

                else 
                {
                    prime = arr[j];
                    notPrime = arr[i];
                }
                
                arr[i] = prime;
                arr[j] = notPrime;
            }

            else if (is_prime_number(arr[i]) && is_prime_number(arr[j]))
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

int main(void)
{
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    
    sorting_arr(arr, n);

    for (int i = 0; i < n; i++) printf("%d ", arr[i]);  
}