#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define root 1, n, 1

const int maxm = 100005;
const int mod = 7;
const double eps = 1e-8;
const double pi = acos( - 1.0);
const int inf = std::numeric_limits<int>::max();
const int maxn = 80;
const int INC_SIZE = 10;

typedef struct LNode
{
    int data;
    LNode *nxt;
} LNode, *Link, *Position;

typedef struct
{
    Link head, tail;
    int length;
    Link cur;
} LinkList;

bool InitList(LinkList &L)
{
    L.head = new LNode;
    if(!L.head) return false;
    L.head -> nxt = 0;

    L.tail = L.head;
    L.length = 0;
    L.cur = L.head;
    return true;
}

void DestroyList(LinkList &L)
{
    Link p;
    p = L.head;
    while(p)
    {
        L.head = L.head -> nxt;
        delete p;
        p = L.head;
    }
}

void ClearList(LinkList &L)
{
    Link p;
    while(L.head -> nxt)
    {
        p = L.head -> nxt;
        L.head -> nxt = p -> nxt;
        delete p;
    }
}

bool LocatePos( LinkList &L, int i )
{
    int k(0);
    L.cur = L.head;
    while(L.cur -> nxt && k < i)
    {
        L.cur = L.cur -> nxt;
        k++;
    }

    if(k != i) return false;
    return true;
}

int InsertAfter(LinkList &L, int e)
{
    Link s;

    if(!L.cur)
        return 0;

    s = new LNode;
    if(!s) return 0;
    s -> data = e;

    s -> nxt = L.cur -> nxt;
    L.cur -> nxt = s;

    if(L.tail == L.cur)
        L.tail = s;

    L.cur = s;
    L.length++;
    return 1;
}

void Show(LinkList L)
{
    Link p;

    printf("链表有%d个元素：", L.length);
    p = L.head;
    while(p -> nxt)
    {
        p = p -> nxt;
        printf("%d, ", p -> data);
    }
    printf("\n\n");
}

int LocateElem(LinkList &L, int e)
{
    L.cur = L.head;
    for(int i = 0; i <= L.length; i++)
    {
        if(L.cur -> data==e) return i;
        else L.cur = L.cur -> nxt;
    }
    return 0;
}

int ListLenth(LinkList L)
{
    int i = 0;
    L.cur = L.head;
    while(L.cur != L.tail)
    {
        L.cur = L.cur -> nxt;
        i++;
    }
    return i;
}

void ListReverse(LinkList &L)
{
    Link q, p, temp;
    L.length=ListLenth(L);
    q = L.head;
    p = q -> nxt;
    temp = p -> nxt;
    p -> nxt = NULL;
    for(int i = 1; i < L.length; i++)
    {
        q = temp -> nxt;
        temp -> nxt = p;
        p = temp;
        temp = q;
    }

    L.head -> nxt = p;
}

int main()
{
    FILE *fp;
    LinkList L;
    int e;

    if((fp = fopen("a.txt", "r")) == 0)
    {
        printf("打开文件失败");
        system("pause");
        return -1;
    }

    if(!InitList(L))
    {
        printf("初始化链表失败\n");
        system("pause");
        return -2;
    }

    LocatePos(L, 0);
    while(fscanf(fp, "%d", &e) != EOF)
        InsertAfter(L, e);

    printf("原始链表\n");
    Show(L);

    printf("链表长度：%d\n", ListLenth(L));

    printf("输入要查找的数: ");
    scanf("%d", &e);
    if(LocateElem(L, e))
        printf("元素%d--%d在链表中\n", e, L.cur -> data);
    else
        printf("元素%d不在链表中\n", e);

    ListReverse(L);
    printf("\n逆转链表\n");
    Show(L);

    DestroyList(L);
    system("pause");

    return 0;
}

