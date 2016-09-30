#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define root 1, n, 1

const int maxn = 9999;
const int maxm = 1005;
const int mod = 10000;
const double eps = 1e-8;
const double pi = acos( -1.0);
const int inf = std::numeric_limits<int>::max();
const int INIT_SIZE	= 80;
const int INC_SIZE = 10;

class Queue
{
public:
    std::queue<int> Q;
    int maxsize;

public:
    Queue(int size)
    {
        maxsize = size;
    }

    int ClearQueue()
    {
        while(!Q.empty())
        	Q.pop();
    }

    int IsEmpty()
    {
        return Q.empty();
    }

    int IsFull()
    {
    	return (Q.size() == maxsize);
    }

    int GetHead()
    {
    	return Q.front();
    }

    bool EnQueue(int e)
    {
    	if(Q.size() == maxsize) return false;
    	Q.push(e); return true;
    }

    bool DeQueue()
    {
    	if(Q.empty()) return false;
    	Q.pop(); return true;
    }
};


int main()
{
    Queue q(5);
    int e;

    while(1)
    {
        fflush(stdin);
        printf("\n输入命令：1.队列空；2.队列满；3.入队；4.出队；5.清空；6.队头元素; 0.退出\n");
        char key = getchar();
        if(key == '0') break;
        switch(key)
        {
        case '1':
            if(q.IsEmpty()) printf("队列空!\n");
            else printf("队列不空!\n");
            break;

        case '2':
            if(q.IsFull()) printf("队列满!\n");
            else printf("队列不满!\n");
            break;

        case '3':
            printf("输入一个整数：");
            scanf("%d", &e);
            if(q.EnQueue(e)) printf("元素%d入队成功\n", e);
            else printf("元素%d入队失败\n", e);
            break;

        case '4':
            if(q.DeQueue()) printf("元素%d出队成功\n", e);
            else printf("出队失败\n", e);
            break;

        case '5':
            q.ClearQueue();
            break;

        case '6':
            if(!q.IsEmpty()) printf("队列头元素%d\n", q.GetHead());
            else printf("队列空!\n");
            break;
        }
    }
    system("pause");

    return 0;
}
