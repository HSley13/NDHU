#include <stdio.h>
#include <stdlib.h>

int sum_intergers_in_string(char *str)
{
    int sum = 0, current_number = 0, constructing_number = 0;

    while(*str)
    {
        if (isdigit(*str)) 
        {
            current_number = current_number * 10 + (*str - '0');
            constructing_number = 1;
        }

        else 
        {
            if (constructing_number)
            {
                sum += current_number;
                current_number = 0;
                constructing_number = 0;
            }
        }

        str++;
    }

    return sum;
}

int main(void)
{
    init();
    char *str = s;
    int sum = sum_intergers_in_string(str);

    printf("%d", sum);
}