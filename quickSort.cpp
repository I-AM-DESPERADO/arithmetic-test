#include <stdio.h>

typedef struct Stack
{
	int s[50];
	int top;
}stack;

int Pop(stack &st);
void InitStack(stack &st);
void Push(stack &st,int x);
int Split(int s[],int l,int h);
void quickSort(int s[],int l,int h);
int empty(stack st);

void main()
{	int l=1,h=20;
	int s[21]={0,16,7,46,23,4,89,44,2,6,75,13,59,85,100,19,17,18,49,66,99};
	/*int w=Split(s,1,20);
	printf("%d",w);*/
	quickSort(s,l,h);

	for(int i=1;i<=20;i++)
	{
		printf("%d,",s[i]);
	}
}
  

int Split(int s[],int l,int h)
{
	int i=l;
	int temp;
	int j=l+1;
	int x=s[l];
	for(j=l+1;j<=h;j++)
	{
		if(s[j]<=x)
		{
			i++;
			if(i!=j)
			{
				temp=s[i];
				s[i]=s[j];
				s[j]=temp;
			}//if
		}//if
	}//for
	temp=s[l];
	s[l]=s[i];
	s[i]=temp;
    int	w=i;
	return w;
}

void Push(stack &st,int x)
{	int i=st.top;
	st.s[i]=x;
	i++;
	st.top=i;
}

int Pop(stack &st)
{
	int x;
	int i=st.top-1;
	x=st.s[i];
	st.top--;
	return x;
}
void InitStack(stack &st)
{
	st.top=0;
	for(int i=0;i<50;i++)
		st.s[i]=0;
}


void quickSort(int s[],int l,int h)
{
	stack st;
	int w;
	InitStack(st);
	if(l<h)
	{
		w=Split(s,l,h);
		if(h-w>1)
		{
			Push(st,w+1);
			Push(st,h);
		}//if
		if(w-l>1)
		{
			Push(st,l);
			Push(st,w-1);
		}
		while(empty(st)!=0)
		{
			h=Pop(st);
			l=Pop(st);
			w=Split(s,l,h);
			if(h-w>1)
			{
				Push(st,w+1);
				Push(st,h);
			}//if
			if(w-l>1)
			{
				Push(st,l);
				Push(st,w-1);
			}
		}//while
		
	}
}

int empty(stack st)
{
	if(st.top==0) return 0;
	else return 1;
}