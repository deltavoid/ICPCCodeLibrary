//图的宽度优先遍历

const int N;
int n;
bool g[N+1][N+1];

int hash[N+1];



void bfs(int k)
{
	int q[N+1];
	
	q[1]=k;
	int f=1,p=2;
	while (f<p)
	{
		int s=q[f];
		
		for (int i=1;i<=n;i++)
		if  (g[s][i]&&hash[i]==0)
		{
			hash[i]=1;
			q[p]=i;
			p++;
		}
		
		f++;
	}
	
}

void main()
{
	for (int i=1;i<=n;i++)
	if  (hash[i]==0)
	{   hash[i]=1;
	    bfs(i);
	}
}
