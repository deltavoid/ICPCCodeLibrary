#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std; 

const int N=50000;
const int M=50000;
struct arrow
{   int d,p;
};
int n,m;
int b[N+100];
arrow A[M+100];

int heap[M+100];
int l;

bool cmp1(int x,int y)  {  return (x>y);}

bool cmp2(arrow x,arrow y)  {  return (x.d>y.d);}

bool cmp3(int x,int y)  {  return (A[x].p<A[y].p);}

void heap_up(int a[],int l,int x)
{
	while (x>1)
	{
		int f=x/2;
		if  (cmp3(a[x],a[f]))  {  swap(a[x],a[f]);  x=f;}
		else break;
	}
}

void heap_down(int a[],int l,int x)
{
	while (x*2<=l)
	{
		int s=x*2;
		if  (s+1<=l&&cmp3(a[s+1],a[s]))  s=s+1;
		if  (cmp3(a[s],a[x]))  {  swap(a[s],a[x]);  x=s;}
		else break;
	}
}

void heap_check(int a[],int l)
{
	for (int i=1;i<=l;i++)
	    printf("%d ",a[i]);
	printf("\n");
}

void heap_in(int x)
{
	heap[++l]=x;
	heap_up(heap,l,l);
}

int heap_out()
{
	int sol=heap[1];
	heap[1]=heap[l--];
	heap_down(heap,l,1);
	return sol;
}

bool heap_none()
{
	return (l==0);
}

int main()
{
	freopen("input.txt","r",stdin);
	
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	    scanf("%d",&b[i]);
	for (int i=1;i<=m;i++)
	    scanf("%d%d",&A[i].d,&A[i].p);
	
	sort(b+1,b+n+1,cmp1);
	sort(A+1,A+m+1,cmp2);
	
	bool flag=true;
	int sol=0;
	int j=0;
	for (int i=1;i<=n;i++)
	{
		while (j+1<=m&&A[j+1].d>=b[i])  heap_in(++j);
		
		if  (!heap_none())
		{
			int t=heap_out();
			sol+=A[t].p;
		}
		else 
		{
			flag=false;
			break;
		}
	}
	
	if  (flag)  printf("%d\n",sol);
	else printf("No Solution\n");
	
	return 0;
}

