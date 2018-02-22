#include<stdio.h> 
#include<stdlib.h>

#define MAXEDGE 20
#define MAXVEX  20
#define INFINITY 65535

typedef struct
{
    int arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;//顶点数，边数
}MGraph;

typedef struct
{
    int begin;
    int end;
    int weight;
}Edge;   //对边集数组Edge结构的定义
void CreateMGraph(MGraph *G);
int cmp(const void* a, const void* b);
int Find(int *parent, int f);
void MiniSpanTree_Kruskal(MGraph G);

int main(void)
{
    MGraph G;
    CreateMGraph(&G);
    MiniSpanTree_Kruskal(G);

    return 0;
}


//创建图的邻接矩阵
void CreateMGraph(MGraph *G) {
    int i, j;

    G->numEdges=9;
    G->numVertexes=6;

    for (i = 0; i < G->numVertexes; i++) {
        for ( j = 0; j < G->numVertexes; j++) {
            if (i==j)
                G->arc[i][j]=0;
            else
                G->arc[i][j] = G->arc[j][i] = INFINITY;
        }
    }
    G->arc[0][1]=1;
    G->arc[0][2]=2;
    G->arc[1][2]=6;
    G->arc[2][3]=9;
    G->arc[1][3]=11;
    G->arc[2][4]=13;
    G->arc[3][4]=7;
    G->arc[3][5]=3;
    G->arc[4][5]=4;
    

    for(i = 0; i < G->numVertexes; i++) {
        for(j = i; j < G->numVertexes; j++) {
            G->arc[j][i] =G->arc[i][j];
        }
    }

}

//快速排序的条件
int cmp(const void* a, const void* b) {
    return (*(Edge*)a).weight - (*(Edge*)b).weight;
}

//找到根节点
int Find(int *parent, int f) {
    while ( parent[f] > 0) {
        f = parent[f];
    }
    return f;
}

// 生成最小生成树
void MiniSpanTree_Kruskal(MGraph G) {
    int i, j, n, m;
    int k = 0;
    int parent[MAXVEX]; //用于寻找根节点的数组

    Edge edges[MAXEDGE]; //定义边集数组,edge的结构为begin,end,weight,均为整型

    // 用来构建边集数组并排序(将邻接矩阵的对角线右边的部分存入边集数组中)
    for ( i = 0; i < G.numVertexes-1; i++) {
        for (j = i + 1; j < G.numVertexes; j++) {
            if (G.arc[i][j] < INFINITY) {
                edges[k].begin = i; //编号较小的结点为首
                edges[k].end = j;   //编号较大的结点为尾
                edges[k].weight = G.arc[i][j];
                k++;
            }
        }
    }

    //为边集数组Edge排序
    qsort(edges, G.numEdges, sizeof(Edge), cmp);

    for (i = 0; i < G.numVertexes; i++)
        parent[i] = 0;

    printf("打印最小生成树：\n");
    for (i = 0; i < G.numEdges; i++) {
        n = Find(parent, edges[i].begin);//寻找边edge[i]的“首节点”所在树的树根
        m = Find(parent, edges[i].end);//寻找边edge[i]的“尾节点”所在树的树根

        //假如n与m不等，说明两个顶点不在一棵树内，因此这条边的加入不会使已经选择的边集产生回路
        if (n != m) {
            parent[n] = m;
            printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
        }
    }
}

