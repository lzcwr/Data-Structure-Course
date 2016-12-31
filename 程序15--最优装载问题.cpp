#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define MaxData 32767

const int maxn = 1005;

struct bbnode
{
    bbnode *parent;
    bool LChild;
};

struct HeapNode
{
    bbnode *ptr;
    int uweight;
    int level;
};

typedef struct Heap
{
    int capa, size;
    HeapNode *Elem;
} Heap, *HeapQueue;

HeapQueue init(int maxElem)
{
    HeapQueue H = new Heap;
    H -> capa = maxElem;
    H -> size = 0;
    H -> Elem = new HeapNode[maxElem + 1];
    H -> Elem[0].uweight = MaxData;
    return H;
}

void InsertMax(HeapNode x, HeapQueue H)
{
    int i;
    for(i = ++H -> size; H -> Elem[i >> 1].uweight<x.uweight; i >>= 1)
        H -> Elem[i] = H -> Elem[i >> 1];
    H -> Elem[i]=x;
}

HeapNode DeleteMax(HeapQueue H)
{
    int i, child;
    HeapNode MaxElem, LastElem;
    MaxElem = H -> Elem[1];
    LastElem = H -> Elem[H -> size--];
    for(i = 1; i << 1 <= H -> size; i = child)
    {
        child = i << 1;
        if(child != H -> size && H -> Elem[child + 1].uweight>H -> Elem[child].uweight)
            child++;
        if(LastElem.uweight < H -> Elem[child].uweight)
            H -> Elem[i] = H -> Elem[child];
    }
    H -> Elem[i] = LastElem;
    return MaxElem;
}

void AddLiveNode(HeapQueue &H, bbnode *E, int wt, bool ch, int lev)
{
    bbnode *b = new bbnode;
    b -> parent = E;
    b -> LChild = ch;
    HeapNode N;
    N.uweight = wt;
    N.level = lev;
    N.ptr = b;
    InsertMax(N, H);
}

int MaxLoading(int w[], int c, int n, int bestx[])
{

    HeapQueue H = init(100);
    int *r = new int[n + 1];
    r[n] = 0;
    for(int j = n - 1; j > 0; j--)
        r[j] = r[j + 1] + w[j + 1];
    int i  =  1;
    bbnode *E = 0;
    int Ew = 0;
    while(i != n + 1)
    {
        int wt = Ew + w[i];
        if(wt <= c)
            AddLiveNode(H, E, wt + r[i], true, i + 1);
        AddLiveNode(H, E, Ew + r[i], false, i + 1);
        HeapNode N;
        N = DeleteMax(H);
        i = N.level;
        E = N.ptr;
        Ew = N.uweight - r[i - 1];
    }
    for(int j = n; j > 0; j--)
    {
        bestx[j] = E -> LChild;
        E = E -> parent;
    }
    return Ew;
}

int n, c, w[maxn], bestx[maxn];

void solve()
{
    scanf("%d%d", &n, &c);
    w[0] = -1;
    for(int i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    int bestw = MaxLoading(w, c, n, bestx);
    cout << bestw << endl;
    for(int j = 1; j <= n; j++)
        if(bestx[j])
            printf("装载质量为%2d的物品%2d个\n", w[j], bestx[j]);
}

int main()
{
    freopen("c.txt", "r", stdin);

    solve();

    return 0;
}
