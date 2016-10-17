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

struct Triple
{
    int i, j;
    int e;
    Triple(){}
    Triple(int _i, int _j, int _e): i(_i), j(_j), e(_e) {}
};

struct TSMatrix
{
    Triple  data[MAX_SIZE + 5];
    int     rpos[maxn + 5];
    int     mu, nu, tu;
};

void InitMatrix(TSMatrix &M, int m, int n)
{
    M.mu = m; M.nu = n; M.tu = 0;
}

void CreateMatrix(TSMatrix &M, int m, int n)
{
    M.mu = m; M.nu = n; M.tu = 0;
    int i, j, e;
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
        for(k = 0; k < M.tu; k++)
        {
            if(M.data[k].i > i || (M.data[k].i == i && M.data[k].j >= j))
                break;
        }
        if(M.data[k].i == i && M.data[k].j == j)
        {
            printf("该位置已经输入元素\n");
            continue;
        }

        if(k < M.tu)
            for(int t = M.tu; t > k; t--)
                M.data[t] = M.data[t - 1];

        M.data[k] = Triple(i, j, k);
        M.tu++;
    }
}

void PrintMatrix(TSMatrix &M)
{
    if(M.mu == 0 || M.nu == 0) return;

    int k(0);
    for(int i = 0; i < M.mu; i++)
    {
        for(int j = 0; j < M.nu; j++)
        {
            if(M.data[k].i == i + 1 && M.data[k].j == j + 1)
            {
                printf("%6d", M.data[k].e);
                k++;
            }
            else printf("%6d", 0);
        }
        printf("\n");
    }
}


int Add(TSMatrix &M, TSMatrix &N, TSMatrix &Q)
{
    if(M.mu != N.mu || M.nu != N.nu)
        return false;
    Q.mu = M.mu; Q.nu = M.nu;

    int m(0), n(0), q(0);

    while(m < M.tu && n < N.tu)
    {
        if(M.data[m].i < N.data[n].i || (M.data[m].i == N.data[n].i && M.data[m].j < N.data[n].j))
            Q.data[q++] = M.data[m++];
        else if(M.data[m].i == N.data[n].i && M.data[m].j == N.data[n].j)
        {
            Q.data[q] = M.data[m++];
            Q.data[q].e += N.data[n++].e;
            if(Q.data[q].e != 0) q++;
        }
        else Q.data[q++] = N.data[n++];
    }

    while(m < M.tu)
        Q.data[q++] = M.data[m++];
    while(n < N.tu)
        Q.data[q++] = N.data[n++];

    return true;
}

int main()
{
    TSMatrix M, N, Q;
    int m, n;

    printf("输入矩阵的行数、列数：");
    scanf("%d%d", &m, &n);

    printf("输入矩阵M：\n");
    CreateMatrix(M, m, n);
    printf("\n");

    printf("输入矩阵N：\n");
    CreateMatrix(N, m, n);
    printf("\n");

    Add(M, N, Q);

    printf("矩阵M：\n");
    PrintMatrix(M);
    printf("\n");

    printf("矩阵M：\n");
    PrintMatrix(N);
    printf("\n");

    printf("矩阵Q=M+N：\n");
    PrintMatrix(Q);
    printf("\n");

    system("pause");

    return 0;
}

