//边集数组

const int N;
const int M;
struct edge
{   int u,v;
    int w;
    int next;
};
struct edge E[M+10];
int s[N+1],tot;

int n;


void add_edge(int u,int v,int w)
{
	int p=++tot;
	E[p].u=u;  E[p].v=v;  E[p].w=w;
	E[p].next=s[u];  
	s[u]=p;
}

void give_edge(int u)
{
	for (int i=s[u];i!=0;i=E[i].next)
	{   edge e=E[i];
	    printf("%d %d %d\n",e.u,e.v,e.w);
	}
}



