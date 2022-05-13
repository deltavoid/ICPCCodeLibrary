//二维树状数组


const int N;
int a[N+1][N+1];
int c[N+1][N+1];

int n;

int lowbit(int x)  {  return  x&(x^(x-1));}

void update(int x,int y,int delta)
{
	for (int i=x;i<=N;i+=lowbit(i))
	    for (int j=y;j<=N;j+=lowbit(j))
	        c[i][j]+=delta;
}


int getsum(int x,int y)
{
	int sum=0;
	for (int i=x;i>=1;i-=lowbit(i))
	    for (int j=y;j>=1;j-=lowbit(j))
	        sum+=c[i][j];
	
	return sum;
}
