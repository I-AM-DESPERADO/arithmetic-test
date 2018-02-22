#include<string.h>
#include<ctype.h>
#include<malloc.h> 
#include<limits.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<math.h> 
#include<process.h> 
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define MAX_NAME 5 // 顶点字符串的最大长度+1
#define MAX_INFO 20 // 相关信息字符串的最大长度+1



#define INFINITY   INT_MAX // 最大值∞
#define MAX_VERTEX_NUM 100 // 最大顶点个数
typedef int vrtype;
typedef char infotype;
typedef char vertextype[MAX_NAME];
typedef int status;

typedef enum {DG,DN,UDG,UDN} graphkind;// {有向图,有向网,无向图,无向网}
typedef struct arccell{
	vrtype adj;
    infotype *info;
}arccell,adjmatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct mgraph
{
	vertextype vexs[MAX_VERTEX_NUM]; // 顶点向量
    adjmatrix arcs;                  // 邻接矩阵
    int   vexnum,arcnum;             // 图的当前顶点数和弧数
    graphkind kind;                  // 图的种类标志
}mgraph;


int locatevex(mgraph G,vertextype u);
void createFUDG(mgraph &G);
void createFUDN(mgraph &G);
void createDG(mgraph &G);
void createDN(mgraph &G);
void createUDG(mgraph &G);
void createUDN(mgraph &G);
void creategraph(mgraph &G);
void destroygraph(mgraph &G);
vertextype& getvex(mgraph G,int v);
status putvex(mgraph &G,vertextype v,vertextype value);
int firstadjvex(mgraph G,vertextype v);
int nextadjvex(mgraph G,vertextype v,vertextype w);
void insertvex(mgraph &G,vertextype v);
status deletevex(mgraph &G,vertextype v);
status deletearc(mgraph &G,vertextype v,vertextype w);
void Display(mgraph G);
typedef int pathmatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 路径矩阵，二维数组
typedef int shortpathtable[MAX_VERTEX_NUM]; // 最短距离表，一维数组

void shortestpath_DIJ(mgraph G,int v0,pathmatrix p,shortpathtable d);

void main(){	
	
	int i,j;
    mgraph g;
	pathmatrix p; 
	shortpathtable d; 
	createDN(g);
	Display(g); 
	shortestpath_DIJ(g,0,p,d);
	printf("最短路径数组p[i][j]如下:\n");
	for(i=0;i<g.vexnum;++i)
	{
		for(j=0;j<g.vexnum;++j)
			printf("%2d",p[i][j]);
		printf("\n");
	}
	printf("%s到各顶点的最短路径长度为\n",g.vexs[0]);
	for(i=0;i<g.vexnum;++i)
		if(i!=0)
			printf("%s-%s:%d\n",g.vexs[0],g.vexs[i],d[i]);	

}


void shortestpath_DIJ(mgraph G,int v0,pathmatrix p,shortpathtable d)
{ 
	int v,w,i,j,min;
	status final[MAX_VERTEX_NUM]; 
	for(v=0;v<G.vexnum;++v)
	{
		final[v]=FALSE; 
		d[v]=G.arcs[v0][v].adj; 
		for(w=0;w<G.vexnum;++w)
			p[v][w]=FALSE; 
		if(d[v]<INFINITY) 
			p[v][v0]=p[v][v]=TRUE; 
	}
	d[v0]=0; 
	final[v0]=TRUE;
	for(i=1;i<G.vexnum;++i)
	{ 
		min=INFINITY; 
		for(w=0;w<G.vexnum;++w) 
			if(!final[w]&&d[w]<min) 
			{
				v=w;
				min=d[w];
			}
			final[v]=TRUE;
			for(w=0;w<G.vexnum;++w) 
				if(!final[w]&&min<INFINITY&&G.arcs[v][w].adj<INFINITY&&(min+G.arcs[v][w].adj<d[w]))
				{
					d[w]=min+G.arcs[v][w].adj;
					for(j=0;j<G.vexnum;++j) 
						p[w][j]=p[v][j];
					p[w][w]=TRUE;
				}
	}
}





int locatevex(mgraph G,vertextype u)
{ 
	int i;
    for(i=0;i<G.vexnum;++i)
		if(strcmp(u,G.vexs[i])==0)
			return i;
		return -1;
}


void createFUDG(mgraph &G)
{ // 采用数组(邻接矩阵)表示法，由文件构造没有相关信息的无向图G

	int i,j,k;
    char filename[50];
    vertextype va,vb;
    FILE *graphlist;
    printf("请输入数据文件名: ");
    scanf("%s",filename);
    graphlist=fopen(filename,"r"); // 打开数据文件，并以graphlist表示
    fscanf(graphlist,"%d",&G.vexnum);
    fscanf(graphlist,"%d",&G.arcnum);
    for(i=0;i<G.vexnum;++i) // 构造顶点向量
		fscanf(graphlist,"%s",G.vexs[i]);
   	for(i=0;i<G.vexnum;++i) // 初始化邻接矩阵
		for(j=0;j<G.vexnum;++j)
		{
		    G.arcs[i][j].adj=0; // 图
            G.arcs[i][j].info=NULL; // 没有相关信息
		}
		for(k=0;k<G.arcnum;++k)
		{

			fscanf(graphlist,"%s%s",va,vb);
            i=locatevex(G,va);
            j=locatevex(G,vb);
            G.arcs[i][j].adj=G.arcs[j][i].adj=1; // 无向图
		}
		fclose(graphlist); // 关闭数据文件
        G.kind=UDG;
}


void createFUDN(mgraph &G)
{ // 采用数组(邻接矩阵)表示法，由文件构造没有相关信息的无向网G

 	int i,j,k,w;
    char filename[50];
    vertextype va,vb;
    FILE *graphlist;
    printf("请输入数据文件名: ");
    scanf("%s",filename);
    graphlist=fopen(filename,"r"); // 打开数据文件，并以graphlist表示
    fscanf(graphlist,"%d",&G.vexnum);
    fscanf(graphlist,"%d",&G.arcnum);
    for(i=0;i<G.vexnum;++i) // 构造顶点向量
		fscanf(graphlist,"%s",G.vexs[i]);
    for(i=0;i<G.vexnum;++i) // 初始化邻接矩阵
	
		for(j=0;j<G.vexnum;++j)
		{
			G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL; 
		}
		for(k=0;k<G.arcnum;++k)
		{
            fscanf(graphlist,"%s%s%d",va,vb,&w);
            i=locatevex(G,va);
            j=locatevex(G,vb);
            G.arcs[i][j].adj=G.arcs[j][i].adj=w; 
		}
		fclose(graphlist);  
		G.kind=UDN;
}



void createDG(mgraph &G)
{ 

	int i,j,k,l,incinfo;
    char s[MAX_INFO];
    vertextype va,vb;
    printf("请输入有向图G的顶点数,弧数,弧是否含其它信息(是:1,否:0): ");
   scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&incinfo);
    printf("请输入%d个顶点的值(<%d个字符):\n",G.vexnum,MAX_NAME);
    for(i=0;i<G.vexnum;++i) // 构造顶点向量
		scanf("%s",G.vexs[i]);
	for(i=0;i<G.vexnum;++i) // 初始化邻接矩阵
		for(j=0;j<G.vexnum;++j)
		{
			G.arcs[i][j].adj=0; 
			G.arcs[i][j].info=NULL;
		}

		printf("请输入%d条弧的弧尾 弧头(以空格作为间隔): \n",G.arcnum);
		for(k=0;k<G.arcnum;++k)
		{
			scanf("%s%s%*c",va,vb); // %*c吃掉回车符
            i=locatevex(G,va);
            j=locatevex(G,vb);
            G.arcs[i][j].adj=1; // 有向图
			if(incinfo)
			{
				printf("请输入该弧的相关信息(<%d个字符): ",MAX_INFO);
                gets(s);
				l=strlen(s);
				if(l)
				{
					G.arcs[i][j].info=(char*)malloc((l+1)*sizeof(char)); 
					strcpy(G.arcs[i][j].info,s);
				}
			}
		}
		G.kind=DG;
}




void createDN(mgraph &G)
{ // 采用数组(邻接矩阵)表示法，构造有向网G

	int i,j,k,w,incinfo;
    char s[MAX_INFO];
    vertextype va,vb;
    printf("请输入有向网G的顶点数,弧数,弧是否含其它信息(是:1,否:0): ");
    scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&incinfo);
    printf("请输入%d个顶点的值( <%d个字符):\n",G.vexnum,MAX_NAME);
    for(i=0;i<G.vexnum;++i) // 构造顶点向量

		scanf("%s",G.vexs[i]);

	for(i=0;i<G.vexnum;++i) // 初始化邻接矩阵
		for(j=0;j<G.vexnum;++j)
		{
			G.arcs[i][j].adj=INFINITY; 
			G.arcs[i][j].info=NULL;
		}
		printf("请输入%d条弧的弧尾 弧头 权值(以,作为间隔): \n",G.arcnum);
		for(k=0;k<G.arcnum;++k)
		{
			scanf("%s%s%d%*c",va,vb,&w); 
            i=locatevex(G,va);
            j=locatevex(G,vb);
            G.arcs[i][j].adj=w; 
			if(incinfo)
			{

				printf("请输入该弧的相关信息( <%d个字符): ",MAX_INFO);
				gets(s);
                w=strlen(s);
				if(w)
				{
					G.arcs[i][j].info=(char*)malloc((w+1)*sizeof(char)); // 有向
					strcpy(G.arcs[i][j].info,s);
				}
			}
		}
		G.kind=DN;
}





void createUDG(mgraph &G)
{ // 采用数组(邻接矩阵)表示法，构造无向图G
	int i,j,k,l,incinfo;
	char s[MAX_INFO];
	vertextype va,vb;
	printf("请输入无向图G的顶点数,边数,边是否含其它信息(是:1,否:0): ");
    scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&incinfo);
    printf("请输入%d个顶点的值(<%d个字符):\n",G.vexnum,MAX_NAME);
	for(i=0;i<G.vexnum;++i) // 构造顶点向量
		scanf("%s",G.vexs[i]);
	for(i=0;i<G.vexnum;++i) // 初始化邻接矩阵
		for(j=0;j<G.vexnum;++j)
		{
			G.arcs[i][j].adj=0; // 图
			G.arcs[i][j].info=NULL;
		}
		printf("请输入%d条边的顶点1 顶点2(以空格作为间隔): \n",G.arcnum);
		for(k=0;k<G.arcnum;++k)
		{
			scanf("%s%s%*c",va,vb);
			i=locatevex(G,va);
            j=locatevex(G,vb);
            G.arcs[i][j].adj=G.arcs[j][i].adj=1; 
			if(incinfo)
			{
				printf("请输入该边的相关信息(<%d个字符): ",MAX_INFO);
				gets(s);
				l=strlen(s);
				if(l) 
				{
					G.arcs[i][j].info=G.arcs[j][i].info=(char*)malloc((l+1)*sizeof(char));
					strcpy(G.arcs[i][j].info,s);
				}
			}
		}
		G.kind=UDG;
}






void createUDN(mgraph &G)
{ // 采用数组(邻接矩阵)表示法，构造无向网G。
	int i,j,k,w,incinfo;
    char s[MAX_INFO];
    vertextype va,vb;
    printf("请输入无向网G的顶点数,边数,边是否含其它信息(是:1,否:0): ");
    scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&incinfo);
    printf("请输入%d个顶点的值(<%d个字符):\n",G.vexnum,MAX_NAME);
	for(i=0;i<G.vexnum;++i) // 构造顶点向量
		scanf("%s",G.vexs[i]);
	for(i=0;i<G.vexnum;++i) // 初始化邻接矩阵
		for(j=0;j<G.vexnum;++j)
		{
			G.arcs[i][j].adj=INFINITY; // 网
            G.arcs[i][j].info=NULL;
		}
		printf("请输入%d条边的顶点1 顶点2 权值(以空格作为间隔): \n",G.arcnum);
		for(k=0;k<G.arcnum;++k)
		{
			scanf("%s%s%d%*c",va,vb,&w); // %*c吃掉回车符
			i=locatevex(G,va);
            j=locatevex(G,vb);
			G.arcs[i][j].adj=G.arcs[j][i].adj=w; // 无向
			if(incinfo)
			{
				printf("请输入该边的相关信息(<%d个字符): ",MAX_INFO);
				gets(s);
				w=strlen(s);
				if(w)
				{
					G.arcs[i][j].info=G.arcs[j][i].info=(char*)malloc((w+1)*sizeof(char));
					strcpy(G.arcs[i][j].info,s);
				}
			}
		}
		G.kind=UDN;
}




void creategraph(mgraph &G)
{ 
	printf("请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3): ");
	scanf("%d",&G.kind);
	switch(G.kind)
	{
	case DG: createDG(G); // 构造有向图
		break;
	case DN: createDN(G); // 构造有向网
		break;
	case UDG:createUDG(G); // 构造无向图
		break;
	case UDN:createUDN(G); // 构造无向网
	}
}



void destroygraph(mgraph &G)
{ 
	int i,j,k=0;
	if(G.kind%2) // 网
		k=INFINITY; // k为两顶点之间无边或弧时邻接矩阵元素的值
	for(i=0;i<G.vexnum;i++) // 释放弧或边的相关信息(如果有的话)
		if(G.kind<2) // 有向
		{
			for(j=0;j<G.vexnum;j++)
				if(G.arcs[i][j].adj!=k) // 有弧
					if(G.arcs[i][j].info) // 有相关信息
					{
						free(G.arcs[i][j].info);
						G.arcs[i][j].info=NULL;
					}
		} 
		else 
			for(j=i+1;j<G.vexnum;j++) 
				if(G.arcs[i][j].adj!=k) 
					if(G.arcs[i][j].info) 
					{
						free(G.arcs[i][j].info);
						G.arcs[i][j].info=G.arcs[j][i].info=NULL;
					}
					G.vexnum=0; 
					G.arcnum=0; 
}





vertextype& getvex(mgraph G,int v)
{ 
	if(v>=G.vexnum||v<0)
		exit(ERROR);
	return G.vexs[v];
}



status putvex(mgraph &G,vertextype v,vertextype value)
{
	int k;
	k=locatevex(G,v); // k为顶点v在图G中的序号
	if(k<0)
		return ERROR;
	strcpy(G.vexs[k],value);
	return OK;
}



int firstadjvex(mgraph G,vertextype v)
{
	int i,j=0,k;
	k=locatevex(G,v); // k为顶点v在图G中的序号
	if(G.kind%2) // 网
		j=INFINITY;
	for(i=0;i<G.vexnum;i++)
		if(G.arcs[k][i].adj!=j)
			return i;
		return -1;
}



int nextadjvex(mgraph G,vertextype v,vertextype w)
{ 
	int i,j=0,k1,k2;
	k1=locatevex(G,v); 
	k2=locatevex(G,w); 
	if(G.kind%2) 
		j=INFINITY;
	for(i=k2+1;i<G.vexnum;i++)
		if(G.arcs[k1][i].adj!=j)
			return i;
		return -1;
}



void insertvex(mgraph &G,vertextype v)
{ 
	int i,j=0;
	if(G.kind%2) 
		j=INFINITY;
	strcpy(G.vexs[G.vexnum],v); // 构造新顶点向量
	for(i=0;i<=G.vexnum;i++)
	{
		G.arcs[G.vexnum][i].adj=G.arcs[i][G.vexnum].adj=j;
		G.arcs[G.vexnum][i].info=G.arcs[i][G.vexnum].info=NULL; // 初始化相关信息指针
	}
	G.vexnum++; // 图G的顶点数加1
}





status deletevex(mgraph &G,vertextype v)
{ 
	int i,j,k;
	vrtype m=0;
	if(G.kind%2) 
		m=INFINITY;
	k=locatevex(G,v); // k为待删除顶点v的序号
	if(k<0) // v不是图G的顶点
		return ERROR;
	for(j=0;j<G.vexnum;j++)
		if(G.arcs[j][k].adj!=m) // 有入弧或边
		{
			if(G.arcs[j][k].info) 
				free(G.arcs[j][k].info); 
			G.arcnum--; // 修改弧数
		}
		if(G.kind<2) // 有向
			for(j=0;j<G.vexnum;j++)
				if(G.arcs[k][j].adj!=m) // 有出弧
				{
					if(G.arcs[k][j].info) // 有相关信息
						free(G.arcs[k][j].info); // 释放相关信息
					G.arcnum--; // 修改弧数
				}
				for(j=k+1;j<G.vexnum;j++) // 序号k后面的顶点向量依次前移
					strcpy(G.vexs[j-1],G.vexs[j]);
				for(i=0;i<G.vexnum;i++)
					for(j=k+1;j<G.vexnum;j++)
						G.arcs[i][j-1]=G.arcs[i][j]; // 移动待删除顶点之右的矩阵元素
					for(i=0;i<G.vexnum;i++)
						for(j=k+1;j<G.vexnum;j++)
							G.arcs[j-1][i]=G.arcs[j][i]; // 移动待删除顶点之下的矩阵元素
						G.vexnum--; // 更新图的顶点数
						return OK;
}



status insertarc(mgraph &G,vertextype v,vertextype w)
{ 
	int i,l,v1,w1;
	char s[MAX_INFO];
	v1=locatevex(G,v); // 尾
	w1=locatevex(G,w); // 头
	if(v1<0||w1<0)
		return ERROR;
	G.arcnum++; // 弧或边数加1
	if(G.kind%2) // 网
	{
		printf("请输入此弧或边的权值: ");
		scanf("%d",&G.arcs[v1][w1].adj);
	}
	else
		G.arcs[v1][w1].adj=1;
	printf("是否有该弧或边的相关信息(0:无 1:有): ");
	scanf("%d%*c",&i);
	if(i)
	{
		printf("请输入该弧或边的相关信息(<%d个字符)： ",MAX_INFO);
		gets(s);
		l=strlen(s);
		if(l)
		{
			G.arcs[v1][w1].info=(char*)malloc((l+1)*sizeof(char));
			strcpy(G.arcs[v1][w1].info,s);
		}
	}
	if(G.kind>1) 
	{
		G.arcs[w1][v1].adj=G.arcs[v1][w1].adj;
		G.arcs[w1][v1].info=G.arcs[v1][w1].info; // 指向同一个相关信息
	}
	return OK;
}



status deletearc(mgraph &G,vertextype v,vertextype w)
{ 
	int v1,w1,j=0;
	if(G.kind%2) // 网
		j=INFINITY;
	v1=locatevex(G,v); // 尾
	w1=locatevex(G,w); // 头
	if(v1<0||w1<0) // v1、 w1的值不合法
		return ERROR;
	G.arcs[v1][w1].adj=j;
	if(G.arcs[v1][w1].info) // 有其它信息
	{
		free(G.arcs[v1][w1].info);
		G.arcs[v1][w1].info=NULL;
	}
	if(G.kind>=2) // 无向，删除对称弧<w,v>
	{
		G.arcs[w1][v1].adj=j;
		G.arcs[w1][v1].info=NULL;
	}
	G.arcnum--; // 弧数-1
	return OK;
}

void Display(mgraph G)
{ // 输出邻接矩阵存储结构的图G
	int i,j;
	char s[7];
	switch(G.kind)
	{
	case DG: strcpy(s,"有向图");
		break;
	case DN: strcpy(s,"有向网");
		break;
	case UDG:strcpy(s,"无向图");
		break;
	case UDN:strcpy(s,"无向网");
	}
	printf("%d个顶点%d条边或弧的%s。顶点依次是: ",G.vexnum,G.arcnum,s);
	for(i=0;i<G.vexnum;++i) // 输出G.vexs
		printf("%s ",G.vexs[i]);
	printf("\nG.arcs.adj:\n"); // 输出G.arcs.adj
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
			printf("%11d",G.arcs[i][j].adj);
		printf("\n");
	}
	printf("G.arcs.info:\n"); // 输出G.arcs.info
	printf("顶点1(弧尾) 顶点2(弧头) 该边或弧的信息： \n");
	for(i=0;i<G.vexnum;i++)
		if(G.kind<2) // 有向
		{
			for(j=0;j<G.vexnum;j++)
				if(G.arcs[i][j].info)
					printf("%5s %11s %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
		} 
		else 
			for(j=i+1;j<G.vexnum;j++)
				if(G.arcs[i][j].info)
					printf("%5s %11s %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
}




