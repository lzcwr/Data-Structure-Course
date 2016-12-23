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
    char info[maxn];
    int nxt;
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
    L.elem = 0; L.length = 0; L.listsize = 0;
}

bool InsertTail(SqList  &L, int key, char info[])
{
    if(L.length >= L.listsize - 1) return false;
    L.elem[++L.length].key = key;
    strncpy(L.elem[L.length].info, info, maxn);
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

void HeapAdjust(SqList & L, int s, int m)
{
    ElemType rc;
    rc.key = L.elem[s].key;
    strcpy(rc.info, L.elem[s].info);
    for(int j = s << 1; j <= m; j <<= 1)
    {
        if(j < m && L.elem[j].key < L.elem[j + 1].key )  ++j;
        if(rc.key >= L.elem[j].key) break;
        L.elem[s].key = L.elem[j].key;
        strcpy(L.elem[s].info, L.elem[j].info);
        s = j;
    }
    L.elem[s].key = rc.key;
    strcpy(L.elem[s].info, rc.info);

}


void HeapSort(SqList & L)
{
    ElemType rc;
    for(int i = L.length >> 1; i > 0; i--)
        HeapAdjust(L, i, L.length);
    for(int i = L.length; i > 1; i--)
    {
        rc.key = L.elem[1].key;
        strcpy(rc.info, L.elem[1].info);
        L.elem[1].key = L.elem[i].key;
        strcpy(L.elem[1].info, L.elem[i].info);
        L.elem[i].key = rc.key;
        strcpy(L.elem[i].info, rc.info);
        HeapAdjust(L, 1, i - 1);
    }

}

void Merge(SqList &src, SqList &dst, int u, int v, int t)
{
    int i(u), j(v), k(u);
    while(i < v && j <= t)
    {
        if(src.elem[i].key < src.elem[j].key)
            dst.elem[k++].key = src.elem[i++].key;
        else
            dst.elem[k++].key = src.elem[j++].key;
    }
    while(i < v)
        dst.elem[k++].key = src.elem[i++].key;
    while(j <= t)
        dst.elem[k++].key = src.elem[j++].key;
}


void MSort(SqList &L, SqList &tmp, int l, int r)
{
    if(l >= r) return ;
    int v = (l + r) / 2 + 1;
    MSort(L, tmp, l, v - 1);
    MSort(L, tmp, v, r);
    Merge(L, tmp, l, v, r);
    for(int i = l; i <= r; i++)
    {
        L.elem[i].key = tmp.elem[i].key;
        strcpy(L.elem[i].info, tmp.elem[i].info);
    }
}


void MergeSort(SqList &L)
{
    SqList tmp;
    InitList (tmp,  L.listsize);
    MSort(L, tmp, 1, L.length);
    DestroyList(tmp);
}

char info[maxn];

void solve()
{
    SqList La, Lb;
    int key;
    InitList(La, 200);
    InitList(Lb, 200);

    FILE *fp;
    if((fp = fopen("a.txt", "r")) == 0)
    {
        printf("打开“a.txt”文件失败");
        system("pause");
        return ;
    }
    for(int i = 1; i < La.listsize; i++)
    {
        info[0] = 0;
        if(fscanf(fp, "%d", &key) == EOF) break;
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

    //堆排序
    CopyList(Lb, La);
    HeapSort(Lb);
    printf("\n堆排序：\n");
    PrintList(Lb);
    printf("\n");

    //归并排序
    CopyList(Lb, La);
    MergeSort(Lb);
    printf("\n归并排序：\n");
    PrintList(Lb);
    printf("\n");

    DestroyList(La);
    DestroyList(Lb);

    system("pause");
}

int main()
{
    solve();

    return 0;
}
