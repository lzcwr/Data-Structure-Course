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
	int	data;
	LNode *next;
} LNode, *Link, *Position;

typedef struct
{
	Link head, tail;
	int lenth;
	Link current;
} LinkList;

bool InitList(LinkList &L)
{
	L.head = new LNode;
	if(!L.head) return false;
	L.head -> next = 0;

	L.tail = L.head;
	L.lenth = 0;
	L.current = L.head;
	return true;
}

{
	Link p;
	p = L.head;
	while(p)
	{
		L.head = L.head -> next;
		delete p;
		p = L.head;
	}
}

void ClearList(LinkList &L)
{
	Link p;
	while(L.head -> next)
	{
		p = L.head -> next;
		L.head -> next = p -> next;
		delete p;
	}
}

bool LocatePos( LinkList &L, int i )
{
	int k(0);
	L.current = L.head;
	while(L.current -> next && k < i)
	{
		L.current = L.current -> next;
		k++;
	}

	if(k != i) return false;
	return true;
}

int InsertAfter(LinkList &L, int e)
{
	Link s;

	if(!L.current)
		return 0;

	s = new LNode;
	if(!s) return 0;
	s -> data = e;

	s -> next = L.current -> next;
	L.current -> next = s;

	if(L.tail == L.current)
		L.tail = s;

	L.current = s;
	L.lenth++;
	return 1;
}

void Show(LinkList L)
{
	Link p;

	printf("������%d��Ԫ�أ�", L.lenth);
	p = L.head;
	while(p -> next)
	{
		p = p -> next;
		printf("%d, ", p -> data);
	}
	printf("\n\n");
}

int LocateElem(LinkList &L, int e)
{
	L.current = L.head;
	for(int i = 0; i <= L.lenth; i++)
	{
		if(L.current -> data==e) return i;
		else L.current = L.current -> next;
	}
	return 0;
}

int ListLenth(LinkList L)
{
	int i = 0;
	L.current = L.head;
	while(L.current != L.tail)
	{
		L.current = L.current -> next;
		i++;
	}
	return i;
}

void ListReverse(LinkList &L)
{
	Link q, p, temp;
	L.lenth=ListLenth(L);
	q = L.head;
	p = q -> next;
	temp = p -> next;
	p -> next = NULL;
	for(int i = 1; i < L.lenth; i++)
	{
		q = temp -> next;
		temp -> next = p;
		p = temp;
		temp = q;
	}

	L.head -> next = p;
}

int main()
{
	FILE *fp;
	LinkList L;
	int e;

	if((fp = fopen("a.txt", "r")) == 0)
	{
		printf("���ļ�ʧ��");
		system("pause");
		return -1;
	}

	if(!InitList(L))
	{
		printf("��ʼ������ʧ��\n");
		system("pause");
		return -2;
	}

	LocatePos(L, 0);
	while(fscanf(fp, "%d", &e) != EOF)
		InsertAfter(L, e);

	printf("ԭʼ����\n");
	Show(L);

	printf("�����ȣ�%d\n", ListLenth(L));

	printf("����Ҫ���ҵ���: ");
	scanf("%d", &e);
	if(LocateElem(L, e))
		printf("Ԫ��%d--%d��������\n", e, L.current -> data);
	else
		printf("Ԫ��%d����������\n", e);

	ListReverse(L);
	printf("\n��ת����\n");
	Show(L);

	DestroyList(L);
	system("pause");

	return 0;
}

