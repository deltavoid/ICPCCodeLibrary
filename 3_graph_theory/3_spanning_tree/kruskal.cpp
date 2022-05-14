//无向图的最小生成树 kruskal算法 含并查集


const int N;
const int M;//最大边数 
struct edge
{   int u,v;
    int w;
};
struct edge E[M+1];
int n,m;
int e[N+1];//
int f[N+1];//

bool cmp(edge A,edge B)
{   return (A.w<B.w);
}


int find(int x)
{   int p=x;
    while (p!=f[p]) p=f[p];
    return f[x]=p;
}
void merge(int x,int y)
{   int a=find(x),b=find(y);
    p[b]=a;
}

void kruskal()
{
	sort(E+1,E+m+1,cmp);
	
	for (int i=1;i<=n;i++)
	    f[i]=i;
	    
	for (int k=1,j=1; k<=n-1; k++)
	{
		bool flag=false;
		while (!flag)
		{
			int u=E[j].u,v=E[j].v;
			int a=find(u),b=find(v);
			
			if  (a!=b)
			{   e[k]=j;
			    merge(a,b);
			    flag=true;
			}
			
			j++;
		}
	}
	
}



 
