#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt  <<  1
#define rson m + 1, r, rt  <<  1 | 1
#define root 1, n, 1

const int maxn = 9999;
const int maxm = 1005;
const int mod = 10000;
const double eps = 1e-8;
const double pi = acos( -1.0);
const int inf = std::numeric_limits<int>::max();
const int INIT_SIZE	= 80;
const int INC_SIZE = 10;

std::queue<int> Q;
int maxsize;

void InitQueue(std::queue<int> Q, int e)
{
	maxsize = e;
}

void ClearQueue()
{
	while(!Q.empty())
		Q.pop();
}

bool QueueEmpty(std::queue<int> Q)
{
	return Q.empty();
}

bool QueueFull(std::queue<int> Q)
{
	return (Q.size() == maxsize);
}

int GetHead(std::queue<int> Q)
{
	return Q.front();
}

bool EnQueue(int e)
{
	if(Q.size() == maxsize) return false;
	Q.push(e);
	return true;
}

bool DeQueue(int e)
{
	if(Q.front() != e) return false;
	Q.pop();
	return true;
}

int main()
{
	int e;
	InitQueue(Q, 5);
	while(true)
	{
		fflush(stdin);
		printf("\n输入命令：1.队列空；2.队列满；3.入队；4.出队；5.清空；6.队头元素; 0.退出\n");
		char key = getchar();
		if(key == '0')
			break;
		switch(key)
		{
		case '1':
			if(Q.empty()) printf("队列空!\n");
			else printf("队列不空!\n");
			break;

		case '2':
			if(QueueFull(Q)) printf("队列满!\n");
			else printf("队列不满!\n");
			break;

		case '3':
			printf("输入一个整数：");
			scanf("%d", &e);
			if(QueueFull(Q)) printf("元素%d入队失败\n", e);
			else
			{
				Q.push(e);
				printf("元素%d入队成功\n", e);
			}
			break;

		case '4':
			e = Q.front();
			Q.pop();
			printf("元素%d出队成功\n", e);
			break;

		case '5':
			ClearQueue();
			break;

		case '6':
			if(!Q.empty()) printf("队列头元素%d\n", Q.front());
			else printf("队列空\n");
			break;
		}
	}
	system("pause");

	return 0;
}