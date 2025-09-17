#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decimal_to_binary(int n) 
{ 
    int bNum[32]; 

    int i = 0; 
    while (n > 0) 
    {
        bNum[i] = n % 2; 
        n /= 2; 
        i++; 
    } 

    for (int j = i - 1; j >= 0; j--) printf("%d", bNum[j]);
} 

int main(void)
{
    int n;
    scanf("%d", &n);

    decimal_to_binary(n);
}