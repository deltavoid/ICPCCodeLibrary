//LCA  倍增法 

const int N;
const int LOG_N:
int g[N+1][N+1];//邻接表 
int p2[31];

int n,m;
int root;
int d[N+1];//depth(v)
int f[N+1][LOG_N+1];//father(v,k)



void p2_init()
{
	p2[0]=1;
	for (int i=1;i<=30;i++)
	    p2[i]=p2[i-1]*2;
}

void dfs(int now,int father,int depth)//dfs(,father,depth)
{
	f[now][0]=father;
	d[now]=depth;
	
	for (int i=1;i<=g[now][0];i++)
	if  (g[now][i]!=father)
	    dfs(g[now][i],now,depth+1);
}


void lca_init()
{
	m=0; for (int i=n;i>=1;i/=2)  m++;
	
	dfs(root,root,1);
	
	for (int k=1;k<=m;k++)
	    for (int i=1;i<=n;i++)
	        f[i][k]=f[ f[i][k-1] ][k-1];
	
}

void lca(int u,int v)
{
	if  (d[u]>d[v])  swap(u,v);
	
	int l=d[v]-d[u];
	for (int i=m;i>=0;i--)
	if  (p2[i]<=l)
	{   v=f[v][i];
		l-=p2[i];
	}
	
	if  (u==v)  return u;
	
	for (int i=m;i>=0;i--)
	if  (f[u][i]!=f[v][i])
	{   u=f[u][i];
	    v=f[v][i];
	}
	return f[u][0];
}
