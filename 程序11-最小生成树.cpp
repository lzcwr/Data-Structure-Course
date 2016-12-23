#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <iostream>

//操作状态
#define	TRUE	1
#define	FALSE	0
#define	OK		1
#define	ERROR	0

// 操作状态类型
typedef int Status;

////////////////////////////////////////////
//使用邻接表表示图

//顶点数据类型
typedef char VexType;

//弧的结点结构
typedef struct ArcNode
{
    int				adjvex;		// 邻接的顶点的下标
    unsigned int	weight;		// 弧的权值
    struct ArcNode	*nextarc;	// 下一条弧的指针
} ArcNode, *ArcLink;

//顶点的结点结构
typedef struct VexNode
{
    VexType		data;			// 顶点数据
    bool		visited;		// 访问标志
    ArcLink		firstarc;		// 第一条弧的指针
} VexNode, *VexLink;

//图的结构定义
typedef struct ArcListGraph
{
    VexNode		*vex;		// 顶点存储空间的基地址
    int			vexnum;		// 顶点个数
    int			vexsize;	// 顶点个数最大值
    int			arcnum;		// 边的条数
    unsigned char kind;		// 图的种类
} ALGraph;
////////////////////////////////////////////

//初始化图，给定能存储的顶点个数的最大值，为顶点分配存储空间
void InitGraph(ALGraph &G, int n)
{
    if(n < 1)
        return;

    G.vex = new VexNode[n+1];
    if(!G.vex)
        return ;

    G.vexnum = 0;
    G.arcnum = 0;
    G.vexsize = n;
}

//销毁图
void DestroyGraph(ALGraph &G)
{
    int i;
    for(i = 1; i < G.vexnum; i++)	// 销毁所有顶点的邻接弧
    {
        ArcLink p, q;
        p = G.vex[i].firstarc;
        while(p)					// 销毁顶点 i 的所有邻接弧
        {
            q = p;
            p = p->nextarc;
            delete q;
        }
    }

    delete []G.vex;					// 释放顶点的存储空间
    G.vex = 0;
    G.vexnum = 0;
    G.vexsize = 0;
}

// 在图 G 中，查找顶点 v 的“位置”
// 若G中存在顶点v，则返回该顶点的下标
// 否则返回 0
int LocateVex(ALGraph &G, VexType v)
{
    int i;
    for(i = 1; i <= G.vexnum; i++)
    {
        if(v == G.vex[i].data)
            return i;
    }
    return 0;
}

//插入顶点， 顶点值 v
Status InsertVextex(ALGraph &G, VexType v)
{
    int i;
    // 顶点的存储空间已满，则增加分配空间（或返回错误）
    if(G.vexnum >= G.vexsize)
    {
        //return false;
        VexNode *newbuf = new VexNode[(G.vexsize +10) + 1];
        for(i=1; i<=G.vexnum; i++)
        {
            newbuf[i].data = G.vex[i].data;
            newbuf[i].firstarc = G.vex[i].firstarc;
        }
        delete []G.vex;

        G.vex = newbuf;
        G.vexsize = G.vexsize +10;
    }

    // v 在顶点集中，则返回错误
    if(LocateVex(G, v) != 0)
        return ERROR;

    // 在顶点集中，添加顶点
    G.vexnum++;
    G.vex[G.vexnum].data = v;
    G.vex[G.vexnum].firstarc = 0;

    return OK;
}


//插入边，边的两个顶点为：v1，v2
Status InsertArc(ALGraph &G, VexType v1, VexType v2, int weight)
{
    //边的两个顶点相等，返回错误
    if(v1 == v2)
        return ERROR;

    // 在顶点集中查找 v1, v2。如果找不到，则插入顶点
    int n1 = LocateVex(G, v1);
    if(n1 == 0)
    {
        if(!InsertVextex(G, v1))
            return ERROR;
        n1 = LocateVex(G, v1);
    }

    int n2 = LocateVex(G, v2);
    if(n2 == 0)
    {
        if(!InsertVextex(G, v2))
            return ERROR;
        n2 = LocateVex(G, v2);
    }

    //ArcLink p;
    ArcNode *p;
    bool find;

    // 在顶点 n1 的邻接点中查找 n2。
    // 如果存在，则不用再插入；否则，在顶点 n1 中插入邻接点 n2
    p = G.vex[n1].firstarc;
    while(p)
    {
        if(p->adjvex == n2)
        {
            p->weight = weight;
            break;
        }
        p = p->nextarc;
    }
    if(!p)
    {
        p = new ArcNode;
        if(!p)
            return ERROR;
        p->adjvex = n2;
        p->weight = weight;
        p->nextarc = G.vex[n1].firstarc;
        G.vex[n1].firstarc = p;
    }
    p = G.vex[n2].firstarc;
    while(p)
    {
        if(p->adjvex == n1)
        {
            p->weight = weight;
            break;
        }
        p = p->nextarc;
    }
    if(!p)
    {
        p = new ArcNode;
        if(!p)
            return ERROR;
        p->adjvex = n1;
        p->weight = weight;
        p->nextarc = G.vex[n2].firstarc;
        G.vex[n2].firstarc = p;
    }

    return OK;
}


//输出图的所有顶点，以及顶点的所有邻接点
void PrintGraph(ALGraph &G)
{
    int i;
    for(i = 1; i < G.vexnum; i++)
    {
        printf("顶点%d, %c：", i, G.vex[i].data);

        ArcLink p = G.vex[i].firstarc;
        while(p)
        {
            //printf("%c ", G.vex[p->adjvex].data);
            printf("%c%c-%d, ", G.vex[i].data, G.vex[p->adjvex].data, p->weight);
            p = p->nextarc;
        }
        printf("\n");
    }
}

// 最小生成树---Prim算法
void MiniSpanTree(ALGraph G, VexType v0)
{
    int i;
    VexType *adjvex;
    unsigned int *lowcost;
    bool *flag;	
    int n0 = LocateVex (G, v0);
    if(n0 == -1)	return;
    int sum = 0;
    for(i = 0; i < G.vexnum; i++)
    {
        ArcLink p = G.vex[i].firstarc;
        while(p)
        {
            sum += p->weight;
            p = p->nextarc;
        }
    }
    adjvex = new VexType[G.vexnum];
    lowcost = new unsigned int[G.vexnum];
    flag = new bool[G.vexnum];

    for (i=0; i<G.vexnum; i++)
    {
        flag[i] = false;
        lowcost[i] = sum;
    }
    int k = n0;
    flag[k] = true;
    adjvex[k] = v0;
    ArcLink p = G.vex[k].firstarc;
    while(p)
    {
        adjvex[p->adjvex] = G.vex[k].data;
        lowcost[p->adjvex] = p->weight;
        p = p->nextarc;
    }

    for(i=1; i<=G.vexnum; i++)
    {
        unsigned int min = sum;
        int j;

        k = -1;
        for(j = 0; j < G.vexnum; j++)
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
        if(k == -1)	break;
        flag[k] = true;
        p = G.vex[k].firstarc;
        while(p)
        {
            if(!flag[p->adjvex])
                if(lowcost[p->adjvex] > p->weight)
                {
                    lowcost[p->adjvex] = p->weight;
                    adjvex[p->adjvex] = G.vex[k].data;
                }
            p = p->nextarc;
        }

    }
    printf("\n最小生成树：");
    for(i = 0; i < G.vexnum; i++)
    {
        if(flag[i] && G.vex[i].data != adjvex[i])
            printf("%c%c-%d, ", adjvex[i],
                   G.vex[i].data, lowcost[i]);
    }
    printf("\n");
    delete[] flag;
    delete[] adjvex;
    delete[] lowcost;

}


int main()
{
    ALGraph G;

    //初始化图
    InitGraph(G, 100);

    ////////////////////////
    //从文本文件“无向网.txt”中读入数据到图 G
    FILE *fp;

    if((fp = fopen("无向网.txt", "r")) == 0)
    {
        printf("打开“无向网.txt”文件失败");
        getch();
        return -1;
    }
    //从文本文件“无向网.txt”中读入数据
    while(1)
    {
        char vex1[20];
        char vex2[20];
        int weight;

        if(fscanf(fp, "%s%s%d", vex1, vex2, &weight) == EOF)
            break;

        printf("插入边：%c%c-%d-------", vex1[0], vex2[0], weight);
        if(InsertArc(G, vex1[0], vex2[0], weight))
            printf("成功\n");
        else
            printf("失败\n");
    }
    //关闭文本文件“无向网.txt”
    fclose(fp);
    ////////////////////////

    printf("\n图的邻接表：\n");
    PrintGraph(G);

    MiniSpanTree(G, G.vex[1].data);
    //销毁图
    DestroyGraph(G);

    printf("\n程序结束，按任意键返回\n");
    getch();
    return 0;
}