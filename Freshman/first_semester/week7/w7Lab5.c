#include <stdio.h>
#include <limits.h>

#define SIZE 10001

int main(void)
{
    int l, h, r, l_side = INT_MAX, r_side = 0;
    int ans[SIZE] = {0};

    while (scanf("%d %d %d", &l, &h, &r) == 3 && l != 0)
    {
        l_side = (l_side > l) ? l : l_side;
        r_side = (r > r_side) ? r : r_side;

        for (int i = l; i < r; i++) ans[i] = (h  > ans[i]) ? h : ans[i];
    }

    for (int i = l_side; i < r_side; i++)
    {
        if (ans[i] != ans[i - 1])
        {
            if (ans[i] == 0) printf("%d 0 ", i);
            
            else printf("%d %d ", i, ans[i]);
        }
    }

    printf("%d 0", r_side);
}