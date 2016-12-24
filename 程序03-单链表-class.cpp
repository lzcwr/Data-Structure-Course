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

class LinkList
{
public:
    Link head, tail;
    int length;
    Link cnr;

public:
    LinkList()
    {
        head = new LNode;
        if(!head) exit(-1);

        head -> nxt = 0;
        tail = head;
        cnr = head;
        length = 0;
    }
    ~LinkList()
    {
        Link p;
        while(head)
        {
            p = head -> nxt;
            delete head;
            head = p;
        }
    }

    int LocatePos(int i)
    {
        int k(0);
        cnr = head;
        while(cnr -> nxt && k < i)
        {
            cnr = cnr -> nxt;
            k++;
        }

        if(k != i) return 0;
        return 1;
    }

    int InsertAfter(int e)
    {
        Link s;
        if(!cnr) return false;
        s = new LNode;

        if(!s) return false;
        s -> data = e;
        s -> nxt = cnr -> nxt;
        cnr -> nxt = s;

        if(tail == cnr) tail = s;
        cnr = s;
        length++;
    }

    void Print()
    {
        Link p;
        p = head;
        while(p -> nxt)
        {
            p = p -> nxt;
            printf("%d, ", p -> data);
        }
    }

    bool LocateElem(int e);
    int ListLenth();
    void ListReverse();
};


bool LinkList::LocateElem(int e)
{
    Link p;

    p = head -> nxt;
    while(p)
    {
        if(p -> data == e)
        {
            cnr = p;
            return true;
        }
        p = p -> nxt;
    }
    return false;
}

int LinkList::ListLenth()
{
    return length;
}

void LinkList::ListReverse()
{
    Link p, q;
    p = head -> nxt;
    tail = p;
    head -> nxt = 0;
    while(p)
    {
        q = p -> nxt;
        p -> nxt = head -> nxt;
        head -> nxt = p;
        p = q;
    }
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
        return 0;
    }

    L.LocatePos(0);
    while(fscanf(fp, "%d", &e) != EOF)
        L.InsertAfter(e);

    printf("原始链表: ");
    L.Print();

    printf("\n链表长度：%d\n", L.ListLenth());

    printf("\n输入要查找的数: ");
    scanf("%d", &e);
    if(L.LocateElem(e) == 1)
        printf("查找成功!\n");
    else
        printf("查找失败!\n");

    L.ListReverse();
    printf("\n逆转链表: ");
    L.Print();
    
    system("pause");

    return 0;
}
