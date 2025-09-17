#include <stdio.h>

int main(void)
{
    int a;
    scanf("%d", &a);

    if ( (a % 3 == 2) && (a % 7 == 5) && (a % 11 == 7) ) printf("YES\n");
    else printf("NO\n");

}