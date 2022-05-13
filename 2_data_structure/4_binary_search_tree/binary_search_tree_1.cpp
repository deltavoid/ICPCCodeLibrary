//二叉排序树  改1

const int N;
struct node
{   int v,js;
    int s[2];
};
struct node T[N+10];
int tot;

int n;



void insert(int now,int x)
{
	int v=T[now].v;
	if  (x==v)
	{   T[now].js++;
	}
	else 
	{
		int r=(x>v);
		//if  (x<v)  int r=0;  else int r=1;
		
		if  (T[now].s[r]==0)
		{   int p=++tot;
		    T[p].v=x;
		    T[p].js=1;
		    T[now].s[r]=p;
		}
		else
		{   insert(T[now].s[r],x);
		}
	}
}

void del(int now,int x)
{
	if  (now==0)  return ;
	
	if  (x==T[now].v)
	{   T[now].js--;
	}
	else
	{   int r=(x>T[now].v);
	    del(T[now].s[r],x);
	}
}

void output(int now)
{
	if  (now==0)  return ;
	
	output(T[now].s[0]);
	
	for (int i=1;i<=T[now].js;i++)
	    printf("%d ",T[now].v);
	
	output(T[now].s[1]);
}



