#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt  <<  1
#define rson m + 1, r, rt  <<  1 | 1
#define root 1, n, 1

const int maxn = 5005;
const int maxm = 100005;
const int mod = 7;
const double eps = 1e-8;
const double pi = acos(-1.0);
const int inf = std::numeric_limits<int>::max();

struct Complex
{
    double re, im;
};

void Assign(Complex &z, double re_val, double im_val)
{
    z.re = re_val; z.im = im_val;
}

double Re(Complex z)
{
    return z.re;
}

double Im(Complex z)
{
    return z.im;
}

void Add(Complex z1,  Complex z2,  Complex &ret)
{
    ret.re = z1.re + z2.re;
    ret.im = z1.im + z2.im;
}

void Sub(Complex z1,  Complex z2,  Complex &ret)
{
    ret.re = z1.re - z2.re;
    ret.im = z1.im - z2.im;
}

void Mul(Complex z1,  Complex z2,  Complex &ret)
{
    ret.re = z1.re * z2.re - z1.im * z2.im;
    ret.im = z1.re * z2.im + z1.im * z2.re;
}

void Div(Complex z1,  Complex z2,  Complex &ret)
{
    ret.re = (z1.re * z2.re - z1.im * z2.im) / (z2.re * z2.re - z2.im * z2.im);
    ret.im = (z1.re * z2.im + z1.im * z2.re) / (z2.re * z2.re - z2.im * z2.im);
}

void Assige(Complex z1,  Complex z2,  Complex &ret) {}

int main()
{
    Complex z1,  z2,  s,  t;
    double re,  im;
    cout << "输入第一个复数的实部和虚部：";
    cin >> re >> im;
    Assign(z1,  re,  im);
    cout << "第一个复数是：" << Re(z1) << " + " << Im(z1) << "i" << endl;
    cout << "输入第二个复数的实部和虚部：";
    cin >> re >> im;
    Assign(z2,  re,  im);
    cout << "第二个复数是：" << Re(z2) << " + " << Im(z2) << "i" << endl;
    Add(z1, z2, s);
    Mul(z1, z2, t);
    cout << "2个复数的和：" << Re(s) << " + " << Im(s) << "i" << endl;
    cout << "2个复数的乘积：" << Re(t) << " + " << Im(t) << "i" << endl;
    system("pause");
    
    return 0;
}
