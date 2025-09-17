#include <stdio.h>

int main(void) 
{
    int *p;
    init(&p);

    printf("%d, %d", p[4], p[31]);
}