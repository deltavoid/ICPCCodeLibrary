// cf55D
// 数位dp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
typedef long long ll;

const ll N=20;
const ll Mod=2520;
const ll Cnt=50;
ll times;
ll n,m;

ll dp[N+5][Mod+10][Cnt+10];

ll bit[N+5];
ll l;

ll hash[Mod+10];



ll gcd(ll a,ll b)
{   ll r=a%b;
    while (r!=0)
    {   a=b;
        b=r;
        r=a%b;
    }
    return b;
}

ll lcm(ll a,ll b)
{   return a / gcd(a, b) * b ;
}

void init()
{
	ll cnt=0;
	for (ll i=1;i<=Mod;i++)
	    if  (Mod%i==0)  hash[i]=++cnt;
}



ll dfs(ll k,ll rest,ll mod,bool limit)
{
	if  (k==0)  return rest%mod==0? 1 : 0 ;
	
	if  (!limit && dp[k][rest][hash[mod]]>=0)  return dp[k][rest][hash[mod]];
	
	ll ans=0;
	ll end= limit? bit[k] : 9 ;
	ll next_rest, next_mod;
	for (ll i=0;i<=end;i++)
	{
		next_rest= (rest * 10 + i ) % Mod ;
		next_mod= i==0? mod : lcm(mod, i) ;
		
		ans+= dfs(k-1, next_rest, next_mod, (limit && i==end) );
	}
	
	if  (!limit)  dp[k][rest][hash[mod]]=ans;
	return ans;
	
	
}


ll query(ll n)
{
	memset(bit,0,sizeof(bit));
	l=0;
	
	for (ll i=n;i>=1;i/=10)
	    bit[++l]=i%10;
	
	return dfs(l, 0, 1, true);
}


int main()
{
	//freopen("input2.txt","r",stdin);
	
	init();
	memset(dp,-1,sizeof(dp));
	
	scanf("%I64d",&times);
	for (ll T=1;T<=times;T++)
	{
		scanf("%I64d%I64d",&n,&m);
		
		ll sol= query(m) - query(n-1) ;
		printf("%I64d\n",sol);
	}
	return 0;
}
