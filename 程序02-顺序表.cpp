#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt  <<  1
#define rson m + 1, r, rt  <<  1 | 1
#define root 1, n, 1

const int maxm = 100005;
const int mod = 7;
const double eps = 1e-8;
const double pi = acos( - 1.0);
const int inf = std::numeric_limits<int>::max();
const int maxn = 80;
const int INC_SIZE = 10;

typedef int ElemType;

typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
} SqList;

bool Init(SqList  &L)
{
    L.elem = (ElemType*) malloc(maxn * sizeof(ElemType));
    if(!L.elem) return false;
    L.length = 0;
    L.listsize = maxn;
    return true;
}

void Delete(SqList  &L)
{
    if(L.elem)
    {
        free(L.elem);
        L.elem = 0;
    }
}

int Find(SqList La, ElemType e)
{
    for(int k = 0; k < La.length; k++)
        if(La.elem[k] == e) return k + 1;
    return 0;
}

void Clear(SqList  &L)
{
    L.elem = 0;
}

int Insert(SqList  &L, int i, ElemType e) 
{
    if(i < 1 || i > L.length + 1) return false;
    if(L.length >= L.listsize)
    {
        int newsize = L.listsize + INC_SIZE;
        ElemType *p = (ElemType *) malloc(sizeof(ElemType)*newsize);
        if(!p) return false;
        memcpy(p, L.elem, L.length * sizeof(ElemType));
        free(L.elem);
        L.elem = p;
        L.listsize = newsize;
    }

    for(int k = L.length; k >= i; k--)
        L.elem[k] = L.elem[k - 1];

    L.elem[i - 1] = e;
    L.length++;

    return true;
}

int Erase(SqList  &L, int i, ElemType &e)
{
    if(i < 1 || i >= L.length)
        return false;

    int k;
    for(k = i - 1; k < L.length - 1; k++)
        L.elem[k] = L.elem[k + 1];
    L.length--;

    return true;
}

void Merge(SqList &La, SqList Lb)
{
    int len_a, len_b, i, e;
    len_a = La.length;
    len_b = Lb.length;

    for(i = 0; i < len_b; i++)
    {
        e = Lb.elem[i];
        if(!Find(La, e))
            Insert(La, ++len_a, e);
    }
}

int main()
{
    FILE  *fp1, *fp2;
    SqList La, Lb;
    int e;
    int i;

    if((fp1 = fopen("a.txt", "r")) == 0 || (fp2 = fopen("b.txt", "r")) == 0 )
    {
        printf("打开文件失败");
        return 1;
    }

    Init(La);
    Init(Lb);

    while(fscanf(fp1, "%d", &e) != EOF)
        Insert(La, La.length + 1, e);

    printf("\nLa:  ");
    for(i = 0; i < La.length; i++)
        printf("%d, ", La.elem[i]);

    while(fscanf(fp2, "%d", &e) != EOF)
        Insert(Lb, Lb.length + 1, e);

    printf("\nLb:  ");
    for(i = 0; i < Lb.length; i++)
        printf("%d, ", Lb.elem[i]);

    Merge(La, Lb);

    printf("\nLab:  ");
    for(i = 0; i < La.length; i++)
        printf("%d, ", La.elem[i]);
    cout << endl;

    Delete(La);
    Delete(Lb);

    system("pause");
    return 0;
}
