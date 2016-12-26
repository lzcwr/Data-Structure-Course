#include <bits/stdc++.h>
using namespace std;

// Sample Input
/*
11
1   4
3   5
0   6
5   7
3   8
5   9
6   10
8   11
8   12
2   13
12  14
*/

const int maxn = 1005;
int a[maxn], b[maxn];

void solve()
{
    int n, cnt;
    scanf("%d", &n);
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
        if (a[i] >= b[k])
        {
            cnt++;
            k = i;
            printf("选择时间段为 (%2d, %2d) 的活动\n", a[i], b[i]);
        }
    printf("选择活动总数为 %d\n", cnt);
}

int main()
{
    freopen("a.txt", "r", stdin);

    solve();

    return 0;
}
