#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;

struct object
{
	int w, v;
};

bool cmp(object a, object b)
{
	return (a.v * 1.0 / a.w) > (b.v * 1.0 / b.w);
}

object obj[maxn];

void solve()
{
	int n, c;
	scanf("%d%d", &n, &c);
	for(int i = 0; i < n; i++)
		scanf("%d%d", &obj[i].w, &obj[i].v);
	sort(obj, obj + n, cmp);

	double ans(0);
	for(int i = 0; i < n; i++)
	{
		if(c == 0) break;
		if(c < obj[i].w) ans += c * obj[i].v * 1.0 / obj[i].w, c = 0;
		else ans += obj[i].v, c -= obj[i].w;
	}
	printf("%.3f\n", ans);
}

int main()
{
	solve();

	return 0;
}