#include <stdio.h>
#include <string.h>

int main(void)
{
    int a;
    float toll;

    scanf("%d", &a);

    if (a < 200)
    {
        toll = a * 1.2;
        printf("%.0f", toll);
    }

    else
    {
        a -= 200;
        toll = (0.75 * a * 1.2) + (200 * 1.2);
        printf("%.0f", toll);
    }
}
