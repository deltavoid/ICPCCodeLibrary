#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

const int N=1000+10;
const int NL=N*2+100;
const int M=1000+10;
const int ML=M*2+100;
const int maxint=0x5fffffff;

int max(int a,int b)  {  if  (a>b)  return a;  else return b;}

int min(int a,int b)  {  if  (a<b)  return a;  else return b;}


struct Nodey
{  int l,r,mid;
   int s1,s2;
   int max,min;
};

class SegTree
{public:
	int maxa[M],mina[M];
	Nodey T[ML];
	int tot,root;
	
	void build(int now,int l,int r);
	void init(int l,int r);
	void update(int now,int y,int maxs,int mins);
	int  getmax(int now,int l,int r);
	int  getmin(int now,int l,int r);
};

void SegTree::build(int now,int l,int r)
{
	Nodey &v=T[now];
	v.l=l;  v.r=r;  v.mid=(v.l+v.r)/2;
	
	if  (v.l==v.r)
	{
		v.s1=0;  v.s2=0;
		v.max=maxa[l];
		v.min=mina[l];
	}
	else 
	{
		v.s1=++tot;  build(v.s1,v.l,v.mid);
		v.s2=++tot;  build(v.s2,v.mid+1,v.r);
		
		Nodey son1=T[v.s1];  Nodey son2=T[v.s2];
		v.max=max(son1.max,son2.max);
		v.min=min(son1.min,son2.min);
	}
}

void SegTree::init(int l,int r)
{
	tot=1;  root=1;
	build(1,l,r);
}

void SegTree::update(int now,int y,int maxs,int mins)
{
	Nodey &v=T[now];
	
	if  (v.l==v.r)
	{
		v.max=maxs;
		v.min=mins;
	}
	else 
	{
		     if  (y<=v.mid)    update(v.s1,y,maxs,mins);
		else if  (y>=v.mid+1)  update(v.s2,y,maxs,mins);
		
		Nodey &son1=T[v.s1];  Nodey &son2=T[v.s2];
		v.max=max(son1.max,son2.max);
		v.min=min(son1.min,son2.min);
	}
}

int SegTree::getmax(int now,int l,int r)
{
	Nodey &v=T[now];
	
	if  (l==v.l&&r==v.r)
	{   return v.max;
	}
	else 
	{
		int t1=-maxint,t2=-maxint;
		     if  (r<=v.mid)    t1=getmax(v.s1,l,r);
		else if  (l>=v.mid+1)  t2=getmax(v.s2,l,r);
		else                {  t1=getmax(v.s1,l,v.mid);  t2=getmax(v.s2,v.mid+1,r);}
		
		return max(t1,t2);
	}
}

int SegTree::getmin(int now,int l,int r)
{
	Nodey &v=T[now];
	
	if  (l==v.l&&r==v.r)
	{   return v.min;
	}
	else 
	{
		int t1=maxint,t2=maxint;
		     if  (r<=v.mid)    t1=getmin(v.s1,l,r);
		else if  (l>=v.mid+1)  t2=getmin(v.s2,l,r);
		else                {  t1=getmin(v.s1,l,v.mid);  t2=getmin(v.s2,v.mid+1,r);}
		
		return min(t1,t2);
	}
}



struct Nodex
{   int l,r,mid;
    int s1,s2;
    SegTree tree;
};

class BiSegTree
{public:
	int a[N][M];
	int n,m;
	Nodex T[NL];
	int tot,root;
	
	void build(int now,int l,int r);
	void init();
	void update(int now,int x,int y,int s);
	int  getmax(int now,int xl,int xr,int yl,int yr);
	int  getmin(int now,int xl,int xr,int yl,int yr);
};

void BiSegTree::build(int now,int l,int r)
{
	Nodex &v=T[now];
	v.l=l;  v.r=r;  v.mid=(v.l+v.r)/2;
	
	if  (v.l==v.r)
	{
		v.s1=0;  v.s2=0;
		
		memset(v.tree.maxa,0,sizeof(v.tree.maxa));
		memset(v.tree.mina,0,sizeof(v.tree.mina));
		for (int i=1;i<=m;i++)
		{   v.tree.maxa[i]=a[v.l][i];
		    v.tree.mina[i]=a[v.l][i];
		}
		v.tree.init(1,m);
	}
	else 
	{
		v.s1=++tot;  build(v.s1,l,v.mid);
		v.s2=++tot;  build(v.s2,v.mid+1,r);
		
		Nodex &son1=T[v.s1];  Nodex &son2=T[v.s2];
		for (int i=1;i<=m;i++)
		{   v.tree.maxa[i]=max( son1.tree.maxa[i] , son2.tree.maxa[i] );
		    v.tree.mina[i]=min( son1.tree.mina[i] , son2.tree.mina[i] );
		}
		v.tree.init(1,m);
	}
}

void BiSegTree::init()
{
	tot=1;  root=1;
	build(1,1,n);
}

void BiSegTree::update(int now,int x,int y,int s)
{
	Nodex &v=T[now];
	
	if  (v.l==v.r)
	{
		v.tree.maxa[y]=s;
		v.tree.mina[y]=s;
		v.tree.update( v.tree.root , y , v.tree.maxa[y] , v.tree.mina[y] );
	}
	else 
	{
		     if  (x<=v.mid)    update(v.s1,x,y,s);
		else if  (x>=v.mid+1)  update(v.s2,x,y,s);
		
		Nodex &son1=T[v.s1];  Nodex &son2=T[v.s2];
		v.tree.maxa[y]=max( son1.tree.maxa[y] , son2.tree.maxa[y] );
		v.tree.mina[y]=min( son1.tree.mina[y] , son2.tree.mina[y] );
		v.tree.update( v.tree.root , y , v.tree.maxa[y] , v.tree.mina[y] );
	}
}

int BiSegTree::getmax(int now,int xl,int xr,int yl,int yr)
{
	Nodex &v=T[now];
	
	if  (xl==v.l&&xr==v.r)
	{
		return v.tree.getmax(v.tree.root,yl,yr);
	}
	else 
	{
		int t1=-maxint,t2=-maxint;
		     if  (xr<=v.mid)    t1=getmax(v.s1,xl,xr,yl,yr);
		else if  (xl>=v.mid+1)  t2=getmax(v.s2,xl,xr,yl,yr);
		else                 {  t1=getmax(v.s1,xl,v.mid,yl,yr);  t2=getmax(v.s2,v.mid+1,xr,yl,yr);}
		
		return max(t1,t2);
	}
}

int BiSegTree::getmin(int now,int xl,int xr,int yl,int yr)
{
	Nodex &v=T[now];
	
	if  (xl==v.l&&xr==v.r)
	{
		return v.tree.getmin(v.tree.root,yl,yr);
	}
	else 
	{
		int t1=maxint,t2=maxint;
	 	     if  (xr<=v.mid)    t1=getmin(v.s1,xl,xr,yl,yr);
		else if  (xl>=v.mid+1)  t2=getmin(v.s2,xl,xr,yl,yr);
		else                 {  t1=getmin(v.s1,xl,v.mid,yl,yr);  t2=getmin(v.s2,v.mid+1,xr,yl,yr);}
		
		return min(t1,t2);
	}
}

BiSegTree tree;

int times;
int n;
int q;
int x,y,l;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output2.txt","w",stdout);
	
	scanf("%d",&times);
	for (int T=1;T<=times;T++)
	{
		scanf("%d",&n);
		//printf("n:%d\n",n);
		tree.n=n;  tree.m=n;
		memset(tree.a,0,sizeof(tree.a));
		for (int i=1;i<=n;i++)
		    for (int j=1;j<=n;j++)
		        scanf("%d",&tree.a[i][j]);
		
		tree.init();
		
		printf("Case #%d:\n",T);
		
		scanf("%d",&q);
		for (int i=1;i<=q;i++)
		{
			scanf("%d%d%d",&x,&y,&l);
			//printf("x:%d  y:%d  l:%d\n",x,y,l);
			
			l/=2;
			int xl=max(x-l,1);
			int xr=min(x+l,n);
			int yl=max(y-l,1);
			int yr=min(y+l,n);
			//printf("xl:%d  xr:%d  yl:%d  yr:%d\n",xl,xr,yl,yr);
			
			int maxs=tree.getmax(tree.root,xl,xr,yl,yr);
			int mins=tree.getmin(tree.root,xl,xr,yl,yr);
			int sol=(maxs+mins)/2;
			printf("%d\n",sol);
			
			tree.a[x][y]=sol;
			tree.update(tree.root,x,y,sol);
			
		}
		
		
	}
	return 0;
}
