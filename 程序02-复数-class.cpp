#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
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

class  Complex
{
public:
    double  re, im;

public:
    Complex(double _re, double _im): re(_re), im(_im) {}
    Complex() {};

public:
    void Assign(double reValue, double imValue)
    {
        re=reValue;
        im=imValue;
    }
    double Re()
    {
        return re;
    }
    double Im()
    {
        return im;
    };

public:
    Complex operator + (const Complex &x) const
    {
        return Complex(re + x.re, im + x.im);
    };
    Complex operator - (const Complex &x) const
    {
        return Complex(re - x.re, im - x.im);
    };
    Complex operator * (const Complex &x) const
    {
        return Complex(re * x.re - im * x.im, re * x.im + im * x.re);
    };
    Complex operator / (const Complex &x) const
    {
        double a = (re * x.re - im * x.im) / (x.re * x.re - x.im * x.im);
        double b = (re * x.im + im * x.re) / (x.re * x.re - x.im * x.im);
        return Complex(a, b);
    };
    Complex& operator = (const Complex &x)
    {
        re = x.re; im = x.im;
        return *this;
    };
};

int main()
{
    Complex c1, c2, c3;
    double re, im;

    cout << "输入第一个复数的实部和虚部：";
    cin >> re >> im;
    c1.Assign(re, im);
    cout << "第一个复数是：" << c1.Re() << " + " << c1.Im() << "i" << endl;

    cout << "输入第2个复数的实部和虚部：";
    cin >> re >> im;
    c2.Assign ( re, im);
    cout << "第二个复数是：" << c2.Re() << " + " << c2.Im() << "i" << endl;

    c3= c1 + c2;
    cout << "两个复数的和：" << c3.Re() << " + " << c3.Im() << "i" << endl;

    c3= c1 -c2;
    cout << "两个复数的差：" << c3.Re() << " + " << c3.Im() << "i" << endl;

    c3= c1 * c2;
    cout << "两个复数的积：" << c3.Re() << " + " << c3.Im() << "i" << endl;

    c3= c1 / c2;
    cout << "两个复数的商：" << c3.Re() << " + " << c3.Im() << "i" << endl;

    system("pause");
    return 0;
}

