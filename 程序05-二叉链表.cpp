#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
// #define lson l, m, rt << 1
// #define rson m + 1, r, rt << 1 | 1
#define lson rt -> lchild
#define rson rt -> rchild
#define root 1, n, 1

const int maxn = 505;
const int maxm = 1005;
const int mod = 1e6 + 3;
const double eps = 1e-8;
const double pi = acos(-1.0);
// const int inf = std::numeric_limits<int>::max();
const int inf = 0x3f3f3f3f;

struct BitNode
{
    char data;
    BitNode *lchild, *rchild;

    BitNode() {}
    BitNode(char a, BitNode* l, BitNode* r)
    {
        data = a; lchild = l; rchild = r;
    }
};

typedef BitNode *BitTree;

bool build(BitTree &rt, char *str, int &pos)
{
    char ch = str[pos];
    if(ch == '0')
    {
        rt = 0;
        return false;
    }

    pos++;
    if(ch == '#') rt = 0;
    else
    {
        rt = new BitNode;
        if(!rt) return false;
        rt -> data = ch;

        bool l_state = build(lson, str, pos);
        bool r_state = build(rson, str, pos);

        if(!l_state || !r_state) return false;
    }
    return true;
}

void print(BitTree &rt)
{
    if(rt)
    {
        printf("%c(", rt -> data);

        print(lson);
        printf(", ");
        print(rson);
        printf(")");
    }
    else printf("#");
}

void destroy(BitTree &rt)
{
    if(rt)
    {
        destroy(lson);
        destroy(rson);
        delete rt;
        rt = 0;
    }
}

void pre_order(BitTree rt)
{
    if(rt)
    {
        printf("%c", rt -> data);
        pre_order(lson);
        pre_order(rson);
    }
}

void in_order(BitTree rt)
{
    if(rt)
    {
        in_order(lson);
        printf("%c", rt -> data);
        in_order(rson);
    }
}

void post_order(BitTree rt)
{
    if(rt)
    {
        post_order(lson);
        post_order(rson);
        printf("%c", rt -> data);
    }
}

void count_leaf(BitTree rt, int &cnt)
{
    if(rt)
    {
        if(!lson && !rson) cnt++;
        count_leaf(lson, cnt);
        count_leaf(rson, cnt);
    }
}

int get_depth(BitTree rt)
{
    int ret(0);
    if(!rt) return 0;
    else
    {
        int left_depth = get_depth(lson);
        int right_depth = get_depth(rson);
        ret = 1 + max(left_depth, right_depth);
    }
    return ret;
}

BitTree copy(BitTree rt)
{
    if(!rt) return 0;
    BitTree new_root = new BitNode;
    if(!new_root) return 0;

    new_root -> data = rt -> data;
    new_root -> lchild = copy(lson);
    new_root -> rchild = copy(rson);

    return new_root;
}

void solve()
{
    BitTree T;
    char buf[maxn];
    int pos(0), cnt(0);

    printf("输入二叉树，以\'#\'表示空树，如\"A#B##\"表示\"A(#,B(#,#))\"：\n");
    gets(buf);

    build(T, buf, pos);
    print(T);
    printf("\n");

    count_leaf(T, cnt);
    printf("叶子节点个数：%d\n", cnt);

    int depth = get_depth(T);
    printf("二叉树的深度：%d\n", depth);

    BitTree newT = copy(T);
    printf("复制的二叉树：");
    print(newT);
    printf("\n");

    printf("先序遍历：");
    pre_order(T);
    printf("\n");

    printf("中序遍历：");
    in_order(T);
    printf("\n");

    printf("后序遍历：");
    post_order(T);
    printf("\n");

    destroy(T);
    destroy(newT);
}


int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    solve();

#ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
    system("out.txt");
#endif

    return 0;
}
