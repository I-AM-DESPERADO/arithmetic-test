#include <stdio.h>
#define maxsize 65535 //表示顶点间不可达
#define n 6   //连通网络的结点数
typedef struct
{
 int formvex,endvex;//边的起点和终点
 int length;//边的权值
}edge;
void prim(int dist[][n],edge T[]);//从第一个定点出发构造连通网络dist的最小生成树，结果放在T中


void main()
{
	 printf("*************************Prim算法**************************\n");
	 int dist[n][n]={
	 {maxsize,6,1,5,maxsize,maxsize},
	 {6,maxsize,5,maxsize,3,maxsize},
	 {1,5,maxsize,7,5,4},
	 {5,maxsize,7,maxsize,maxsize,2},
	 {maxsize,3,5,maxsize,maxsize,6},
	 {maxsize,maxsize,4,2,6,maxsize}
	 };//连通网络的带权邻接矩阵
	 edge T[n-1];//生成树
	 prim(dist,T);
	 int i,j;
	 printf("{输出连通网络的带权邻接矩阵}\n");
	 for(i=0;i<n;i++)
	 {
		for(j=0;j<n;j++)
		printf("\t%d",dist[i][j]);
		printf("\n");
	 }
	 printf("{输出最小生成树的边及权}\n");
	 for(i=0;i<n-1;i++)
	 {
		printf("\t(%d,%d) %d\n",T[i].formvex,T[i].endvex,T[i].length);
	 }
}





void prim(int dist[][n],edge T[])//从第一个定点出发构造连通网络dist的最小生成树，结果放在T中
{
 int j,k,m,v,min,max=10000;
 int d;
 edge e;
 for(j=1;j<n;j++) 
 {
	T[j-1].formvex=1;  
	T[j-1].endvex=j+1;
	T[j-1].length=dist[0][j];
 }
 for(k=0;k<n-1;k++)//求第k条边
 {
	min=max;
	for(j=k;j<n-1;j++)
	{
		if(T[j].length<min)
	{
	min=T[j].length;
	m=j;
	}
  }
  e=T[m];T[m]=T[k];T[k]=e;
  v=T[k].endvex;
  for(j=k+1;j<n-1;j++)
  {
   d=dist[v-1][T[j].endvex-1];
   if(d<T[j].length)
   {
    T[j].length=d;
    T[j].formvex=v;
   }
  }
 }
}//prim
 