//图的深度优先遍历

const int N;
int n;
bool g[N+1][N+1];

int hash[N+1];


void dfs(int k)
{
	
	for (int i=1;i<=n;i++)
	if  (g[k][i]&&hash[i]==0)
	{   hash[i]=1;
	    dfs(i);
	}
	    
}


void main()
{
	for (int i=1;i<=n;i++)
	if  (hash[i]==0)
	{   hash[i]=1;
	    dfs(i);
	}
	    
}
