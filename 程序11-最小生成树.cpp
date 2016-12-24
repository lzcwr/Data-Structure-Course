#include <bits/stdc++.h>
#ifdef __WINDOWS_
    #include <windows.h>
#endif
using namespace std;

#define showtime printf("time = %.15f\n", clock() / (double)CLOCKS_PER_SEC);
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define root 1, n, 1

const int maxn = 20;

struct ArcNode
{
    int adjvex;
    unsigned int weight;
    struct ArcNode *nextarc;
};
typedef ArcNode *ArcLink;

typedef struct VexNode
{
    char data;
    bool vis;
    ArcLink firstarc;
} VexNode, *VexLink;

struct Graph
{
    VexNode *vex;
    int vexnum; 
    int vexsize;
    int arcnum; 
    unsigned char kind; 
};

void InitGraph(Graph &G, int n)
{
    if(n < 1) return ;
    G.vex = new VexNode[n + 1];
    if(!G.vex) return ;
    G.vexnum = 0;
    G.arcnum = 0;
    G.vexsize = n;
}

void DestroyGraph(Graph &G)
{
    for(int i = 1; i < G.vexnum; i++)
    {
        ArcLink p = G.vex[i].firstarc, q;
        while(p)
        {
            q = p;
            p = p -> nextarc;
            delete q;
        }
    }

    delete[] G.vex;
    G.vex = 0;
    G.vexnum = 0;
    G.vexsize = 0;
}

int LocateVex(Graph &G, char v)
{
    for(int i = 1; i <= G.vexnum; i++)
        if(v == G.vex[i].data) return i;
    return 0;
}

bool InsertVextex(Graph &G, char v)
{
    if(G.vexnum >= G.vexsize)
    {
        VexNode *newbuf = new VexNode[(G.vexsize + 10) + 1];
        for(int i = 1; i <= G.vexnum; i++)
        {
            newbuf[i].data = G.vex[i].data;
            newbuf[i].firstarc = G.vex[i].firstarc;
        }
        delete[] G.vex;
        G.vex = newbuf;
        G.vexsize = G.vexsize +10;
    }
    if(LocateVex(G, v) != 0) return false;
    G.vex[++G.vexnum].data = v;
    G.vex[G.vexnum].firstarc = 0;
    return true;
}

bool InsertArc(Graph &G, char v1, char v2, int weight)
{
    if(v1 == v2) return false;
    int n1 = LocateVex(G, v1);
    if(n1 == 0)
    {
        if(!InsertVextex(G, v1)) return false;
        n1 = LocateVex(G, v1);
    }
    int n2 = LocateVex(G, v2);
    if(n2 == 0)
    {
        if(!InsertVextex(G, v2)) return false;
        n2 = LocateVex(G, v2);
    }
    ArcNode *p;
    bool find;
    p = G.vex[n1].firstarc;
    while(p)
    {
        if(p -> adjvex == n2)
        {
            p -> weight = weight;
            break;
        }
        p = p -> nextarc;
    }
    if(!p)
    {
        p = new ArcNode;
        if(!p) return false;
        p -> adjvex = n2;
        p -> weight = weight;
        p -> nextarc = G.vex[n1].firstarc;
        G.vex[n1].firstarc = p;
    }
    p = G.vex[n2].firstarc;
    while(p)
    {
        if(p -> adjvex == n1)
        {
            p -> weight = weight;
            break;
        }
        p = p -> nextarc;
    }
    if(!p)
    {
        p = new ArcNode;
        if(!p) return false;
        p -> adjvex = n1;
        p -> weight = weight;
        p -> nextarc = G.vex[n2].firstarc;
        G.vex[n2].firstarc = p;
    }
    return true;
}

void PrintGraph(Graph &G)
{
    for(int i = 1; i < G.vexnum; i++)
    {
        printf("顶点%d, %c：", i, G.vex[i].data);
        ArcLink p = G.vex[i].firstarc;
        while(p)
        {
            printf("%c%c-%d, ", G.vex[i].data, G.vex[p -> adjvex].data, p -> weight);
            p = p -> nextarc;
        }
        printf("\n");
    }
}

void Prim(Graph G, char v0)
{
    char *adjvex; unsigned int *lowcost; bool *flag; 
    int k = LocateVex (G, v0);
    if(k == -1) return;
    int sum(0);
    for(int i = 0; i < G.vexnum; i++)
    {
        ArcLink p = G.vex[i].firstarc;
        while(p)
        {
            sum += p -> weight;
            p = p -> nextarc;
        }
    }
    adjvex = new char[G.vexnum];
    lowcost = new unsigned int[G.vexnum];
    flag = new bool[G.vexnum];
    for (int i = 0; i < G.vexnum; i++)
    {
        flag[i] = false;
        lowcost[i] = sum;
    }
    flag[k] = true; adjvex[k] = v0;
    ArcLink p = G.vex[k].firstarc;
    while(p)
    {
        adjvex[p -> adjvex] = G.vex[k].data;
        lowcost[p -> adjvex] = p -> weight;
        p = p -> nextarc;
    }
    for(int i = 1; i <= G.vexnum; i++)
    {
        unsigned int min = sum;
        k = -1;
        for(int j = 0; j < G.vexnum; j++)
        {
            if(!flag[j])
            {
                if(min > lowcost[j])
                {
                    k = j;
                    min = lowcost[j];
                }
            }
        }
        if(k == -1) break;
        flag[k] = true; p = G.vex[k].firstarc;
        while(p)
        {
            if(!flag[p -> adjvex])
                if(lowcost[p -> adjvex] > p -> weight)
                {
                    lowcost[p -> adjvex] = p -> weight;
                    adjvex[p -> adjvex] = G.vex[k].data;
                }
            p = p -> nextarc;
        }
    }
    printf("\n最小生成树：");
    for(int i = 0; i < G.vexnum; i++)
        if(flag[i] && G.vex[i].data != adjvex[i])
            printf("%c%c-%d, ", adjvex[i], G.vex[i].data, lowcost[i]);
    printf("\n");
    delete[] flag;
    delete[] adjvex;
    delete[] lowcost;
}

char vex1[maxn], vex2[maxn];
int weight;

void solve()
{
    Graph G;
    InitGraph(G, 100);

    FILE *fp;
    if((fp = fopen("无向网.txt", "r")) == 0)
    {
        printf("打开“无向网.txt”文件失败");
        system("pause");
        return ;
    }
    while(fscanf(fp, "%s%s%d", vex1, vex2, &weight) != EOF)
    {
        printf("插入边：%c%c-%d-------", vex1[0], vex2[0], weight);
        if(InsertArc(G, vex1[0], vex2[0], weight)) printf("成功\n");
        else printf("失败\n");
    }
    fclose(fp);

    printf("\n图的邻接表：\n");
    PrintGraph(G);
    Prim(G, G.vex[1].data);
    DestroyGraph(G);
    system("pause");
}

int main()
{
    solve();

    return 0;
}
