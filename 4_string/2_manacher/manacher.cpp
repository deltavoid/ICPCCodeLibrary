//manacher 
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int L=1000000;
int n;
char s[L+1000];
char a[L*2+1000];
int p[L*2+1000];

void Manacher(char s[],int len)
{
	int l=0;
	a[l++]='$';
	a[l++]='#';
	for (int i=0;i<len;i++)
	{   a[l++]=s[i];
	    a[l++]='#';
	}
	a[l]=0;
	
	memset(p,0,sizeof(p));
	
	int mx=0,id=0;
	for (int i=0;i<l;i++)
	{   
	    p[i]=mx>i? min(p[2*id-i],mx-i) :1;
	    while (a[i+p[i]]==a[i-p[i]])  p[i]++;
	    
	    if  (i+p[i]>mx)  {  mx=i+p[i];  id=i;}
	}
	
}

int main()
{
	//freopen("input.txt","r",stdin);
	
	scanf("%d\n",&n);
	for (int t=1;t<=n;t++)
	{
		gets(s);
		int len=strlen(s);
		
		Manacher(s,len);
		
		int ans=0;
		for (int i=0;i<2*len+2;i++)
		    ans=max(ans,p[i]-1);
		printf("%d\n",ans);   
		
	}
	return 0;
}
