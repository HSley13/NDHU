#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int main(void)
{
    char sentence[1001] = {0}; 
    int count [130] = {0};
   
    while (gets(sentence))
    {
        int length = strlen (sentence);

        for (int i = 0; i < length; i++)
        {
            count[(int)sentence[i]]++;
        }

        for (int i= 1; i <= length; i++)
        {
            for (int j = 127; j >= 32; j--)
            {
                if (count[j] == i)
                {
                    printf("%d %d\n", j, i);
                }
            }
        }
        
        printf("\n");
        for (int i = 0; i <= 130; i++)
        {
            count[i] = 0;
        }
    }

}