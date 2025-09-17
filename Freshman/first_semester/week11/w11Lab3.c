#include <stdio.h>
#include <stdlib.h>

void generateLookAndSay(const char *prev, int N) 
{
    if (N == 0) return;
    
    char *result = (char *) malloc(2 * strlen(prev) + 1);

    if (result == NULL) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int count = 1;
    char currentDigit = prev[0];
    int resultIndex = 0;

    for (int i = 1; prev[i] != '\0'; i++) 
    {
        if (prev[i] == currentDigit) count++;

        else 
        {
            // Append the count and currentDigit to the result
            resultIndex += sprintf(result + resultIndex, "%d%c", count, currentDigit);

            // Reset count and update currentDigit
            count = 1;
            currentDigit = prev[i];
        }
    }

    // Append the count and currentDigit for the last group
    resultIndex += sprintf(result + resultIndex, "%d%c", count, currentDigit);

    result[resultIndex] = '\0';

    printf("%s\n", result);

    generateLookAndSay(result, N - 1);

    free(result);
}

int main(void) 
{
    int N;
    scanf("%d", &N);

    if (N >= 1) 
    {
        printf("1\n");
        generateLookAndSay("1", N - 1);
    }
}