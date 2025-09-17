#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool distinct(char *arr, int i, int j)
{
    int encountered[256] = {0};

    for (int k = i; k <= j; k++)
    {
        if (encountered[arr[k]]) return false;

        encountered[arr[k]] = 1;
    }

    return true;
}

void longest_subs_string(char *arr, int *start, int *end)
{
    int longest = 0;
    int n = strlen(arr);

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (distinct(arr, i, j) && (j - i + 1 > longest))
            {
                longest = j - i + 1;
                *start = i;
                *end = j;
            } 
        }
    }
}

int main(void)
{
    char str[1000];
    scanf("%s", str);

    int start = 0, end = 0;
    longest_subs_string(str, &start, &end);

    for (int i = start; i <= end; i++) printf ("%c", str[i]);
}