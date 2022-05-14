//单源最短路径 SPFA

const int N;
int g[N+1][N+1];
int n;
int s;//源点 
int Q[N*4+10];//尽量用循环队列 
int hash[N+1];//节点是否在队列中 
int dist[N+1];//源点到所有点的最短距离 
int path[N+1];//最短路径树中 节点的前驱 



void SPFA()
{
	for (int i=1;i<=n;i++)
	    dist[i]=maxint;
	dist[s]=0;  path[s]=s;
		
	Q[1]=s;  hash[s]=1;
	int f=1,p=2;
	while (f<p)
	{
		int u=Q[f];
		
		for (int v=1;v<=n;i++)
		if  (g[u][v]<maxint)
		{
			int d=dist[u]+g[u][v];
			if  (d<dist[v])
			{
				dist[v]=d;  path[v]=u;
				
				if  (hash[v]==0)
				{   Q[p]=v;  hash[v]=1;
				    p++;
				}
			}
		}
		
		hash[u]=0;
		f++;
	}
	
}
 
