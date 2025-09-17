#include <stdio.h>

int main(void)
{
    int n;
    scanf("%d", &n);

    float arr[n];

    float note;
    for (int i = 0; i < n; i++)
    {
        scanf("%f", &note);
        arr[i] = note;
    }

    float average;
    for (int i = 0; i < n; i++)
    {
        average += arr[i];
    }

    average /= n;
    
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < average) count++;
    }

    printf("%d", count);
}