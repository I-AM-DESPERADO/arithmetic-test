#include <stdio.h>
void MERGE(int a[],int p,int q,int r);
void BOTTOMUPSORT(int a[]);
#define N 11
void main()
{	
	
	int a[N]={0,3,6,5,4,8,9,7,4,10,19};
	BOTTOMUPSORT(a);
/*	for(int i=0;i<N;i++)
	{
		printf("%d,",a[i]);
	}//for
	*/
}

void MERGE(int a[],int p,int q,int r)
{
	int b[50];
	int s,t,k,i,j;
	s=p;t=q+1;k=p;
	while(s<=q&&t<=r)
	{
		if(a[s]<=a[t])
		{
			b[k]=a[s];
			s++;
		}
		else 
		{
			b[k]=a[t];
			t++;
		}
		k++;
	}//while
	if(s>=q+1)
	{	i=k;j=t;
		while(i>=k&&i<=r&&j>=t&&j<=r)
		{
			b[i]=a[j];i++;j++;

		}
	}//if
	else
	{
		i=k;j=s;
		while(i>=k&&i<=r&&j>=s&&j<=q)
		{
			b[i]=a[j];i++;j++;
		}
	}//else
	for(int x=p;x<=r;x++)
	{
		a[x]=b[x];
	}
//test
	for(int y=0;y<N;y++)
	{
		printf("%d,",a[y]);
	}//for

}

void BOTTOMUPSORT(int a[])
{
	int t=1;
	int s,i;
	while (t<N)
	{
		s=t;t=2*s;i=0;
		while(i+t<=N)
		{
			MERGE(a,i+1,i+s,i+t);
			i=i+t;
		}//while2
		if(i+s<N) MERGE(a,i+1,i+s,N);
	}//while1

}