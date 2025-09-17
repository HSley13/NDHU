#include <stdio.h>
#include <stdlib.h>

/*************************************************************
function name: convertToDifferentBase
description: Convert a decimal number @dec to the number with different @base and store the result as a string in result
return vaule: Result after convert.
notice: The letter you see in the number should be upper case.
*************************************************************/
char *convertToDifferentBase(int dec, int base, char *result) 
{
    int arr[50]; 
    char hex[] = {'0','1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    int num = dec, i = 0; 

    while(num != 0)
    {
        arr[i] = num % base; 
        num /= base; 
        i++; 
    }

    int index = 0; 
    for(int j = i - 1; j >= 0; j--)
    {
        for(int a = 0; a < 16; a++)
        {
            if(arr[j] == a) result[index] = hex[a]; 
        }

        index++; 
    }  
    result[index] = '\0';    

    return result; 
}