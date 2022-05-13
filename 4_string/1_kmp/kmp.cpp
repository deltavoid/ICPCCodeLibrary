//kmp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

const int N=1000000;
const int M=10000;
int times;
int n,m;
char T[N+1000];//0->n
char P[M+1000];//0->m
int pre[M+1000];


void pre_init()
{
	pre[0]=-1;
	int j=-1;
	
	for (int i=1;i<=m;i++)
	{
		while (j>-1&&P[i]!=P[j+1])  j=pre[j];
		if  (P[i]==P[j+1])  j++;
		pre[i]=j;
	}
}

int kmp()
{
	int js=0;
	int j=-1;
	for (int i=0;i<=n;i++)
	{
		while (j>-1&&T[i]!=P[j+1])  j=pre[j];
		if  (T[i]==P[j+1])  j++;
		if  (j==m)  {  js++;  j=pre[j];}
	}
	return js;
}


int main()
{
	//freopen("input.txt","r",stdin);
	
	scanf("%d\n",&times);
	for (int t=1;t<=times;t++)
	{
		memset(pre,0,sizeof(pre));
		
		gets(P);
		m=strlen(P)-1;

		gets(T);
		n=strlen(T)-1;


		
		pre_init();
		
		int sol=kmp();
		printf("%d\n",sol);
		
	}
	
	return 0;
}
 
