//LCA  tarjan 

const int N;
const int M;
int g[N+1][N+1];
int root;
int ques[N+1][N+1],ans[N+1][N+1];

int n,m;
int f[N+1];
bool hash[N+1];



int find(int x)
{
	while (x!=f[x])  f[x]=find(f[x]);
	return f[x];
}

void merge(int x,int y)
{
	int a=find(x),b=find(y);
	f[b]=a;
}

void dfs(int u,int father)
{
	f[u]=u;
	
	for (int i=1;i<=g[u][0];i++)
	if  (g[u][i]!=father)
	{   int v=g[u][i];
	    dfs(v,u);
	    merge(u,v);
	}
	hash[u]=true;
	
	
	for (int i=1;i<=ques[u][0];i++)
	{   int v=ques[u][i];
	    if  (hash[v])
	        ans[u][i]=find(v);
	}
	
}

void lca()
{
	dfs(root,root);
}



