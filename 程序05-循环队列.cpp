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
		printf("\n�������1.���пգ�2.��������3.��ӣ�4.���ӣ�5.��գ�6.��ͷԪ��; 0.�˳�\n");
		char key = getchar();
		if(key == '0')
			break;
		switch(key)
		{
		case '1':
			if(Q.empty()) printf("���п�!\n");
			else printf("���в���!\n");
			break;

		case '2':
			if(QueueFull(Q)) printf("������!\n");
			else printf("���в���!\n");
			break;

		case '3':
			printf("����һ��������");
			scanf("%d", &e);
			if(QueueFull(Q)) printf("Ԫ��%d���ʧ��\n", e);
			else
			{
				Q.push(e);
				printf("Ԫ��%d��ӳɹ�\n", e);
			}
			break;

		case '4':
			e = Q.front();
			Q.pop();
			printf("Ԫ��%d���ӳɹ�\n", e);
			break;

		case '5':
			ClearQueue();
			break;

		case '6':
			if(!Q.empty()) printf("����ͷԪ��%d\n", Q.front());
			else printf("���п�\n");
			break;
		}
	}
	system("pause");

	return 0;
}