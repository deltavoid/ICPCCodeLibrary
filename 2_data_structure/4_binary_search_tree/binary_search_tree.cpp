//二叉排序树

const int N;
struct node
{   int v,s;
    int s1,s2;
};
struct node T[N+10];
int tot;

int n;



void insert(int now,int x)
{
	if  (x==T[now].v)
	{   T[now].s++;
	}
	else if  (x<T[now].v)
	{
		if  (T[now].s1==0)
		{
			int p=++tot;
			T[p].v=x;
			T[p].s=1;
			T[now].s1=p;
		}
		else 
		{   insert(T[now].s1,x);
		}
	}
	else if  (x>T[now].v)
	{
		if  (T[now].s2==0)
		{
			int p=++tot;
			T[p].v=x;
			T[p].s=1;
			T[now].s2=p;
		}
		else
		{   insert(T[now].s2,x);
		}
	}
}


void del(int now,int x)
{
	if  (now==0)  return ;
	
	if  (x==T[now].v)
	{   T[now].s--;
	}
	else if  (x<T[now].v)
	{   del(T[now].s1,x);
	}
	else if  (x>T[now].v)
	{   del(T[now].s2,x);
	}
}

void output(int now)
{
	if  (now==0)  return ;
	
	output(T[now].s1);
	
	for (int i=1;i<=T[now].s;i++)
	    printf("%d ",T[now].v);
	
	output(T[now].s2);
	
}

