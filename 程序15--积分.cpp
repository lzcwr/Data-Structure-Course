#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n",  clock() / (double)CLOCKS_PER_SEC);

const double eps = 1e-6;
const int MOD = 1e6;
const int operation = 1e7;

double F(double x)  
{  
    return sin(x);
}  
double simpson(double a, double b)
{  
    double c = a + (b - a) / 2;  
    return (F(a) + 4 * F(c) + F(b))*(b - a) / 6;  
}  
double integrate(double a, double b, double eps, double A)
{  
    double c = a + (b - a) / 2;  
    double L = simpson(a, c), R = simpson(c, b);  
    if (fabs(L + R - A) <= 15 * eps)return L + R + (L + R - A) / 15.0;  
    return integrate(a, c, eps / 2, L) + integrate(c, b, eps / 2, R);  
}  
double integrate(double a, double b, double eps)
{  
    return integrate(a, b, eps, simpson(a, b));  
}  

void solve()
{
    int l, r, cas(0);
    while(cin >> l >> r)
        printf("Case #%d: integrate = %9f\n", ++cas, integrate(l, r, eps));
}

int main()
{
    solve();

    return 0;
}