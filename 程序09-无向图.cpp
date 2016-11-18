#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt  <<  1
#define rson m + 1, r, rt  <<  1 | 1
#define root 1, n, 1

const int maxn = 405;
const int maxm = 1e5 + 5;
const int mod = 10000;
const double eps = 1e-8;
const int inf = 0x3f3f3f3f;

std::vector<int> G[maxn], node;
std::vector<int>::iterator it;
bool vis[maxn], used[maxn];

void init()
{
    for(int i = 0; i < maxn; i++)
        G[i].clear();
}

void addnode(int n)
{
    if(!used[n])
        node.push_back(n);
}

void addedge(int u, int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}

void deledge(int u, int v)
{
    for(it = G[u].begin(); it != G[u].end(); it++)
        if(*it == v) G[u].erase(it);
    for(it = G[v].begin(); it != G[v].end(); it++)
        if(*it == u) G[v].erase(it);
}

void dfs(int cur)
{
    printf("%d ", cur),
    vis[cur] = true;
    for(int i = 0; i < G[cur].size(); i++)
    {
        if(!vis[G[cur][i]])
            dfs(G[cur][i]);
    }
}

void bfs(int st)
{
    std::queue<int> Q;
    while(!Q.empty()) Q.pop();
    memset(vis, false, sizeof(vis));
    Q.push(st);
    vis[st] = true;
    printf("%d ", st);
    while(!Q.empty())
    {
        int tmp = Q.front();
        Q.pop();
        for(int i = 0; i < G[tmp].size(); i++)
        {
            if(!vis[G[tmp][i]])
            {
                vis[G[tmp][i]] = true;
                Q.push(G[tmp][i]);
                printf("%d ", G[tmp][i]);
            }
        }
    }
    printf("\n");
    return ;
}

void solve()
{
    int u, v;
    init();
    memset(used, false, sizeof(used));
    while(scanf("%d%d", &u, &v) != EOF)
    {
        addedge(u, v);
        addnode(u);
        addnode(v);
    }
    sort(node.begin(), node.end());
    memset(vis, false, sizeof(vis));
    printf("BFS: "); bfs(node[0]);
    memset(vis, false, sizeof(vis));
    printf("DFS: "); dfs(node[0]);

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
