//拓扑图动规 aoe网


const int N;
int g[N+1][N+1];
int n;
//int s,t;
int Q[N+10];
int f=1,p=1;
int du[N+1];//节点的入度 
int dist[N+1];//每个节点完成所需的最少时间 



void aoe_sort()
{
	for (int i=1;i<=n;i++)
	{   for (int j=1;j<=n;j++)
	    if  (g[i][j]>0)  du[i]++;
	    
	    if  (d[i]==0)  {  dist[i]=0;  Q[p]=i;  p++;}
	}
	    
	    
	while (f<p)
	{
		int u=Q[f];
		
		for (int v=1;v<=n;v++)
		if  (g[u][v]>0)
		{
			int d=dist[u]+g[u][v];
			if  (d>dist[v])  dist[v]=d;
			
			du[v]--;
			if  (du[v]==0)
			{   Q[p]=v;  
			    p++;
			}
		}
		
		f++;
	}
	
} 
