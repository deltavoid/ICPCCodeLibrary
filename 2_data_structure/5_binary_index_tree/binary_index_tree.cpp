//树状数组

const int N;
int a[N+1];//原始数组 
int c[N+1];//树状数组工作数组 
int n;

int lowbit(int x)  {  return  x&(x^(x-1));}

void update(int x,int delta)//将地址为 x 的点 改变delta 
{
	for (int i=x;i<=N;i+=lowbit(i))
	    c[i]+=delta;
}


int getsum(int x)//求 1->x 的区间和 
{
	int sum=0;
	for (int i=x;i>=1;i-=lowbit(i))
	    sum+=c[i];
	
	return sum;
}


 
