#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt  <<  1
#define rson m + 1, r, rt  <<  1 | 1
#define root 1, n, 1

const int maxn = 20;
const int maxm = 1e5 + 5;
const int mod = 10000;
const int MAX_SIZE = 500;
const double eps = 1e-8;
const int inf = 0x3f3f3f3f;

class Triple
{
public:
    int  i, j;
    int  e;
    Triple() {}
    Triple(int _i, int _j, int _e): i(_i), j(_j), e(_e) {}
};

class TSMatrix
{
public:
    Triple  data[MAX_SIZE + 5];
    int     rpos[maxn + 5];
    int     mu, nu, tu;

public:
    TSMatrix(): mu(0), nu(0), tu(0) {}
    TSMatrix(int m, int n): mu(m), nu(n), tu(0) {}
    TSMatrix(const TSMatrix &A)
    {
        mu = A.mu; nu = A.nu; tu = A.tu;
        for(int i = 0; i < tu; i++)
            data[i] = A.data[i];
    }

    TSMatrix& operator = (const TSMatrix &A)
    {
        mu = A.mu; nu = A.nu; tu = A.tu;
        for(int i = 0; i < tu; i++)
            data[i] = A.data[i];
    }

    int operator()(int n) const
    {
        if(n >= 0 && n < tu) return data[n].e;
        return 0;
    }

    int operator()(int i, int j) const
    {
        if(i > 0 && i <= mu && j > 0 && j <= nu)
        {
            for(int n = 0; n < tu; n++)
                if(data[n].i == i && data[n].j == j)
                    return data[n].e;
        }
        return 0;
    }

    TSMatrix operator + (const TSMatrix &S) const;

    void print();
    void create(int m, int n);
};

void TSMatrix::print()
{
    if(mu == 0 || nu == 0) return;
    int k(0);
    for(int i = 0; i < mu; i++)
    {
        for(int j = 0; j < nu; j++)
        {
            if(data[k].i == i + 1 && data[k].j == j + 1)
            {
                printf("%6d", data[k].e);
                k++;
            }
            else printf("%6d", 0);
        }
        printf("\n");
    }
}

void TSMatrix::create(int m, int n)
{
    int i, j, e;
    mu = m; nu = n; tu = 0;
    while(true)
    {
        printf("请输入元素所在的行、列和元素值(0行或0列退出)：");

        scanf("%d", &i);
        if(i <= 0) break;
        else if(i > m)
        {
            printf("行超界\n");
            continue;
        }

        scanf("%d", &j);
        if(j <= 0) break;
        else if(j > n)
        {
            printf("列超界\n");
            continue;
        }

        scanf("%d", &e);
        int k(0);
        for(k = 0; k < tu; k++)
        {
            if(data[k].i > i || (data[k].i == i && data[k].j >= j))
                break;
        }
        if(data[k].i == i && data[k].j == j)
        {
            printf("该位置已经输入元素\n");
            continue;
        }

        if(k < tu)
            for(int t = tu; t > k; t--)
                data[t] = data[t - 1];

        data[k] = Triple(i, j, e);
        tu++;
    }
}


TSMatrix TSMatrix::operator + (const TSMatrix &N) const
{
    TSMatrix ret(mu, nu);
    if(mu != N.mu || nu != N.nu) return ret;

    int m(0), n(0), q(0);
    while(m < tu && n < N.tu)
    {
        if(data[m].i < N.data[n].i || (data[m].i == N.data[n].i && data[m].j < N.data[n].j))
            ret.data[q++] = data[m++];
        else if(data[m].i == N.data[n].i && data[m].j == N.data[n].j)
        {
            ret.data[q] = data[m++];
            ret.data[q].e += N.data[n++].e;
            if(ret.data[q].e != 0) q++;
        }
        else ret.data[q++] = N.data[n++];
    }

    while(m < tu)
        ret.data[q++] = data[m++];
    while(n < N.tu)
        ret.data[q++] = N.data[n++];

    ret.tu = q;
    return ret;
}


int main()
{
    TSMatrix M, N, Q;
    int m, n;

    printf("输入矩阵的行数、列数：");
    scanf("%d%d", &m, &n);

    printf("输入矩阵M：\n");
    M.create(m, n);
    printf("\n");

    printf("输入矩阵N：\n");
    N.create(m, n);
    printf("\n");

    Q = M + N;

    printf("矩阵M：\n");
    M.print();
    printf("\n");

    printf("矩阵M：\n");
    N.print();
    printf("\n");

    printf("矩阵Q=M+N：\n");
    Q.print();
    printf("\n");

    system("pause");
    
    return 0;
}

