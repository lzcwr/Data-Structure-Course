#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() /(double)CLOCKS_PER_SEC);
// #define lson l, m, rt  <<  1
// #define rson m + 1, r, rt  <<  1 | 1
// #define root 1, n, 1
#define lson T -> lchild
#define rson T -> rchild

const int maxn = 205;
const int maxm = 1e5 + 5;
const int mod = 10000;
const double eps = 1e-8;
const int inf = 0x3f3f3f3f;
const int MAX_N = 50005;

typedef struct BiTNode
{
    char   data;       
    struct BiTNode  *lchild;    
    struct BiTNode  *rchild;    
} BiTNode, *BiTree;

int build(BiTree &T, char *str, int &pos)
{
    char ch = str[pos];
    if(ch == 0)
    {
        T = 0;
        return false;
    }

    pos++;
    if(ch == '#') T = 0;
    else
    {
        T = new BiTNode;
        if(!T) return false;

        T -> data = ch;
        int l_state, r_state;
        l_state = build(lson, str, pos);
        r_state = build(rson, str, pos);

        if(!l_state || !r_state) return false;
    }

    return true;
}
void PrintBiTree(BiTree &T)
{
    if(T)
    {
        printf("%c(", T -> data);

        PrintBiTree(lson);
        printf(", ");

        PrintBiTree(rson);
        printf(")");
    }
    else printf("#");
}

void DestroyBiTree(BiTree &T)
{
    if(T)
    {
        DestroyBiTree(lson);
        DestroyBiTree(rson);
        delete T;
        T = 0;
    }
}
void PreOrder(BiTree T)
{
    if(T)
    {
        printf("%c", T -> data);
        PreOrder(lson);
        PreOrder(rson);
    }
}
void InOrder(BiTree T)
{
    if(T)
    {
        InOrder(lson);
        printf("%c", T -> data);
        InOrder(rson);
    }
}
void PostOrder(BiTree T)
{
    if(T)
    {
        PostOrder(lson);
        PostOrder(rson);
        printf("%c", T -> data);
    }
}
void CountLeaf(BiTree T,  int &cnt)
{
    if(T)
    {
        if((!lson)&&(!rson))
            cnt++;
        CountLeaf(lson, cnt);
        CountLeaf(rson, cnt);
    }
}
int Depth(BiTree T)
{
    int dep(0);
    if(!T) return 0;
    else
    {
        int depthLeft = Depth(lson);
        int depthRight = Depth(rson);
        dep = 1 + max(depthLeft, depthRight);
    }

    return dep;
}
BiTree CopyTree(BiTree T)
{
    if(!T) return 0;
    BiTree newT = new BiTNode;
    if(!newT) return 0;
    newT -> data = T -> data;
    newT -> lchild = CopyTree(lson);
    newT -> rchild = CopyTree(rson);

    return newT;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    BiTree T;
    char buf[maxn];
    int pos(0), cnt(0);

    printf("输入二叉树，以\'#\'表示空树，如\"A#B##\"表示\"A(#,B(#,#))\"：\n");
    gets(buf);

    build(T, buf, pos);
    PrintBiTree(T);
    printf("\n");

    CountLeaf(T, cnt);
    printf("叶子节点个数：%d\n", cnt);

    int depth = Depth(T);
    printf("二叉树的深度：%d\n", depth);

    BiTree newT = CopyTree(T);
    printf("复制的二叉树：");
    PrintBiTree(newT);
    printf("\n");

    printf("先序遍历：");
    PreOrder(T);
    printf("\n");

    printf("中序遍历：");
    InOrder(T);
    printf("\n");

    printf("后序遍历：");
    PostOrder(T);
    printf("\n");

    DestroyBiTree(T);
    DestroyBiTree(newT);

#ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
    system("out.txt");
#endif

    return 0;
}

