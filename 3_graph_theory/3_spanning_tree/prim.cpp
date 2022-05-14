//无向图的最小生成树 Prim算法

const int N;
struct edge
{   int u,v;
    int w;
};
struct edge E[N+1];
int g[N+1][N+1];//未连通边权值为 maxint 
int n;



void Prim()
{
	//初始化边集数组，起点全部为1，终点为 2->n-1 
	for (int i=1;i<=n-1;i++)
	{   E[i].u=1;  E[i].v=i+1;  E[i].w=g[1][i+1];}
	
	
	//选取最小生成树的n-1条边 
	for (int k=1;k<=n-1;k++)
	{   //选取第k条边
	 
	    //从待选边中找到权值最小的一条边 
		int minw=E[k].w,m=k;
		for (int i=k+1; i<=n-1; i++)
		if  (minw>E[i].w) {  minw=E[i].w;  m=i;}
		
		//将权值最小的一条边交换到 k 
		if  (m!=k) {  edge t=E[k];  E[k]=E[m];  E[m]=t;}
		
		//用新加入边的v作为u 去更新到未加入点的权值 
		int u=E[k].v;
		for (i=k+1; i<=n-1; i++)
		{   int v=E[i].v;  int w=g[u][v];
			if  (w<E[i].w) {  E[i].w=w;  E[i].u=u;}
		}
	}
	
	//E[1->n-1]即为所求生成树的n-1条边 
}
 
