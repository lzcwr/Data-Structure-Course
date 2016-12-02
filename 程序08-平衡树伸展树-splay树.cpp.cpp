#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
// #define lson l, m, rt << 1
// #define rson m + 1, r, rt << 1 | 1
// #define root 1, n, 1
#define Key_value ch[ch[root][1]][0]

const int maxn = 50010;
const int mod = 1e9 + 7;
const double eps = 1e-8;
const double pi = acos(-1.0);
const int inf = 0x7f7f7f7f;
const int N = 200005;
const int INF = 1 << 28;
int a[N];

struct Node
{
    int val, sz;
    int sum, ml, mr, mc;
    Node *pre, *ch[2];
};

class Splay
{
public:
    Node *null, *root, *S[N], data[N];
    int cnt, top;

    Node *getNewNode(int x)
    {
        Node *p;
        if(top) p = S[top--];
        else p = &data[cnt++];
        p -> val = p -> sum = p -> ml = p -> mr = p -> mc = x;
        p -> sz = 1;
        p -> ch[0] = p -> ch[1] = p -> pre = null;
        return p;
    }

    void init()
    {
        cnt = top = 0;
        null = getNewNode(-INF);
        null -> sum = null -> sz = 0;
        root = getNewNode(-INF);
        root -> sum = 0;
        root -> ch[1] = getNewNode(INF);
        root -> ch[1] -> sum = 0;
        root -> ch[1] -> pre = root;
        update(root);
    }

    void update(Node *p)
    {
        p -> sz = p -> ch[0] -> sz + p -> ch[1] -> sz + 1;
        p -> sum = p -> ch[0] -> sum + p -> ch[1] -> sum + p -> val;
        p -> ml = max(p -> ch[0] -> ml, p -> ch[0] -> sum + p -> val + max(p -> ch[1] -> ml, 0));
        p -> mr = max(p -> ch[1] -> mr, p -> ch[1] -> sum + p -> val + max(p -> ch[0] -> mr, 0));
        p -> mc = max(p -> ch[0] -> mc, p -> ch[1] -> mc);
        p -> mc = max(p -> mc, max(p -> ch[0] -> mr + p -> ch[1] -> ml, 0) + p -> val);
        p -> mc = max(p -> mc, max(p -> ch[0] -> mr, p -> ch[1] -> ml) + p -> val);
    }

    void rotate(Node *x, int c)
    {
        Node *y = x -> pre;
        y -> ch[!c] = x -> ch[c];
        if(x -> ch[c] != null) x -> ch[c] -> pre = y;
        x -> pre = y -> pre;
        if(y -> pre != null)
        {
            if(y -> pre -> ch[0] == y) y -> pre -> ch[0] = x;
            else y -> pre -> ch[1] = x;
        }
        x -> ch[c] = y;
        y -> pre = x;
        if(y == root) root = x;
        update(y);
    }

    void splay(Node *x, Node *f)
    {
        while(x -> pre != f)
        {
            if(x -> pre -> pre == f)
                rotate(x, x -> pre -> ch[0] == x);
            else
            {
                Node *y = x -> pre;
                Node *z = y -> pre;
                if(z -> ch[0] == y)
                {
                    if(y -> ch[0] == x)
                        rotate(y, 1), rotate(x, 1);
                    else
                        rotate(x, 0), rotate(x, 1);
                }
                else
                {
                    if(y -> ch[1] == x)
                        rotate(y, 0), rotate(x, 0);
                    else
                        rotate(x, 1), rotate(x, 0);
                }
            }
        }
        update(x);
    }

    void select(int k, Node *f)
    {
        int tmp;
        Node *t = root;
        while(true)
        {
            tmp = t -> ch[0] -> sz;
            if(tmp + 1 == k) break;
            if(k <= tmp) t = t -> ch[0];
            else
            {
                k -= tmp + 1;
                t = t -> ch[1];
            }
        }
        splay(t, f);
    }

    void insert(int pos, int val)
    {
        Node *tmproot = getNewNode(val);
        select(pos - 1, null);
        select(pos, root);
        root -> ch[1] -> ch[0] = tmproot;
        tmproot -> pre = root -> ch[1];
        splay(root -> ch[1], null);
    }

    void del(int k)
    {
        select(k, null);
        Node *old_root = root;
        root = root -> ch[1];
        root -> pre = null;
        select(1, null);
        root -> ch[0] = old_root -> ch[0];
        root -> ch[0] -> pre = root;
        update(root);
        S[++top] = old_root;
    }

    void replace(int x, int y)
    {
        select(x, null);
        root -> val = y;
        update(root);
    }

    Node *build(int l, int r)
    {
        if(l > r) return null;
        int m = (l + r) >> 1;
        Node *p = getNewNode(a[m]);
        p -> ch[0] = build(l, m-1);
        if(p -> ch[0] != null)
            p -> ch[0] -> pre = p;
        p -> ch[1] = build(m+1, r);
        if(p -> ch[1] != null)
            p -> ch[1] -> pre = p;
        update(p);
        return p;
    }

    void print(Node* tree)
    {
        if(tree != NULL)
        {
            if(tree -> val == INF || tree -> val == -INF)
                printf("*(");
            else printf("%d(", tree -> val);
            // cout << tree -> mc << '(';
            print(tree -> ch[0]);
            printf(",");
            print(tree -> ch[1]);
            printf(")");
        }
        else printf("#");
    }
    void print() { print(root); }
};

Splay sp;

void solve()
{
    int n, m, x, y;
    sp.init();
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    Node *troot = sp.build(1, n);
    sp.root -> ch[1] -> ch[0] = troot;
    troot -> pre = sp.root -> ch[1];
    sp.update(sp.root -> ch[1]);
    sp.update(sp.root);
    sp.splay(sp.root -> ch[1], sp.null);
    
    sp.print();
}

int main()
{
// #ifndef ONLINE_JUDGE
//     freopen("in.txt", "r", stdin);
//     freopen("out.txt", "w", stdout);
// #endif

    solve();

// #ifndef ONLINE_JUDGE
//     fclose(stdin);
//     fclose(stdout);
//     system("out.txt");
// #endif

    return 0;
}