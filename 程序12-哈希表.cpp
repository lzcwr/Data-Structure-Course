#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define root 1, n, 1
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

typedef char* KeyType;

struct ElemType
{
    KeyType name;
    char * info;
};

struct HashTable
{
    ElemType *elem;
    int cnt;
    int size;
};

bool InitHashTable(HashTable &HT, int size)
{
    HT.elem = new ElemType[size];
    if(!HT.elem) return false;
    HT.size = size; HT.cnt = 0;
    for(int i = 0; i < HT.size; i++)
    {
        HT.elem[i].name = 0;
        HT.elem[i].info = 0;
    }
    return true;
}

void DestroyHashTable(HashTable &HT)
{
    if(!HT.elem) return;
    for(int i = 0; i < HT.size; i++)
        if(HT.elem[i].name)
            delete HT.elem[i].name;
    delete HT.elem;
    HT.elem = 0; HT.cnt = 0; HT.size = 0;
}

int Hash(HashTable &HT, KeyType key)
{
    char *p = key;
    int sum = 0;
    while(*p) sum += *p++;
    return abs(sum) % HT.size;
}

void collision(HashTable &HT, int &p, int c)
{
    p += 1;
    p %= HT.size;
}

void collision2(HashTable &HT, int h, int i, int &p)
{
    p = h + i;
    p %= HT.size;
}

bool SearchHash(HashTable &HT, KeyType key, int &p, int &c)
{
    p = Hash(HT, key);
    c = 0;
    while(HT.elem[p].name != 0 && strcmp(HT.elem[p].name, key) != 0)
        collision(HT, p, ++c);

    if(HT.elem[p].name == 0)
        return false;
    return true;
}

bool InsertHash(HashTable &HT, ElemType e)
{
    int c(0), p;
    if(SearchHash(HT, e.name, p, c))
        return false;
    else if(c < HT.size >> 1)
    {
        HT.elem[p].name = new char[strlen(e.name) + 1];
            strcpy(HT.elem[p].name, e.name);

        HT.elem[p].info = new char[strlen(e.info) + 1];
            strcpy(HT.elem[p].info, e.info);
        return true;
    }
    else return false;
}

void solve()
{
    HashTable HT;
    char key[40], info[40];
    ElemType e;
    e.name = key; e.info = info;
    FILE *fp;

    if((fp = fopen("哈希表.txt", "r")) == 0)
    {
        printf("打开“哈希表.txt”文件失败");
        system("pause");
        return ;
    }
    InitHashTable(HT, 101);
    for(int i = 0; i < HT.size; i++)
    {
        if(fscanf(fp, "%s%s", info, key) == EOF)
            break;

        if(InsertHash(HT, e))
            printf("\n插入成功\n");
        else
            printf("\n插入失败\n");

    }
    fclose(fp);

    printf("输入要查找的人名：");
    fflush(stdin);
    gets(key);
    int p, c(0);
    if(SearchHash(HT, key, p, c))
        printf("\n查找成功！%s：位置，%d；冲突，%d\n", HT.elem[p].name, p, c);
    else
        printf("\n查找失败\n");
    DestroyHashTable(HT);
    printf("\n程序结束，按任意键返回\n");
    system("pause");
}

int main()
{
    solve();

    return 0;
}