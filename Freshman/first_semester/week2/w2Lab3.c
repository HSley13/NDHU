#include <stdio.h>

int main()
{
  int a, b, c, d, swap;
  
  scanf("%d %d %d %d", &a, &b, &c, &d);
  
  if (a > b)
  {
    swap = a;
    a = b;
    b = swap;
  }
  
  if (c > d)
  {
    swap = c;
    c = d;
    d = swap;
  }
  
  if (b<c || d<a) printf("no overlay");
  else printf("overlay");  
}