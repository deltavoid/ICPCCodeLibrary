//并查集

const int N;
int n;
int f[N+1];

void init()
{
	for (int i=1;i<=n;i++)
	    f[i]=i;
}

int find(int x)
{
	if (f[x]!=x)  f[x]=find(f[x]);
	return f[x];
}

void merge(int x,int y)
{
	int a=find(x),b=find(b);
	p[b]=a;
}

