#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define root 1, n, 1
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

const int maxn = 40;

struct ElemType
{
    int key;
    char info[40];
    int next;
};

struct SqList
{
    ElemType *elem;
    int length;
    int listsize;
};

bool InitList(SqList  &L, int size)
{
    L.elem = new ElemType[size];
    if(!L.elem) return false;
    L.length = 0;
    L.listsize = size;
    return true;
}

void DestroyList(SqList  &L)
{
    if(L.elem) delete[] L.elem;
    L.elem = 0;
    L.length = 0;
    L.listsize = 0;
}

bool InsertTail(SqList  &L, int key, char info[])
{
    if(L.length >= L.listsize - 1)
        return false;
    L.length++;
    L.elem[L.length].key = key;
    strncpy(L.elem[L.length].info, info, 40);
    return true;
}

bool CopyList(SqList &Dst, SqList &Src)
{
    if(Dst.listsize < Src.length + 1)
    {
        DestroyList(Dst);
        InitList(Dst, Src.listsize);
    }
    for(int i = 1; i <= Src.length; i++)
    {
        Dst.elem[i].key = Src.elem[i].key;
        strcpy(Dst.elem[i].info, Src.elem[i].info);
    }
    Dst.length = Src.length;
    return true;
}

void PrintList(SqList &L)
{
    for(int i = 1; i <= L.length; i++)
        printf("%d, ", L.elem[i].key);
}

void ListInsertionSort(SqList &L)
{
    int p, q;
    L.elem[0].next = 1;
    L.elem[1].next = 0;

    for(int i = 2; i <= L.length; i++)
    {
        int key;
        key = L.elem[i].key;
        p = 0;
        for(int j = 1; j < i; j++)
        {
            q = L.elem[p].next;
            if(key < L.elem[q].key) break;
            p = q;
        }
        L.elem[i].next = L.elem[p].next;
        L.elem[p].next = i;
    }

    p = L.elem[0].next;
    for(int i = 1; i < L.length; i++)
    {
        while(p < i) p = L.elem[p].next;
        q = L.elem[p].next;
        int tmp = L.elem[i].key;
        L.elem[i].key = L.elem[p].key;
        L.elem[p].key = tmp;
        L.elem[p].next = L.elem[i].next;
        L.elem[i].next = p;
        p = q;
    }
}

int Partition(SqList &L, int low, int high)
{
    L.elem[0].key = L.elem[low].key;
    while(low < high)
    {
        while(low<high && L.elem[0].key<L.elem[high].key)
            --high;
        if(low==high)
            break;
        L.elem[low].key = L.elem[high].key;
        while(low<high && L.elem[0].key > L.elem[low].key)
            ++low;
        L.elem[high].key = L.elem[low].key;
    }
    L.elem[low].key = L.elem[0].key;

    return low;
}

void QSort(SqList &L, int l, int r)
{
    if(l >= r) return;
    int m = Partition(L, l, r);
    QSort(L, l, m - 1);
    QSort(L, m + 1, r);
}

void QuickSort(SqList & L)
{
    QSort(L, 1, L.length);
}

void HeapAdjust(SqList & L, int s, int m)
{
    L.elem[0].key = L.elem[s].key;
    int j = 2 * s;
    while(j <= m)
    {
        if(j + 1 <= m && L.elem[j].key < L.elem[j + 0].key)
            ++j;
        if(L.elem[j].key < L.elem[s].key)
            break;
        L.elem[s].key = L.elem[j].key;
        s = j;
        j = 2 * s;
    }
    L.elem[s].key = L.elem[0].key;
}

void HeapSort (SqList & L)
{
    for(int i = L.length >> 1; i > 0; i--)
        HeapAdjust(L, i, L.length);

    for(int i = L.length; i > 1; i--)
    {
        L.elem[0].key = L.elem[1].key;
        L.elem[1].key = L.elem[i].key;
        L.elem[i].key = L.elem[0].key;
        HeapAdjust(L, 1, i - 1);
    }
}

char info[maxn];

void solve()
{
    SqList La, Lb;
    int key;
    InitList(La, 200);
    InitList(Lb, 200);

    FILE *fp;
    if((fp = fopen("排序数据.txt", "r")) == 0)
    {
        printf("打开“排序数据.txt”文件失败");
        system("pause");
        return ;
    }
    for(int i = 1; i < La.listsize; i++)
    {
        info[0] = 0;
        if(fscanf(fp, "%d", &key) == EOF)
            break;

        info[maxn - 1] = 0;
        if(InsertTail(La, key, info))
            printf("\n插入成功\n");
        else
            printf("\n插入失败\n");

    }
    fclose(fp);

    printf("\n原始数据：\n");
    PrintList(La);
    printf("\n");

    CopyList(Lb, La);
    ListInsertionSort(Lb);
    printf("\n表插入排序：\n");
    PrintList(Lb);
    printf("\n");

    CopyList(Lb, La);
    QuickSort(Lb);
    printf("\n快速排序：\n");
    PrintList(Lb);
    printf("\n");

    CopyList(Lb, La);
    HeapSort(Lb);
    printf("\n堆排序：\n");
    PrintList(Lb);
    printf("\n");

    DestroyList(La);
    DestroyList(Lb);

    printf("\n程序结束，按任意键返回\n");
    system("pause");
}

int main()
{
    solve();

    return 0;
}