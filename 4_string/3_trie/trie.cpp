//trie 树 
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

const int N=100000;
const int L=10;
struct node
{   int  c;
    int js;
    int s[30];
};
struct node T[N*L+10000];
int root=1,tot=1;

int n,m;
char st[L+10];

void insert(int now,char st[],int l,int k)
{
	T[now].js++;
	
	if  (k<=l)
	{
		int ch=st[k]-'a';
		if  (T[now].s[ch]==0)  T[now].s[ch]=++tot;
		insert(T[now].s[ch],st,l,k+1);
	}
}



int consult(int now,char st[],int l,int k)
{
	if  (k>l)
	{   return T[now].js;
	}
	else 
	{   int ch=st[k]-'a';
	    return consult(T[now].s[ch],st,l,k+1);
	}
}



int main()
{
	//freopen("input.txt","r",stdin);
	
	scanf("%d\n",&n);
	
	//root=++tot;
	for (int i=1;i<=n;i++)
	{   gets(st);
	    insert(root,st,strlen(st)-1,0);
	}
	
	scanf("%d\n",&m);
	for (int i=1;i<=m;i++)
	{   gets(st);
	    int sol=consult(root,st,strlen(st)-1,0);
	    printf("%d\n",sol);
	}
	
	return 0;
}




