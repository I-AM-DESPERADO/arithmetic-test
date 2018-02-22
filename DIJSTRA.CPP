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
#define MAX_NAME 5 // �����ַ�������󳤶�+1
#define MAX_INFO 20 // �����Ϣ�ַ�������󳤶�+1



#define INFINITY   INT_MAX // ���ֵ��
#define MAX_VERTEX_NUM 100 // ��󶥵����
typedef int vrtype;
typedef char infotype;
typedef char vertextype[MAX_NAME];
typedef int status;

typedef enum {DG,DN,UDG,UDN} graphkind;// {����ͼ,������,����ͼ,������}
typedef struct arccell{
	vrtype adj;
    infotype *info;
}arccell,adjmatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct mgraph
{
	vertextype vexs[MAX_VERTEX_NUM]; // ��������
    adjmatrix arcs;                  // �ڽӾ���
    int   vexnum,arcnum;             // ͼ�ĵ�ǰ�������ͻ���
    graphkind kind;                  // ͼ�������־
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
typedef int pathmatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // ·�����󣬶�ά����
typedef int shortpathtable[MAX_VERTEX_NUM]; // ��̾������һά����

void shortestpath_DIJ(mgraph G,int v0,pathmatrix p,shortpathtable d);

void main(){	
	
	int i,j;
    mgraph g;
	pathmatrix p; 
	shortpathtable d; 
	createDN(g);
	Display(g); 
	shortestpath_DIJ(g,0,p,d);
	printf("���·������p[i][j]����:\n");
	for(i=0;i<g.vexnum;++i)
	{
		for(j=0;j<g.vexnum;++j)
			printf("%2d",p[i][j]);
		printf("\n");
	}
	printf("%s������������·������Ϊ\n",g.vexs[0]);
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
{ // ��������(�ڽӾ���)��ʾ�������ļ�����û�������Ϣ������ͼG

	int i,j,k;
    char filename[50];
    vertextype va,vb;
    FILE *graphlist;
    printf("�����������ļ���: ");
    scanf("%s",filename);
    graphlist=fopen(filename,"r"); // �������ļ�������graphlist��ʾ
    fscanf(graphlist,"%d",&G.vexnum);
    fscanf(graphlist,"%d",&G.arcnum);
    for(i=0;i<G.vexnum;++i) // ���춥������
		fscanf(graphlist,"%s",G.vexs[i]);
   	for(i=0;i<G.vexnum;++i) // ��ʼ���ڽӾ���
		for(j=0;j<G.vexnum;++j)
		{
		    G.arcs[i][j].adj=0; // ͼ
            G.arcs[i][j].info=NULL; // û�������Ϣ
		}
		for(k=0;k<G.arcnum;++k)
		{

			fscanf(graphlist,"%s%s",va,vb);
            i=locatevex(G,va);
            j=locatevex(G,vb);
            G.arcs[i][j].adj=G.arcs[j][i].adj=1; // ����ͼ
		}
		fclose(graphlist); // �ر������ļ�
        G.kind=UDG;
}


void createFUDN(mgraph &G)
{ // ��������(�ڽӾ���)��ʾ�������ļ�����û�������Ϣ��������G

 	int i,j,k,w;
    char filename[50];
    vertextype va,vb;
    FILE *graphlist;
    printf("�����������ļ���: ");
    scanf("%s",filename);
    graphlist=fopen(filename,"r"); // �������ļ�������graphlist��ʾ
    fscanf(graphlist,"%d",&G.vexnum);
    fscanf(graphlist,"%d",&G.arcnum);
    for(i=0;i<G.vexnum;++i) // ���춥������
		fscanf(graphlist,"%s",G.vexs[i]);
    for(i=0;i<G.vexnum;++i) // ��ʼ���ڽӾ���
	
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
    printf("����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
   scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&incinfo);
    printf("������%d�������ֵ(<%d���ַ�):\n",G.vexnum,MAX_NAME);
    for(i=0;i<G.vexnum;++i) // ���춥������
		scanf("%s",G.vexs[i]);
	for(i=0;i<G.vexnum;++i) // ��ʼ���ڽӾ���
		for(j=0;j<G.vexnum;++j)
		{
			G.arcs[i][j].adj=0; 
			G.arcs[i][j].info=NULL;
		}

		printf("������%d�����Ļ�β ��ͷ(�Կո���Ϊ���): \n",G.arcnum);
		for(k=0;k<G.arcnum;++k)
		{
			scanf("%s%s%*c",va,vb); // %*c�Ե��س���
            i=locatevex(G,va);
            j=locatevex(G,vb);
            G.arcs[i][j].adj=1; // ����ͼ
			if(incinfo)
			{
				printf("������û��������Ϣ(<%d���ַ�): ",MAX_INFO);
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
{ // ��������(�ڽӾ���)��ʾ��������������G

	int i,j,k,w,incinfo;
    char s[MAX_INFO];
    vertextype va,vb;
    printf("������������G�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
    scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&incinfo);
    printf("������%d�������ֵ( <%d���ַ�):\n",G.vexnum,MAX_NAME);
    for(i=0;i<G.vexnum;++i) // ���춥������

		scanf("%s",G.vexs[i]);

	for(i=0;i<G.vexnum;++i) // ��ʼ���ڽӾ���
		for(j=0;j<G.vexnum;++j)
		{
			G.arcs[i][j].adj=INFINITY; 
			G.arcs[i][j].info=NULL;
		}
		printf("������%d�����Ļ�β ��ͷ Ȩֵ(��,��Ϊ���): \n",G.arcnum);
		for(k=0;k<G.arcnum;++k)
		{
			scanf("%s%s%d%*c",va,vb,&w); 
            i=locatevex(G,va);
            j=locatevex(G,vb);
            G.arcs[i][j].adj=w; 
			if(incinfo)
			{

				printf("������û��������Ϣ( <%d���ַ�): ",MAX_INFO);
				gets(s);
                w=strlen(s);
				if(w)
				{
					G.arcs[i][j].info=(char*)malloc((w+1)*sizeof(char)); // ����
					strcpy(G.arcs[i][j].info,s);
				}
			}
		}
		G.kind=DN;
}





void createUDG(mgraph &G)
{ // ��������(�ڽӾ���)��ʾ������������ͼG
	int i,j,k,l,incinfo;
	char s[MAX_INFO];
	vertextype va,vb;
	printf("����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
    scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&incinfo);
    printf("������%d�������ֵ(<%d���ַ�):\n",G.vexnum,MAX_NAME);
	for(i=0;i<G.vexnum;++i) // ���춥������
		scanf("%s",G.vexs[i]);
	for(i=0;i<G.vexnum;++i) // ��ʼ���ڽӾ���
		for(j=0;j<G.vexnum;++j)
		{
			G.arcs[i][j].adj=0; // ͼ
			G.arcs[i][j].info=NULL;
		}
		printf("������%d���ߵĶ���1 ����2(�Կո���Ϊ���): \n",G.arcnum);
		for(k=0;k<G.arcnum;++k)
		{
			scanf("%s%s%*c",va,vb);
			i=locatevex(G,va);
            j=locatevex(G,vb);
            G.arcs[i][j].adj=G.arcs[j][i].adj=1; 
			if(incinfo)
			{
				printf("������ñߵ������Ϣ(<%d���ַ�): ",MAX_INFO);
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
{ // ��������(�ڽӾ���)��ʾ��������������G��
	int i,j,k,w,incinfo;
    char s[MAX_INFO];
    vertextype va,vb;
    printf("������������G�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0): ");
    scanf("%d,%d,%d",&G.vexnum,&G.arcnum,&incinfo);
    printf("������%d�������ֵ(<%d���ַ�):\n",G.vexnum,MAX_NAME);
	for(i=0;i<G.vexnum;++i) // ���춥������
		scanf("%s",G.vexs[i]);
	for(i=0;i<G.vexnum;++i) // ��ʼ���ڽӾ���
		for(j=0;j<G.vexnum;++j)
		{
			G.arcs[i][j].adj=INFINITY; // ��
            G.arcs[i][j].info=NULL;
		}
		printf("������%d���ߵĶ���1 ����2 Ȩֵ(�Կո���Ϊ���): \n",G.arcnum);
		for(k=0;k<G.arcnum;++k)
		{
			scanf("%s%s%d%*c",va,vb,&w); // %*c�Ե��س���
			i=locatevex(G,va);
            j=locatevex(G,vb);
			G.arcs[i][j].adj=G.arcs[j][i].adj=w; // ����
			if(incinfo)
			{
				printf("������ñߵ������Ϣ(<%d���ַ�): ",MAX_INFO);
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
	printf("������ͼG������(����ͼ:0,������:1,����ͼ:2,������:3): ");
	scanf("%d",&G.kind);
	switch(G.kind)
	{
	case DG: createDG(G); // ��������ͼ
		break;
	case DN: createDN(G); // ����������
		break;
	case UDG:createUDG(G); // ��������ͼ
		break;
	case UDN:createUDN(G); // ����������
	}
}



void destroygraph(mgraph &G)
{ 
	int i,j,k=0;
	if(G.kind%2) // ��
		k=INFINITY; // kΪ������֮���ޱ߻�ʱ�ڽӾ���Ԫ�ص�ֵ
	for(i=0;i<G.vexnum;i++) // �ͷŻ���ߵ������Ϣ(����еĻ�)
		if(G.kind<2) // ����
		{
			for(j=0;j<G.vexnum;j++)
				if(G.arcs[i][j].adj!=k) // �л�
					if(G.arcs[i][j].info) // �������Ϣ
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
	k=locatevex(G,v); // kΪ����v��ͼG�е����
	if(k<0)
		return ERROR;
	strcpy(G.vexs[k],value);
	return OK;
}



int firstadjvex(mgraph G,vertextype v)
{
	int i,j=0,k;
	k=locatevex(G,v); // kΪ����v��ͼG�е����
	if(G.kind%2) // ��
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
	strcpy(G.vexs[G.vexnum],v); // �����¶�������
	for(i=0;i<=G.vexnum;i++)
	{
		G.arcs[G.vexnum][i].adj=G.arcs[i][G.vexnum].adj=j;
		G.arcs[G.vexnum][i].info=G.arcs[i][G.vexnum].info=NULL; // ��ʼ�������Ϣָ��
	}
	G.vexnum++; // ͼG�Ķ�������1
}





status deletevex(mgraph &G,vertextype v)
{ 
	int i,j,k;
	vrtype m=0;
	if(G.kind%2) 
		m=INFINITY;
	k=locatevex(G,v); // kΪ��ɾ������v�����
	if(k<0) // v����ͼG�Ķ���
		return ERROR;
	for(j=0;j<G.vexnum;j++)
		if(G.arcs[j][k].adj!=m) // ���뻡���
		{
			if(G.arcs[j][k].info) 
				free(G.arcs[j][k].info); 
			G.arcnum--; // �޸Ļ���
		}
		if(G.kind<2) // ����
			for(j=0;j<G.vexnum;j++)
				if(G.arcs[k][j].adj!=m) // �г���
				{
					if(G.arcs[k][j].info) // �������Ϣ
						free(G.arcs[k][j].info); // �ͷ������Ϣ
					G.arcnum--; // �޸Ļ���
				}
				for(j=k+1;j<G.vexnum;j++) // ���k����Ķ�����������ǰ��
					strcpy(G.vexs[j-1],G.vexs[j]);
				for(i=0;i<G.vexnum;i++)
					for(j=k+1;j<G.vexnum;j++)
						G.arcs[i][j-1]=G.arcs[i][j]; // �ƶ���ɾ������֮�ҵľ���Ԫ��
					for(i=0;i<G.vexnum;i++)
						for(j=k+1;j<G.vexnum;j++)
							G.arcs[j-1][i]=G.arcs[j][i]; // �ƶ���ɾ������֮�µľ���Ԫ��
						G.vexnum--; // ����ͼ�Ķ�����
						return OK;
}



status insertarc(mgraph &G,vertextype v,vertextype w)
{ 
	int i,l,v1,w1;
	char s[MAX_INFO];
	v1=locatevex(G,v); // β
	w1=locatevex(G,w); // ͷ
	if(v1<0||w1<0)
		return ERROR;
	G.arcnum++; // ���������1
	if(G.kind%2) // ��
	{
		printf("������˻���ߵ�Ȩֵ: ");
		scanf("%d",&G.arcs[v1][w1].adj);
	}
	else
		G.arcs[v1][w1].adj=1;
	printf("�Ƿ��иû���ߵ������Ϣ(0:�� 1:��): ");
	scanf("%d%*c",&i);
	if(i)
	{
		printf("������û���ߵ������Ϣ(<%d���ַ�)�� ",MAX_INFO);
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
		G.arcs[w1][v1].info=G.arcs[v1][w1].info; // ָ��ͬһ�������Ϣ
	}
	return OK;
}



status deletearc(mgraph &G,vertextype v,vertextype w)
{ 
	int v1,w1,j=0;
	if(G.kind%2) // ��
		j=INFINITY;
	v1=locatevex(G,v); // β
	w1=locatevex(G,w); // ͷ
	if(v1<0||w1<0) // v1�� w1��ֵ���Ϸ�
		return ERROR;
	G.arcs[v1][w1].adj=j;
	if(G.arcs[v1][w1].info) // ��������Ϣ
	{
		free(G.arcs[v1][w1].info);
		G.arcs[v1][w1].info=NULL;
	}
	if(G.kind>=2) // ����ɾ���Գƻ�<w,v>
	{
		G.arcs[w1][v1].adj=j;
		G.arcs[w1][v1].info=NULL;
	}
	G.arcnum--; // ����-1
	return OK;
}

void Display(mgraph G)
{ // ����ڽӾ���洢�ṹ��ͼG
	int i,j;
	char s[7];
	switch(G.kind)
	{
	case DG: strcpy(s,"����ͼ");
		break;
	case DN: strcpy(s,"������");
		break;
	case UDG:strcpy(s,"����ͼ");
		break;
	case UDN:strcpy(s,"������");
	}
	printf("%d������%d���߻򻡵�%s������������: ",G.vexnum,G.arcnum,s);
	for(i=0;i<G.vexnum;++i) // ���G.vexs
		printf("%s ",G.vexs[i]);
	printf("\nG.arcs.adj:\n"); // ���G.arcs.adj
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
			printf("%11d",G.arcs[i][j].adj);
		printf("\n");
	}
	printf("G.arcs.info:\n"); // ���G.arcs.info
	printf("����1(��β) ����2(��ͷ) �ñ߻򻡵���Ϣ�� \n");
	for(i=0;i<G.vexnum;i++)
		if(G.kind<2) // ����
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



