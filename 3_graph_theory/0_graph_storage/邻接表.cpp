//邻接表

const int N;
int n;
int g[N+1][N+1];

void add_edge(int u,int v)
{
	g[u][++g[u][0]]=v;
} 

void give_edge(int u)
{
	for (int i=1;i<=g[u][0];i++)
	    printf("%d %d\n",u,g[u][i]);
	
}
