#include <bits/stdc++.h>
#ifdef __WINDOWS_
#include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define root 1, n, 1

const int maxn = 1010;
const int maxm = 1e5 + 5;
const int mod = 10000;
const double eps = 1e-8;
const int inf = 0x3f3f3f3f;

bool vis[maxn], used[maxn];
int pre[maxn], lowcost[maxn], cost[maxn][maxn], d[maxn][maxn];
std::vector<char> node;

void Dijkstra(int cost[][maxn], int lowcost[], int n, int st)
{
	for(int i = 0; i < n; i++)
	{
		lowcost[i] = inf;
		vis[i] = false;
		pre[i] = -1;
	}
	lowcost[st] = 0;
	for(int j = 0; j < n; j++)
	{
		int k = -1;
		int Min = inf;
		for(int i = 0; i < n; i++)
			if(!vis[i] && lowcost[i] < Min)
			{
				Min = lowcost[i];
				k = i;
			}
		if(k == -1)break;
		vis[k] = true;
		for(int i = 0; i < n; i++)
			if(!vis[i] && lowcost[k] + cost[k][i] < lowcost[i])
			{
				lowcost[i] = lowcost[k] + cost[k][i];
				pre[i] = k;
			}
	}
}

int lowc[maxn];
int Prim(int cost[][maxn], int n)
{
	int ret = 0;
	memset(vis, false, sizeof(vis));
	vis[0] = true;
	for(int i = 1; i < n; i++)
        lowc[i] = cost[0][i];
	for(int i = 1; i < n; i++)
	{
		int minc = inf;
		int p = -1;
		for(int j = 0; j < n; j++)
			if(!vis[j] && minc > lowc[j])
			{
				minc = lowc[j];
				p = j;
			}
		if(minc == inf) return -1;
		ret += minc;
		vis[p] = true;
		for(int j = 0; j < n; j++)
			if(!vis[j] && lowc[j] > cost[p][j])
				lowc[j] = cost[p][j];
	}
	return ret;
}

void floyd(int n)
{
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

void solve()
{
	int w;
	char u[10], v[10];
	node.clear();
	memset(used, false, sizeof(used));
	for(int i = 0; i < maxn; i++)
		for(int j = 0; j < maxn; j++)
			d[i][j] = inf;
	while(scanf("%s%s%d", &u, &v, &w) != EOF)
	{
		cost[u[0] - 'a'][v[0] - 'a'] = w;
		d[u[0] - 'a'][v[0] - 'a'] = w;
		if(!used[u[0] - 'a']) node.push_back(u[0]);
		if(!used[v[0] - 'a']) node.push_back(v[0]);
		used[u[0] - 'a'] = used[v[0] - 'a'] = true;
	}
	cin.clear();
	printf("---%d %d\n", node.size(), inf);
	printf("MST: %d\n", Prim(cost, node.size()));
	char x; cin >> x;
	Dijkstra(cost, lowcost, node.size(), x);
	for(int i = 0; i < node.size(); i++)
		printf("Dijkstra: %c -> %c: %d\n", x, node[i], lowcost[i]);
	floyd(node.size());
	for(int i = 0; i < node.size(); i++)
		printf("Floyed: %c -> %c: %d\n", x, node[i], d[x - 'a'][node[i] - 'a']);
}

int main()
{
#ifndef ONLINE_JUDGE
	// freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
#endif

	solve();

#ifndef ONLINE_JUDGE
	// fclose(stdin);
	// fclose(stdin);
	// system("out.txt");
#endif

	return 0;
}
