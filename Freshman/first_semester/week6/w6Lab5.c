#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decimal_to_roman(int num) 
{
    int decimal_value[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char* roman_symbol[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    int len = sizeof(decimal_value) / sizeof(decimal_value[0]);

    for (int i = 0; i < len; i++) 
    {
        while (num >= decimal_value[i]) 
        {
            printf("%s", roman_symbol[i]);
            num -= decimal_value[i];
        }
    }
}


int main(void) 
{
    int n;
    scanf("%d", &n);
    
    decimal_to_roman(n);
}