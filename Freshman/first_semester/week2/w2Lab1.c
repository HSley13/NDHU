#include <stdio.h>
#include <math.h>

int main(void)
{
    float a, b, c;
    scanf("%f",&a);

    b = round (a*100)/100;
    c = floor (a*100)/100;

    printf("%.2f\n",b);
    printf("%.2f\n",c);
}