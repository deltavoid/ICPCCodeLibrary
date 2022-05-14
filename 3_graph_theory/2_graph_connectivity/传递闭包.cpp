//图的传递闭包

const int N;
int n;
bool g[N+1][N+1];//邻接矩阵


void chuandibibao()
{
	for (int k=1;k<=n;k++)//中间节点必须是第一层循环 
	    for (int i=1;i<=n;i++)
	        for (int j=1;j<=n;j++)
	        if  ( g[i][j] || (g[i][k]&&g[k][j]) )
	            g[i][j]=true;
	            
} 
