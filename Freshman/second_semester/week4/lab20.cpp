#include <iostream>
#include <vector>
#include <stack>

int main(void)
{
    int n;
    std::cin >> n;

    for (int t = 0; t < n; t++)
    {
        int a, b;
        std::cin >> a >> b;

        int stx, sty;
        std::cin >> stx >> sty;

        int draw[a + 1][b * 2 + 1] = {0};

        for (int i = 0; i < a + 1; i++)
        {
            for (int j = 0; j < b * 2 + 1; j++)
            {
                if (i != a)
                {
                    if (j & 1)
                        draw[i][j] = 2;
                    else
                        draw[i][j] = 1;
                }
                else
                {
                    if (j & 1)
                        draw[i][j] = 2;
                }
            }
        }

        struct p
        {
            int x, y;
        };

        p tmp;

        tmp.x = stx - 1;
        tmp.y = sty * 2 - 1;

        std::stack<p> stk;
        stk.push(tmp);

        for (int count = a * b - 1; count > 0; count--)
        {
            char c;
            std::cin >> c;

            if (c == 'U')
            {
                tmp.x++;
                draw[tmp.x][tmp.y] = 0;

                stk.push(tmp);
            }

            if (c == 'D')
            {
                draw[tmp.x][tmp.y] = 0;
                tmp.x--;

                stk.push(tmp);
            }

            if (c == 'L')
            {
                tmp.y -= 2;
                draw[tmp.x][tmp.y + 1] = 0;

                stk.push(tmp);
            }

            if (c == 'R')
            {
                tmp.y += 2;
                draw[tmp.x][tmp.y - 1] = 0;

                stk.push(tmp);
            }

            if (c == 'F')
            {
                int num;
                std::cin >> num;

                for (int i = 0; i < num; i++)
                    stk.pop();

                count++;

                tmp = stk.top();
            }
        }

        for (int i = a; i >= 0; i--)
        {
            for (int j = 0; j < b * 2 + 1; j++)
            {
                if (i == a && j == b * 2)
                    continue;

                if (draw[i][j] == 1)
                    std::cout << "|";

                if (draw[i][j] == 2)
                    std::cout << "_";

                if (draw[i][j] == 0)
                    std::cout << " ";
            }

            std::cout << std::endl;
        }

        if (t != n - 1)
            std::cout << std::endl;
    }
}
