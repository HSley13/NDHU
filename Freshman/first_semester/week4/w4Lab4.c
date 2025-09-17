#include <stdio.h>
#include <string.h>

int main(void)
{
    char num[1001];
  
   while (1)
   {
     scanf("%s",num);
     
     if (num[0] == '0' && strlen(num) == 1) break;
     
     int evenSum = 0, oddSum = 0, length = strlen(num);
     
     for (int i = 0; i < length; i++)
     {
      	if (!(i % 2)) evenSum += num[i] - '0';
        else oddSum += num[i] - '0';
     }
     
     int diff = evenSum - oddSum;
     
     if (!(diff % 11)) printf("%s is a multiple of 11.\n", num);
     else printf("%s is not a multiple of 11.\n", num);
     
   }
}