#include <bits/stdc++.h>
#ifdef __WINDOWS_
#include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n",  clock() / (double)CLOCKS_PER_SEC);

const int maxn = 1005;

int dp[maxn], capa;
std::vector<int> wgt, val;

void init()
{
    memset(dp, 0, sizeof(dp));
    wgt.clear();
    val.clear();
}

void solve()
{
    scanf("%d", &capa);
    int a, b;
    while(scanf("%d%d", &a, &b) != EOF)
    {
        wgt.push_back(a);
        val.push_back(b);
    }
    int n = val.size();
    for(int i = 0; i < n; i++)
        for(int j = capa; j >= wgt[i]; j--)
            dp[j] = max(dp[j], dp[j - wgt[i]] + val[i]);
    printf("最大总价值为 %d\n", dp[capa]);
}

int main()
{
    freopen("a.txt", "r", stdin);

    solve();

    return 0;
}
