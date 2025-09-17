#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++)
    {
       scanf("%d", &arr[i]);
    }

    float sum;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    float average = sum / n;
    
    float deviation;
    for (int i = 0; i < n; i++)
    {
        deviation += pow((arr[i] - average), 2);
    }
    
    deviation = sqrt (deviation / n);

    printf("%.2f", deviation);
}