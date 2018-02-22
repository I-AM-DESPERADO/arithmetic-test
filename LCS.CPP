#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int LCS(char A[],int n,char B[],int m,int L[][13]);
int max(int a,int b);

void main()
{
	char B[13]={'0','z','x','z','y','y','z','x','x','y','x','x','z'};
	char A[11]={'0','x','y','x','x','z','x','y','z','x','y'};
	
	int L[11][13];
	int l=LCS(A,10,B,12,L);
	printf("最长公共子序列长度为%d          ",l);
}



int LCS(char A[],int n,char B[],int m,int L[][13])
{
	int i,j;
	
	for(i=0;i<n+1;i++)
	{
		L[i][0]=0;
	}
	for(j=0;j<m+1;j++)
	{
		L[0][j]=0;
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			if(A[i]==B[j])
			{
				L[i][j]=L[i-1][j-1]+1;
			}
			else L[i][j]=max(L[i][j-1],L[i-1][j]);
		}
	}
	return L[n][m];
} 


int max(int a,int b)
{
	if(a>=b) return a;
	else return b;
}