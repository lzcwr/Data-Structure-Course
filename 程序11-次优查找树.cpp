#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

struct Element
{
    char key;
    double weight;
    Element(){}
    Element(char a, double b)
    {
        key = a;
        weight = b;
    }
};

struct SSTable
{
    Element *elem;
    int lenth;
    int size;
};

struct BiTNode
{
    Element data;
    BiTNode* lchild;
    BiTNode* rchild;
};

typedef BiTNode *BiTree;
typedef BiTree SOSTree;

bool InitSSTable(SSTable &ST, int size)
{
    ST.elem = new Element[size + 1];
    if(!ST.elem) return false;

    ST.lenth = 0;
    ST.size = size;

    return true;
}

void DestroySSTable(SSTable &ST)
{
    delete ST.elem;
    ST.lenth = 0;
    ST.size = 0;
}

void DestroyBiTree(BiTree &T)
{
    if(!T) return;

    DestroyBiTree(T -> lchild);
    DestroyBiTree(T -> rchild);

    delete T;
    T = 0;
}

void PrintBiTree(BiTree &T)
{
    if(T)
    {
        printf("%c(", T -> data.key);

        PrintBiTree(T -> lchild);
        printf(",");

        PrintBiTree(T -> rchild);
        printf(")");
    }
    else printf("#");
}

bool SecondOptimal(BiTree &T, Element R[], double sw[], int l, int r)
{
    if(l > r) return false;
    int mink = l;
    double minP = fabs(sw[r] - sw[l]);
    double deltaP;
    for(int i = l + 1 ; i <= r ; i++)
    {
        deltaP = fabs(sw[r] + sw[l - 1] - sw[i - 1] - sw[i]);
        if(deltaP < minP)
        {
            minP = deltaP;
            mink = i;
        }
    }

    T = new BiTNode;
    if(!T) return false;
    T -> data.key = R[mink].key;
    T -> data.weight = R[mink].weight;

    if(mink == l)
        T -> lchild = 0;
    else
        SecondOptimal(T -> lchild, R, sw, l, mink-1);
    if(mink == r)
        T -> rchild = 0;
    else
        SecondOptimal(T -> rchild, R, sw, mink+1, r);

    return true;
}

bool SO2(BiTree &T, Element R[], double sw[], int l, int r)
{
    if(l > r) return false;
    int mink = l;
    double minP = fabs(sw[r] - sw[l]);
    double deltaP;
    for(int i = l + 1 ; i <= r; i++)
    {
        deltaP = fabs(sw[r] + sw[l - 1] - sw[i - 1] - sw[i]);
        if(deltaP < minP)
        {
            minP = deltaP;
            mink = i;
        }
    }
    int k = mink;
    if(l < mink && R[mink - 1].weight > R[k].weight)
        k = mink - 1;
    if(mink < r && R[mink + 1].weight > R[k].weight)
        k = mink + 1;
    mink = k;

    T = new BiTNode;
    if(!T) return false;
    T -> data.key = R[mink].key;
    T -> data.weight = R[mink].weight;

    if(mink == l)
        T -> lchild = 0;
    else
        SO2(T -> lchild, R, sw, l, mink - 1);
    if(mink == r)
        T -> rchild = 0;
    else
        SO2(T -> rchild, R, sw, mink + 1, r);
    return true;
}

bool CreateSOSTree(SOSTree &T, SSTable &ST)
{
    if(ST.lenth == 0) T = NULL;
    else
    {
        double *sw = new double[ST.lenth + 1];
        double sum = 0;
        sw[0] = 0;
        for(int i = 1; i <= ST.lenth; i++)
        {
            sum += ST.elem[i].weight;
            sw[i] = sum;
        }
        SO2(T, ST.elem, sw, 1, ST.lenth);
        delete sw;
    }
    return true;
}

double PH(SOSTree &T, int depth)
{
    if(!T) return 0;
    double sum;
    sum = depth * T -> data.weight;
    sum += PH(T -> lchild, depth + 1);
    sum += PH(T -> rchild, depth + 1);
    return sum;
}

BiTNode* SOSSearch(SOSTree &T, char key)
{
    if(!T) return 0;
    if(T -> data.key == key) return T;
    BiTNode* p = SOSSearch(T -> lchild, key);
    if(p) return p;
    return SOSSearch(T -> rchild, key);
}

void solve()
{
    BiTree T = 0;
    SSTable ST;
    FILE *fp;
    if((fp = fopen("次优查找树的有序表数据.txt", "r")) == 0)
    {
        printf("打开“次优查找树的有序表数据.txt”文件失败");
        system("pause");
        return ;
    }
    InitSSTable(ST, 200);
    for(int i = 0; i < ST.size; i++)
    {
        char key[20];
        double weight;

        if(fscanf(fp, "%s%lf", key, &weight) == EOF)
            break;

        ST.lenth++;
        ST.elem[ST.lenth].key = key[0];
        ST.elem[ST.lenth].weight = weight;
    }
    fclose(fp);

    if(CreateSOSTree(T, ST) == false)
        printf("创建次优二叉树失败\n");
    else
    {
        printf("次优二叉树：\n");
        PrintBiTree(T);
        printf("\n");

        int depth = 1;
        printf("\nPH值：%4.2f\n", PH(T, depth));

        printf("\n输入要查找的关键字: ");
        fflush(stdin);
        char key = getchar();

        BiTNode* p = SOSSearch(T, key);
        if(p)
            printf("\n%c--%3.1f\n", p -> data.key, p -> data.weight);
        else
            printf("\n%c没有找到\n", key);
    }

    DestroyBiTree(T);
    DestroySSTable(ST);

    printf("\n程序结束，按任意键返回\n");
    system("pause");
}

int main()
{
    solve();

    return 0;
}