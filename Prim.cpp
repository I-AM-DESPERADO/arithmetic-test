#include <stdio.h>
#define maxsize 65535 //��ʾ����䲻�ɴ�
#define n 6   //��ͨ����Ľ����
typedef struct
{
 int formvex,endvex;//�ߵ������յ�
 int length;//�ߵ�Ȩֵ
}edge;
void prim(int dist[][n],edge T[]);//�ӵ�һ���������������ͨ����dist����С���������������T��


void main()
{
	 printf("*************************Prim�㷨**************************\n");
	 int dist[n][n]={
	 {maxsize,6,1,5,maxsize,maxsize},
	 {6,maxsize,5,maxsize,3,maxsize},
	 {1,5,maxsize,7,5,4},
	 {5,maxsize,7,maxsize,maxsize,2},
	 {maxsize,3,5,maxsize,maxsize,6},
	 {maxsize,maxsize,4,2,6,maxsize}
	 };//��ͨ����Ĵ�Ȩ�ڽӾ���
	 edge T[n-1];//������
	 prim(dist,T);
	 int i,j;
	 printf("{�����ͨ����Ĵ�Ȩ�ڽӾ���}\n");
	 for(i=0;i<n;i++)
	 {
		for(j=0;j<n;j++)
		printf("\t%d",dist[i][j]);
		printf("\n");
	 }
	 printf("{�����С�������ı߼�Ȩ}\n");
	 for(i=0;i<n-1;i++)
	 {
		printf("\t(%d,%d) %d\n",T[i].formvex,T[i].endvex,T[i].length);
	 }
}





void prim(int dist[][n],edge T[])//�ӵ�һ���������������ͨ����dist����С���������������T��
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
 for(k=0;k<n-1;k++)//���k����
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
 