#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int c;
    int new_sentence = 1;
    int CAP_NEX_WORD = 1;

    while ((c = getchar()) != EOF)
    {
        if (new_sentence) 
        {
            if (isalpha(c)) 
            {
                if (CAP_NEX_WORD)
                {
                    putchar(toupper(c)); 
                    CAP_NEX_WORD = 0; 
                }

                else putchar(c); 

                new_sentence = 0; 
            }
                    
            else
            {
                putchar(c); 

                if (c == '.' || c == '!' || c == '?') 
                {
                    new_sentence = 1; 
                    CAP_NEX_WORD = 1; 
                }

                else if (c == '%')  CAP_NEX_WORD = 0; 
            }
        }

        else
        {
            putchar(c); 
            if (c == '.' || c == '!' || c == '?')
            {
                new_sentence = 1; 
                CAP_NEX_WORD = 1; 
            }

            else if (c == '%')
            {
                CAP_NEX_WORD = 0; 
            }
        }
    }
}
