#include <bits/stdc++.h>
using namespace std;

const int manx = 1005;
int b[maxn];

int Paratition(int *a, int p, int r)
{
    int key = a[r];
    int i = p - 1;
    for(int j = p; j < r; j++)
        if(a[j] < key)
        {
            i++;
            swap(a[i], a[j]);
        }
    swap(a[i + 1], a[r]);
    return i + 1;
}

int RandomParatition(int *a, int p, int r)
{
    int x = rand() % (r - p + 1) + p;
    swap(a[x], a[r]);  
    return Paratition(a, p, r);
}

int select(int *a, int p, int r, int k)
{
    if(p == r)
        return a[p];
    int q = RandomParatition(a, p, r);  
    int x = q - p + 1;
    if(x == k) 
        return a[q];
    if(x > k)  
        return select(a, p, q - 1, k);
    else  
        return select(a, q + 1, r, k - x);
}

void solve()
{
    int n, q;
    scanf("%d%d", &n, &q);
   
    for(int i = 1; i <= n; i++)
        scanf("%d", &b[i]);
    while(q--)
    {
    	int k;
    	scanf("%d", &k);
	    int ans = select(b, 1, n, k);
	    printf("The %dth MIN number is %d\n", k, ans);
	}
}

int main()
{

	solve();

	return 0;
}