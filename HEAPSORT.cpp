#include <stdio.h>
#include <stdlib.h>
void shiftDown(int s[],int i,int n);
void makeHeap(int s[],int n);
void heapSort(int s[],int n);
void main()
{
	int s[11]={0,13,5,7,6,7,4,9,15,7,10};
	heapSort(s,10);
	for(int i=1;i<=10;i++)
	{
		printf("%d,",s[i]);
	}
	
}
void makeHeap(int s[],int n)
{
	for(int i=n/2;i<=n/2&&i>=1;i--)
	{
		shiftDown(s, i, n);
	}
}

void shiftDown(int s[],int i,int n)
{
	int done=0;int temp;
//	if(2*i>n) exit(0);
	while(2*i<=n&&done==0)
	{
		i=2*i;
		if(i+1<=n&&s[i+1]>s[i]) i++;
		if(s[i/2]<s[i])
		{
			temp=s[i];
			s[i]=s[i/2];
			s[i/2]=temp;
		}
		else done=1;
	}
}

void heapSort(int s[],int n)
{
	int temp;
	makeHeap(s,n);
	for(int j=n;j<=n&&j>=2;j--)
	{
		temp=s[j];
		s[j]=s[1];
		s[1]=temp;
		shiftDown(s,1,j-1);
	}
}