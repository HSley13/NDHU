#include <stdio.h>
#include <math.h>

#define N 114514

typedef long long ll;

int main(void) 
{
    int C;
    scanf("%d", &C);

    while (C--) 
    {
        int n;
        scanf("%d", &n);

        ll points[N][2]; 

        for (int i = 0; i < n; i++) scanf("%lld %lld", &points[i][0], &points[i][1]);
    
        for (int i = 0; i < n - 1; i++) 
        {
            for (int j = 0; j < n - i - 1; j++) 
            {
                if (points[j][0] > points[j + 1][0]) 
                {
                    ll temp[2];
                    temp[0] = points[j][0];
                    temp[1] = points[j][1];
                    points[j][0] = points[j + 1][0];
                    points[j][1] = points[j + 1][1];
                    points[j + 1][0] = temp[0];
                    points[j + 1][1] = temp[1];
                }
            }
        }

        double ans = 0;
        ll k = 0;

        for (int i = n - 2; i >= 0; i--) 
        {
            k = k > points[i + 1][1] ? k : points[i + 1][1];

            if (points[i][1] > k) 
            {
                double dis = sqrt(pow(points[i][0] - points[i + 1][0], 2) + pow(points[i][1] - points[i + 1][1], 2));

                ans += (points[i][1] - k) * dis / (points[i][1] - points[i + 1][1]);
            }
        }

        printf("%.2lf\n", ans);
    }
}