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
const int N=100005,inf=50,MOD=1e9+7;
int a[N],pw[inf+1][inf+1];
map<int,vector<ii> > fac;
int mult(int x,int y,int mod)
{
  ll tmp=(ll)x*y;
  if(tmp>=mod) tmp%=mod;
  return tmp;
}
int pow1(int x,int y,int mod)
{
  x%=mod;
  int ans=1;
  while(y)
    {
      if(y&1) ans=mult(ans,x,mod);
      x=mult(x,x,mod);
      y>>=1;
    }
  return ans;
}
vector<ii> factorise(int x)
{
  assert(x!=1);
  if(fac.count(x)) return fac[x];
  int sq=sqrt(x);
  vector<ii> tmp;
  int phi=1,num=x;
  rep(i,2,sq+1)
    {
      if(x%i) continue;
      int cnt=0,pw=1;
      while(x%i==0) x/=i,cnt++,pw*=i;
      tmp.pb(mp(i,cnt));
      phi*=(pw-pw/i);
    }
  if(x!=1) tmp.pb(mp(x,1)),phi*=(x-1);
  return fac[num]=tmp;
}
int getnext(int l,int r)
{
  vi tmp;
  rep(i,l,min(l+5,r+1))
    {
      if(a[i]==1) break;
      if(a[i]>=inf) return inf;
      tmp.pb(a[i]);
    }
  if(sz(tmp)==0) return 1;
  if(sz(tmp)==1) return tmp[0];
  if(sz(tmp)==2) return pw[tmp[0]][tmp[1]];
  if(sz(tmp)==3) return pw[tmp[0]][pw[tmp[1]][tmp[2]]];
  return inf;
}
int fun(int l,int r,int mod)
{
  if(l==r) return a[l]%mod;
  if(mod==1) return 0;
  int nxtval=getnext(l+1,r);
  if(nxtval<inf) return pow1(a[l],nxtval,mod);
  vector<ii> tmp=factorise(mod);
  int mod1=1,mod2=1,phi=1;
  for(auto it:tmp)
    {
      int pw1=pow1(it.fi,it.se,MOD);
      if(a[l]%it.fi==0)
	mod1*=pw1;
      else
	mod2*=pw1,phi*=(pw1-pw1/it.fi);
    }
  int ans=pow1(a[l],fun(l+1,r,phi),mod2);
  int inv=pow1(mod1,phi-1,mod2);
  ans=mult(ans,mult(mod1,inv,mod),mod);
  return ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,m,q;
  cin>>n>>m;
  rep(i,1,n+1) cin>>a[i];
  rep(i,0,inf+1)
    {
      pw[i][0]=1;
      rep(j,1,inf+1)
	{
	  if(pw[i][j-1]==inf) pw[i][j]=inf;
	  else pw[i][j]=min(inf,pw[i][j-1]*i);
	}
    }
  cin>>q;
  rep(Q,1,q+1)
    {
      int l,r;
      cin>>l>>r;
      cout<<fun(l,r,m)<<endl;
    }
  return 0 ;
}
