//单源最短路径  dijkstra

const int N;
int g[N+1][N+1];
int n;
int s;//源点 
int stat[N+1];//状态 
int dist[N+1];//s到各点的距离 
int path[N+1];//最短路径树中 节点的前驱 


void dijkstra()
{
	for (int i=1;i<=n;i++)
	{   stat[i]=i;  dist[i]=maxint;}
	    
	dist[s]=0;
	path[s]=s;
	
	for (int k=1;k<=n;k++)
	{
		int mind=maxint,p=0;
		for (int i=k;i<=n;i++)
		if  (mind>dist[stat[i]]) {  mind=dist[stat[i]]];  p=i;}
		
		if  (p!=k)  {  int t=stat[k];  stat[k]=stat[p];  stat[p]=t;}
		
		int u=stat[k];
		for (int i=k+1;i<=n;i++)
		{   int v=stat[i];  int d=dist[u]+g[u][v];
		    if  (d<dist[v]) {  dist[v]=d;  path[v]=u;}
		}
	}
	
} 
