#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt  <<  1
#define rson m + 1, r, rt  <<  1 | 1
#define root 1, n, 1

const int maxm = 100005;
const int mod = 7;
const double eps = 1e-8;
const double pi = acos( - 1.0);
const int inf = std::numeric_limits<int>::max();
const int maxn = 80;
const int INC_SIZE = 10;

typedef int ElemType;

class SqList
{
public:
	ElemType *elem;
	int length;

private:
	int listsize;

public:
	SqList()
	{
		elem = new ElemType[maxn];
		length = 0;
		listsize = maxn;
	}

	~SqList()
	{
		delete[] elem;
	}

	void Clear()
	{
		length = 0;
	}

	int Find(ElemType e)
	{
		for(int k = 0; k < length; k++)
			if(elem[k] == e) return k + 1;
		return 0;
	}

	bool Insert(int i, ElemType e)
	{
		if(i < 1 || i > length + 1) return false;
		if(length >= listsize)
		{
			int newsize = listsize + INC_SIZE;
			ElemType *p = new ElemType[newsize];
			if(!p) return false;
			memcpy(p, elem, length * sizeof(ElemType));
			delete[] elem;
			elem = p;
			listsize = newsize;
		}

		
		for(int k = length; k >= i; k--)
			elem[k] = elem[k - 1];

		elem[i - 1] = e;
		length++;

		return true;
	}

	int Erase(int i, ElemType &e)
	{
		if(i < 0 || i >= length - 1) return false;
		for(int k = i; k < length - 1; k++)
			elem[k] = elem[k + 1];
		return true;
	}
};

ostream& operator << (ostream& os, const SqList& L)
{
	for(int i = 0; i < L.length; i++)
		os << L.elem[i] << ", ";
	os << endl;
}

void Merge(SqList &La, SqList Lb)
{
	int i;
	int length_a, length_b;
	ElemType e;

	length_a = La.length;
	length_b = Lb.length;

	for(i = 1; i <= length_b; i++)
	{
		e = Lb.elem[i - 1];
		if(!La.Find(e))
			La.Insert(++length_a, e);
	}
}


int main()
{
	FILE *fp1, *fp2;
	SqList La, Lb;
	int e, i;

	if((fp1 = fopen("a.txt", "r")) == 0 || (fp2 = fopen("b.txt", "r")) == 0 )
	{
		printf("打开文件失败");
		return  -1;
	}

	while(fscanf(fp1, "%d", &e) != EOF)
		La.Insert(La.length + 1, e);

	printf("\nLa: ");
	for(i = 0; i < La.length; i++)
		printf("%d, ", La.elem[i]);

	while(fscanf(fp2, "%d", &e) != EOF)
		Lb.Insert(Lb.length + 1, e);

	printf("\nLb: ");
	cout << Lb;
	printf("\nLb: ");
	for(i = 0; i < Lb.length; i++)
		printf("%d, ", Lb.elem[i]);
	cout << endl;

	Merge(La, Lb);
	printf("\nLa+Lb: ");
	for(i = 0; i < La.length; i++)
		printf("%d, ", La.elem[i]);
	cout << endl;

	system("pause");
	return 0;
}
