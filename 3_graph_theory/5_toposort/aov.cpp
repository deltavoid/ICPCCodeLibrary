//拓扑图排序 aov网 

const int N;
bool g[N+1][N+1];
int n;
int Q[N+10];
int f=1,p=1;
int du[N+1]; 


void aov_sort()
{
	for (int i=1;i<=n;i++)
	{   for (int j=1;j<=n;j++)
	    if  (g[i][j])  du[i]++;
	    if  (du[i]==0)  {  Q[p]=i;  p++;}
	}
	
	while (f<p)
	{
		int u=Q[f];
		
		for (int v=1;v<=n;v++)
		if  (g[u][v])
		{
			du[v]--;
			
			if  (du[v]==0)
			{
				Q[p]=v;
				p++;
			}
		}
		
		f++;
	}
	
	//所得拓扑序列存于 Q[1->f-1] 中 
}
