#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;


struct Line
{   double x,y1,y2;
    int flag;
    Line(double x=0,double y1=0,double y2=0,int flag=0):x(x),y1(y1),y2(y2),flag(flag)  {  }
};

bool operator < (Line A,Line B)  {  return A.x<B.x;}

struct Node
{   int l,r,mid;
	double lx,rx,mx;
	int s1,s2;
	int cover;
	double len1,len2;
};


const int N=2000;
int times;
int n;
Line L[N+100];

double y[N*2+100];


Node T[N*2+100];
int tot,root;

void build(int now,int l,int r)
{
	Node &f=T[now];
	
	f.l=l;      f.r=r;      f.mid=(l+r)/2;
	f.lx=y[l];  f.rx=y[r];  f.mx=y[f.mid];
	f.cover=0;
	f.len1=0;   f.len2=0;
	
	if  (l+1==r)
	{   f.s1=0;  f.s2=0;
	}
	else 
	{  f.s1=++tot;  build(f.s1, f.l, f.mid);
	   f.s2=++tot;  build(f.s2, f.mid, f.r);
	}
}

void cal(int now)
{
	Node &f=T[now];
	
	if       (f.cover>=2)
	{   f.len1 = f.rx - f.lx ;
	    f.len2 = f.len1 ;
	}
	else if  (f.cover==1)
	{   f.len1 = f.rx - f.lx ;
	    f.len2 = T[f.s1].len1 + T[f.s2].len1 ;
	}
	else if  (f.cover==0)
	{   f.len1 = T[f.s1].len1 + T[f.s2].len1 ;
	    f.len2 = T[f.s1].len2 + T[f.s2].len2 ;
	}
}

void update(int now,Line l)
{
	Node &f=T[now];
	
	if  (l.y1==f.lx && l.y2==f.rx)
	{   f.cover+=l.flag;
	}
	else 
	{   if       (l.y2<=f.mx)  update(f.s1, l);
	    else if  (l.y1>=f.mx)  update(f.s2, l);
	    else 
	    {   update(f.s1, Line(l.x, l.y1, f.mx, l.flag));
	        update(f.s2, Line(l.x, f.mx, l.y2, l.flag));
	    }
	}
	
	cal(now);
}


int main()
{
	//freopen("input.txt","r",stdin);
	
	scanf("%d",&times);
	double x1,y1,x2,y2;
	for (int kase=1;kase<=times;kase++)
	{
		scanf("%d",&n);  

		for (int i=1;i<=n;i++)
		{   scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
		    L[i*2-1]=Line(x1, y1, y2, 1);
		    L[i*2  ]=Line(x2, y1, y2, -1);
		    y[i*2-1]=y1;
		    y[i*2  ]=y2;
		}
		
		sort(L+1, L+n*2+1);
		sort(y+1, y+n*2+1);
		int ly=unique(y+1, y+n*2+1)-y-1;
		
	
		root=tot=1;
		build(root, 1, ly);
		
		double sol=0;
		for (int i=1;i<=n*2-1;i++)
		{
			update(root, L[i]);
			sol+= T[root].len2 * ( L[i+1].x - L[i].x );
		}
		
		printf("%.2lf\n",sol);
		
	}
	return 0;
}
