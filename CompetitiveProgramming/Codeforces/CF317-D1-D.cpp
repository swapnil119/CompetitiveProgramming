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
map<int,vi> m;
map<ii,int> dp;
map<int,bool> done;
int fun(int mask,int n)
{
  if(__builtin_popcount(mask)==0)
    return 0;
  if(dp.count(mp(mask,n))) return dp[mp(mask,n)];
  set<int> s;
  rep(i,0,n)
    {
      if(!(mask&(1<<i))) continue;
      int nxt=mask;
      for(int j=i;j<n;j+=(i+1))
	{
	  if(mask&(1<<j))
	    nxt^=(1<<j);
	}
      s.insert(fun(nxt,n));
    }
  int curr=0;
  while(true)
    {
      if(!s.count(curr)) return dp[mp(mask,n)]=curr;
      curr++;
    }
  assert(false);
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n;
  cin>>n;
  int sq=sqrt(n);
  int cnt=0;
  rep(i,2,sq+1)
    {
      if(done.count(i)) continue;
      for(int pw=i;pw<=n;pw*=i)
	m[i].pb(pw),cnt++,done[pw];
    }
  int rem=n-cnt;
  int grundy=0;
  for(auto it:m)
    {
      int sz=sz(it.se);
      grundy^=fun((1<<sz)-1,sz);
    }
  if(rem&1) grundy^=1;
  if(grundy) cout<<"Vasya"<<endl;
  else cout<<"Petya"<<endl;
  return 0 ;
}
