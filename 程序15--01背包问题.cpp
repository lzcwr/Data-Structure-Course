#include <bits/stdc++.h>
#ifdef __WINDOWS_
#include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n",  clock() / (double)CLOCKS_PER_SEC);

const int maxn = 1005;
int dp[maxn][maxn], w[maxn], v[maxn];

void init()
{
	memset(w, 0, sizeof(w));
	memset(v, 0, sizeof(v));
	memset(dp, 0, sizeof(dp));
}

void solve()
{
	int N, C, temp;
	scanf("%d%d", &N, &C);
	for (int i = 1; i <= N; i++)
		scanf("%d%d", &w[i], &v[i]);
	for (int i = 1; i <= N; i++)
		for (int c = 0; c <= C; c++)
		{
			dp[i][c] = dp[i - 1][c];
			if (c >= w[i]) dp[i][c] = max(dp[i][c], dp[i - 1][c - w[i]] + v[i]);
		}
	printf("最大总价值为%2d\n", dp[N][C]);
	temp = C;
	for (int i = N; i > 0 && temp > 0; i--)
		if (dp[i][temp] != dp[i - 1][temp])
		{
			printf("选择质量为%2d, 价值为%2d的物品\n", w[i], v[i]);
			temp -= w[i];
		}
}

int main()
{
	freopen("a.txt", "r", stdin);
	
	solve();
	
	return 0;
}
