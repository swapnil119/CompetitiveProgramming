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
const ll inf=(ll)1e18;
const int N=7000005;
int c1,c2,sq2[N];
map<ll,ll> dp,dp2;
ll dpa[N],dpb[N];
map<ll,vector<ll> > store;
void faltu(ll n)
{
  if(n==1) return;
  if(store.count(n)) return ;
  int sq;
  if(n>=N) sq=sqrt(n);
  else sq=sq2[n];
  rep(i,1,sq+1)
    {
      if(n%i) continue;
      store[n].pb(i); faltu(i);
      if((ll)i*i!=n && i!=1) store[n].pb(n/i),faltu(n/i);
    }
}
ll fun(ll n)
{
  if(n==1) return 0;
  if(n>=N)
    {
      if(dp.count(n)) return dp[n];
    }
  else if(dpa[n]!=-1) return dpa[n];
  ll ans=inf;
  for(ll i:store[n])
    ans=min(ans,(ll)c1+fun(i)+(n/i-1)*c2);
  if(n>=N)
    return dp[n]=ans;
  else
    return dpa[n]=ans;
}
ll fun2(ll n)
{
  ll ans2=fun(n);
  if(n==1) return 1;
  if(n>=N)
    {
      if(dp2.count(n)) return dp2[n];
    }
  else if(dpb[n]!=-1) 
    return dpb[n];
  ll ans=0;
  for(ll i:store[n])
    {
      ll tmp=fun(i);
      if((ll)c1+tmp+(n/i-1)*c2==ans2)
    ans+=fun2(i);
    }
  if(n>=N)
    return dp2[n]=ans;
  else
    return dpb[n]=ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  memset(dpa,-1,sizeof(dpa));
  memset(dpb,-1,sizeof(dpb));
  ll n;
  cin>>n>>c1>>c2;
  rep(i,1,N) sq2[i]=sqrt(i);
  faltu(n);
  ll ans1=fun(n);
  ll ans2=fun2(n);
  cout<<ans1<<" "<<ans2<<endl;
  return 0 ;
}
