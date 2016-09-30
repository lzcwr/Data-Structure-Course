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
        printf("\n�������1.���пգ�2.��������3.��ӣ�4.���ӣ�5.��գ�6.��ͷԪ��; 0.�˳�\n");
        char key = getchar();
        if(key == '0') break;
        switch(key)
        {
        case '1':
            if(q.IsEmpty()) printf("���п�!\n");
            else printf("���в���!\n");
            break;

        case '2':
            if(q.IsFull()) printf("������!\n");
            else printf("���в���!\n");
            break;

        case '3':
            printf("����һ��������");
            scanf("%d", &e);
            if(q.EnQueue(e)) printf("Ԫ��%d��ӳɹ�\n", e);
            else printf("Ԫ��%d���ʧ��\n", e);
            break;

        case '4':
            if(q.DeQueue()) printf("Ԫ��%d���ӳɹ�\n", e);
            else printf("����ʧ��\n", e);
            break;

        case '5':
            q.ClearQueue();
            break;

        case '6':
            if(!q.IsEmpty()) printf("����ͷԪ��%d\n", q.GetHead());
            else printf("���п�!\n");
            break;
        }
    }
    system("pause");

    return 0;
}
