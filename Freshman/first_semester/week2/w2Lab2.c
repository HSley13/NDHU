#include <stdio.h>
#include <string.h>

int main(void)
{
   char input[4], output[4];
   scanf("%s",input);

   int length = strlen (input);

   for (int i = length - 1, j = 0; i >= 0; i--, j++)
   {
        output[j] = input[i];
   }

    output[length] = '\0';

    printf("%s", output);
}