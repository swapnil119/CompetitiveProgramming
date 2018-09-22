#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long
#define db long double
#define ii pair<int,int>
#define vi vector<int>
#define fi first
#define se second
#define sz(a) (int)(a).size()
#define all(a) (a).begin(),(a).end()
#define pb push_back
#define mp make_pair
#define FN(i, n) for (int i = 0; i < (int)(n); ++i)
#define FEN(i,n) for (int i = 1;i <= (int)(n); ++i)
#define rep(i,a,b) for(int i=a;i<b;i++)
#define repv(i,a,b) for(int i=b-1;i>=a;i--)
#define SET(A, val) memset(A, val, sizeof(A))
typedef tree<int ,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>ordered_set ;
// order_of_key (val): returns the no. of values less than val
// find_by_order (k): returns the kth largest element.(0-based)
#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
  cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
  const char* comma = strchr(names + 1, ','); cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif
//chinese remainder theorem, do brute decays in logn, mod becomes 1
const int N=10000005,bigmod=1e9+7;
int phi[N],sp[N];
void sieve()
{
  int i,j;
  rep(i,1,N) phi[i]=i;
  rep(i,2,N)
    {
      if(phi[i]!=i) continue;
      for(j=2*i;j<N;j+=i)
	phi[j]-=phi[j]/i,sp[j]=i;
      phi[i]=i-1;
      sp[i]=i;
    }
}
int mult(int x,int y,int mod)
{
  ll tmp=(ll)x*y;
  if(tmp>=mod) tmp%=mod;
  return tmp;
}
int pow1(int x,int y,int mod)
{
  int ans=1;
  while(y)
    {
      if(y&1) ans=mult(ans,x,mod);
      x=mult(x,x,mod);
      y>>=1;
    }
  return ans;
}
vector<ii> primes;
void factorise(int mod)
{
  primes.clear();
  while(mod!=1)
    {
      int tmp=sp[mod],cnt=0;
      while(mod%tmp==0)
	mod/=tmp,cnt++;
      primes.pb(mp(tmp,cnt));
    }
  reverse(all(primes));
}
int getnext(int i,int b)
{
  if(i==1) return b;
  if(i==2)
    {
      if(b<=3) return pow1(b,b,bigmod);
      return bigmod;
    }
  if(b>2) return bigmod;
  if(i<=4)
    {
      int pw=1;
      while(i--) pw=pow1(b,pw,bigmod);
      return pw;
    }
  return bigmod;
}
int fun(int i,int b,int mod)
{
  if(mod==1) return 0;
  if(i==0 || b==1) return 1;
  if(i==1) return b%mod;
  int nxtval=getnext(i-1,b);
  if(nxtval!=bigmod)
    return pow1(b,nxtval,mod);
  factorise(mod);
  int mod1=1,mod2=1;
  for(auto it:primes)
    {
      if(b%it.fi==0) mod1*=pow1(it.fi,it.se,bigmod);
      else mod2*=pow1(it.fi,it.se,bigmod);
    }
  int ans=pow1(b,fun(i-1,b,phi[mod2]),mod2);
  int pp=mod1;
  int inv=pow1(pp,phi[mod2]-1,mod2);
  ans=mult(ans,mult(pp,inv,mod),mod);
  return ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; //cout.tie(NULL) ;
  sieve();
  int b,i,n;
  while(cin>>b)
    {
      if(!b) break;
      cin>>i>>n;
      int tmp=n;
      n=pow1(10,n,bigmod);
      int ret=fun(i,b,n);
      string ans=to_string(ret);
      rep(i,0,tmp-sz(ans)) cout<<0;
      cout<<ans<<endl;
    }
  return 0 ;
}

