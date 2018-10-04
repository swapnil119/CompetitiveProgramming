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
#define pli pair<ll,ll>
map<pli,pli> dp;
pli fun(ll n,ll mx)
{
  if(n==0) return mp(0,0);
  if(n<10)
    {
      pli ans=mp(1,0);
      if(mx>n) ans.se=n-mx;
      return ans;
    }
  ll tn=n;
  if(dp.count(mp(n,mx))) return dp[mp(n,mx)];
  ll mod=1;
  while(mod<=n/10) mod*=10;
  pli ans=mp(0,0);
  while(true)
    {
      ll nmx=mx;
      ll d=n/mod;
      nmx=max(nmx,d);
      pli tmp=fun(n%mod,nmx);
      ans.fi+=tmp.fi;
      if(tmp.se<0)
	n=n-(n%mod)+tmp.se;
      else if(tmp.se==0)
	{
	  n=n-(n%mod)-nmx;
	  if(nmx) ans.fi++;
	}
      if(d==0) break;
    }
  ans.se=n;
  return dp[mp(tn,mx)]=ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  ll n;
  cin>>n;
  cout<<fun(n,0).fi<<endl;
  return 0 ;
}
