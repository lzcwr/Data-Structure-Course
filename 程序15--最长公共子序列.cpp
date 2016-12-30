#include <bits/stdc++.h>
#ifdef __WINDOWS_
#include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n",  clock() / (double)CLOCKS_PER_SEC);

const int maxn = 1005;

char a[maxn], b[maxn], p[maxn];
int dp[maxn][maxn], la[maxn][30], lb[maxn][30];
int an, bn, state;

void dfs(int x, int y, int len)
{
    if(state) return;
    if(len == 0)
    {
        state = true;
        for(int i = dp[an][bn] - 1; i >= 0; i--)
            printf("%c", p[i]);
        printf("\n");
    }
    else
    {
        for(int i = 0; i < 26; i++)
        {
            int t1 = la[x][i];
            int t2 = lb[y][i];
            if(dp[t1][t2] == len)
            {
                p[len - 1] = 'a' + i;
                dfs(--t1, --t2, --len);
            }
        } 
    }
}

void init()
{
    memset(dp, 0, sizeof(dp));
    memset(la, 0, sizeof(la));
    memset(lb, 0, sizeof(lb));
    memset(p, '\0', sizeof(p));
}

void solve()
{
    while(~scanf("%s%s", a, b))
    {
    	printf("给定两个字符串的LCS为：   "); 
        an = strlen(a);
        bn = strlen(b);
        for(int i = 0; i < an / 2; i++)
        {
            char c = a[i];
            a[i] = a[an - i - 1];
            a[an - i - 1] = c;
        }

        for(int i = 0; i < bn / 2; i++)
        {
            char c = b[i];
            b[i] = b[bn - i - 1];
            b[bn - i - 1] = c;
        }

        for(int i = 0; i < an; i++)
            for(int j = 0; j < bn; j++)
                if(a[i] == b[j])
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                else
                    dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]);

        for(int i = 0; i < an; i++)
            for(int j = 0; j < 26; j++)
                if(a[i] == 'a' + j)
                    la[i + 1][j] = i + 1;
                else
                    la[i + 1][j] = la[i][j];

        for(int i = 0; i < bn; i++)
            for(int j = 0; j < 26; j++)
                if(b[i] == 'a' + j)
                    lb[i + 1][j] = i + 1;
                else
                    lb[i + 1][j] = lb[i][j];

        state = false;
        dfs(an, bn, dp[an][bn]);
    }
}

int main()
{
    freopen("b.txt", "r", stdin);

    solve();

    return 0;
}
