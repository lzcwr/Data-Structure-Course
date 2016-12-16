#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;
int a[maxn], b[maxn];

void solve()
{
    int n, cnt, tmp;
    while(scanf("%d", &n))
    {
    	if(n == 0) break;
        cnt = 1;
        for (int i = 0; i < n; i++)
        	scanf("%d%d", &a[i], &b[i]);
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                if (b[j] < b[i])
                {
                	swap(a[i], a[j]);
                	swap(b[i], b[j]);
                }
            }
        }
        int k(0);
        for (int i = 1; i < n; i++)
            if (a[i] >= b[k])  { cnt++; k = i; }
        printf("%d\n", cnt);
    }
}

int main()
{
	solve();

	return 0;
}