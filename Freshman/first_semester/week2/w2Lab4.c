#include <stdio.h>

int main(void)
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    if (a + b > c)
    {
        if (a * a + b * b == c * c)
        {
            printf("right triangle\n");
        }

        else if (a * a + b * b > c * c)
        {
            printf("acute triangle\n");
        }

        else if ( a * a + b * b < c * c )
        {
            printf("obstuse triangle\n");
        }        
    }

    else printf("can not construct\n");

}