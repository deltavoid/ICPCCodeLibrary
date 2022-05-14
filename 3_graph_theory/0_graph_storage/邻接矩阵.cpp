//邻接矩阵


const int N;
int n;
int g[N+1][N+1];



void add_edge(int u,int v,int w)
{
	g[u][v]=w;
} 

void give_edge(int u)
{
	for (int v=1;v<=n;v++)
	if  (g[u][v]>0)
	    printf("%d %d %d\n",u,v,g[u][v]);
}
