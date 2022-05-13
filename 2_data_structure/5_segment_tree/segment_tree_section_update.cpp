//线段树

const int N;
struct node
{   int l,r,mid;
    int sum,flag;
    int s1,s2;
};
struct node T[N*2+100];
int tot,root;

int n;
int a[N+1];


void build(int now,int l,int r)
{
	int mid=(l+r)/2;
	T[now].l=l;  T[now].r=r;  T[now].mid=mid;
	
	if  (l==r)
	{   T[now].sum=a[l];
	}
	else 
	{
		int sum=0;
		int s1=++tot;  T[now].s1=s1;  sum+=build(s1,l,mid);
		int s2=++tot;  T[now].s2=s2;  sum+=build(s2,mid+1,r);
		T[now].sum=sum;
	}
	return T[now].sum;
}

void update(int now,int xl,int xr,int delta)
{
	int l=T[now].l,r=T[now].r,mid=T[now].mid;
	int s1=T[now].s1,s2=T[now].s2;
	
	if  (l==xl&&r==xr)  
	{   T[now].flag+=delta;
	}
	else
	{   T[now].sum+=(xr-xl+1)*delta;
	
	    if       (xr<=mid)                update(s1,xl,xr,delta);
	    else if  (mid+1<=xl)              update(s2,xl,xr,delta);
	    else if  (xl<=mid&&mid+1<=xr)  {  update(s1,xl,mid,delta);  update(s2,mid+1,xr,delta);}
	}
	
}

void pushdown(int now)
{
	int l=T[now].l,r=T[now].r;
	int s1=T[now].s1,s2=T[now].s2;
	int flag=T[now].flag;
	
	T[now].sum+=(r-l+1)*flag;
	
	if  (l!=r)  {  T[s1].flag+=flag;  T[s2].flag+=flag;}
	
	T[now].flag=0;
}

int getsum(int now,int xl,int xr)
{
	int l=T[now].l,r=T[now].r,mid=T[now].mid;
	int s1=T[now].s1,s2=T[now].s2;
	
	if  (T[now].flag!=0)  pusdown(now);
	
	if  (xl==l&&xr==r)  return T[now].sum;
	else 
	{   if       (xr<=mid)             return getsum(s1,xl,xr);
	    else if  (mid+1<=xl)           return getsum(s2,xl,xr);
	    else if  (xl<=mid&&mid+1<=xr)  return getsum(s1,xl,mid)+getsum(s2,mid+1,xr);
	}
}



