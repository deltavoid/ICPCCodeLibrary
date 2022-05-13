// heavy_path_decomposition, 树链剖分
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;


const int N=50000;
const int Q=100000;
int n,m,q;
char ch[20];

struct Edge
{   int u,v;
    int next;
};
Edge E[N*2+100];
int root,tot,s[N+100];

int a[N+100];
int siz[N+100],dep[N+100],fa[N+100],son[N+100];
int top[N+100],tid[N+100];
int tim;

int c[N+100];



void init()
{
	memset(c,0,sizeof(c));
	memset(s,0,sizeof(s));
	tot=0;  root=1; tim=0;
}

void add_edge(int u,int v)
{
	int p=++tot;
	E[p].u=u;
	E[p].v=v;
	E[p].next=s[u];
	s[u]=p;
}

void dfs1(int u,int f,int d)
{
	dep[u]=d;  fa[u]=f;
	siz[u]=1;  son[u]=-1;
	
	for (int i=s[u];i!=0;i=E[i].next)
	{   int v=E[i].v;
	    if  (v==f)  continue;
	    
	    dfs1(v, u, d+1);
	    siz[u]+= siz[v] ;
	    if  (son[u]==-1 || siz[son[u]]<siz[v])
	        son[u]=v;
	}
}

void dfs2(int u,int tp)
{
	top[u]=tp;
	tid[u]=++tim;
	
	if  (son[u]==-1)  return ;
	dfs2(son[u], tp);
	for (int i=s[u];i!=0;i=E[i].next)
	{   int v=E[i].v;
	    if  (v==fa[u] || v==son[u])  continue;
	    
	    dfs2(v, v);
	}
}


int lowbit(int x)  {  return x&(-x);}

void add(int x,int w)
{
	for (int i=x;i<=n;i+=lowbit(i))
	    c[i]+= w ;
}

int sum(int x)
{   int sol=0;
    for (int i=x;i>=1;i-=lowbit(i))
        sol+= c[i] ;
    return sol;
}

void update(int l,int r,int w)
{
	add(l, w);
	add(r+1, -w);
}


void change(int u,int v,int w)
{
	while (top[u]!=top[v])
	{
		if  (dep[top[u]]>dep[top[v]])  swap(u, v);
		update(tid[top[v]], tid[v], w);
		v=fa[top[v]];
	}
	
	if  (dep[u]>dep[v])  swap(u, v);
	update(tid[u], tid[v], w);
	
}



int main()
{
	freopen("input.txt","r",stdin);
	
	while (scanf("%d%d%d",&n,&m,&q)!=EOF)
	{
		init();
		int x,y,z;
		for (int i=1;i<=n;i++)
		    scanf("%d",&a[i]);
		for (int i=1;i<=m;i++)
		{   scanf("%d%d",&x,&y);
		    add_edge(x, y);
		    add_edge(y, x);
		}
		
		dfs1(1, 0, 1);
		
		dfs2(1, 1);
		
		
		for (int i=1;i<=n;i++)
		    update(tid[i], tid[i], a[i]);
		
		for (int i=1;i<=q;i++)
		{   scanf("%s",ch);
		    
		    if  (ch[0]=='I')
		    {   scanf("%d%d%d",&x,&y,&z);
		        change(x, y, z);
		    }
		    else if  (ch[0]=='D')
		    {   scanf("%d%d%d",&x,&y,&z);
		        change(x, y, -z);
		    }
		    else if  (ch[0]=='Q')
		    {   scanf("%d",&x);
		        int sol= sum(tid[x]);
		        printf("%d\n",sol);
		    }
		}
		
	}
	return 0;
}
