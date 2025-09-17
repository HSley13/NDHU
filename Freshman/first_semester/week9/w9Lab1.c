#include <stdio.h>

int main(void) 
{
    init();
    void *p = &block; 

    printf("%d, %c, %f", *(int *)p, *(char *)((char *)p + sizeof(int)), *(float *)((char *)p + sizeof(int) + sizeof(char)));
}
