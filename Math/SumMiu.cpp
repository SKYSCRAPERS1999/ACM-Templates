#include<bits/stdc++.h>
#define MAXN 5000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
bool is_prime[MAXN];
int cnt,mu[MAXN],prime[MAXN];
ll n,m,f[MAXN];
map<ll,ll> mp;
void genmiu(int n)
{
    int p=0;
    for(int i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    memset(mu,0,sizeof(mu));
    mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; mu[i]=-1;}
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            mu[i*prime[j]]=i%prime[j]?-mu[i]:0;
            if(i%prime[j]==0) break;
        }
    }
    for(int i=1;i<=n;i++) f[i]=f[i-1]+mu[i];
}
ll calc(ll x)
{
	if(x<=5000000) return f[x];
	if(mp.find(x)!=mp.end()) return mp[x];
	ll ans=1;
	for(ll i=2,r;i<=x;i=r+1)
	{
		r=x/(x/i);
		ans-=calc(x/i)*(r-i+1);
	}
	return mp[x]=ans;
}
int main()
{
	genmiu(5000000);
	scanf("%lld%lld",&n,&m);
	printf("%lld\n",calc(m)-calc(n-1));
	return 0;
}
