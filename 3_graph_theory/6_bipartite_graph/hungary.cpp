// 2016.12.01
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;


const int N=1000;
int n,nu,nv;
bool g[N+1][N+1];//二分图存储为 左边节点u 指向 右边节点v 的有向边  g[u][v]
int link[N+1];
bool used[N+1];

bool dfs(int u)
{
	for (int v=1;v<=nv;v++)
	if  (g[u][v]&&!used[v])
	{
		used[v]=true;
		if  (link[v]==0||dfs(link[v]))
		{
			link[v]=u;
			return true;
		}
	}
	return false;
}

int match()
{
	memset(link,0,sizeof(link));
	int sol=0;
	for (int i=1;i<=nu;i++)
	{
		memset(used,false,sizeof(used));
		if  (dfs(i)) sol++;
	}
	return sol;
}


int main()
{
	freopen("input.txt","r",stdin);
	
	while (scanf("%d",&n)!=EOF)
	{
		memset(g,false,sizeof(g));
		nu=nv=N;
		
		int x,y;
		for (int i=1;i<=n;i++)
		{   scanf("%d%d",&x,&y);
		    g[x][y]=true;
		}
		
		int sol=match();
		printf("%d\n",sol);
	}
	return 0;
}
