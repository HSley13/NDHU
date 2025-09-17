#include <stdio.h>

int main(void)
{
    int a;
    scanf("%d", &a);

    while (a > 0)
    {
        if ( a % 10 == 4)
        {
            printf("Yes");
            return 0;
        }
        a /= 10;
    }
    printf("No");
}