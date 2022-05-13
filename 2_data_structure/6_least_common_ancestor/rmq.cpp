//RMQ

const int N;
const int M;//M= log 2 N;
int p2[31];
int d[N+1][M+1];

int n;
int a[N+1];


void p2_init()
{
	p2[0]=1;
	for (int i=1;i<=30;i++)
	    p2[i]=p2[i-1]*2;
}

void RMQ_init()
{
	int m=0;  while (p2[m+1]<=n) m++;
	
	for (int i=1;i<=n;i++)
	    d[i][0]=a[i];
	
	for (int k=1;k<=m;k++)
	    for (int i=1;i+p2[k]-1<=n;i++)
	        d[i][k]=min(d[i][k-1],d[i+p2[k-1]][k-1]);
}

int RMQ_ask(int l,int r)
{
	int len=r-l+1,m=0;
	while (p2[m+1]<=len)  m++;
	
	return min(d[l][m],d[j-p2[m]+1][m]);
}
