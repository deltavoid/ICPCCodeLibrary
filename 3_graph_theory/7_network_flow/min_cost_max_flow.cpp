//最小费用最大流  


const int N;
int n;
int s,t;
int res[N+1][N+1];//残量网络 
int cos[N+1][N+1];//单位费用网络 

int Q[N+10];//扩展队列 
bool hash[N+1];//是否在队列 
int dist[N+1];//到每个节点的最小费用（有流量的情况下） 
int neck[N+1];//最小费用下到每个节点的流量瓶颈 
int path[N+1];//最小费用下每个节点的来路 

int spfa()
{
	memset(Q,0,sizeof(Q));
	memset(hash,false,sizeof(size));
	memset(dist,maxint,sizeof(dist));
	memset(neck,0,sizeof(neck));
	memset(path,0,sizeof(path));
	
	Q[1]=s;  hash[s]=true;  dist[s]=0;  neck[s]=maxint;  path[s]=s;
	
	int f=1,p=2;
	while (f<p)
	{
		int u=Q[f];
		
		for (int v=1;v<=n;v++)
		if  (res[u][v]>0)
		{
			int d=dist[u]+cos[u][v];
			if  (d<dist[v])
			{
				dist[v]=d;
				neck[v]=min(neck[u],res[u][v]);
				path[v]=u;
				
				if  (!hash[v])
				{
					Q[p]=v;  hash[v]=true;
					p++;
				}
			}
		}
		
		hash[u]=false;
		f++;
	}
	
	if  (neck[t]>0)
	{
		int flow=neck[t],cost=dist[t]*neck[t];
		for (int i=t;i!=s;i=path[i])
		{   res[path[i]][i]-=flow;
		    res[i][path[i]]+=flow;
		}
		return flow;
	}
	else
	{   return 0;
	}
}

int min_cost_max_flow()
{
	int flow=0,cost=0;
	while (1)
	{   
	    int f=spfa();
	    flow+=f;
	    if  (f==0) break;
	}
	return flow;
}
