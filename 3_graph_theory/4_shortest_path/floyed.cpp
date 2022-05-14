//全源最短路径 floyed算法

const int N;
int g[N+1][N+1];//不连通点 距离为maxint 
int n;
int dist[N+1][N+1];//不连通点 距离为maxint 



void floyed()
{
	for (int i=1;i<=n;i++)
	    for (int j=1;j<=n;j++)
	        dist[i][j]=g[i][j];
	
	for (int k=1;k<=n;k++)
	    for (int i=1;i<=n;i++)
	        for (int j=1;j<=n;j++)
	            dist[i][j]=min( dist[i][j] , dist[i][k]+dist[k][j] );
	
	
}
