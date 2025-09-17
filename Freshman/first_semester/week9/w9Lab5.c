#include <stdio.h>

int calculSum(int *a, int *b) 
{
    int sum = 0;

    if (a != NULL && b != NULL && a < b) 
    {
        for (int *p = a; p < b; p++) 
        {
            sum += *p;
        }
    } 

    return sum;
}

int main(void) 
{
    int *a, *b;
    init(&a, &b);

    int result = calculSum(a, b);

    printf("%d", result);
}
