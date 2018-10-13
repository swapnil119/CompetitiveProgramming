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
const int N=1000005;
vi v[N];
int dp[N],k;
ii tmp[N];
void dfs(int u)
{
  if(!sz(v[u]))
    {
      dp[u]=1;
      tmp[u]=mp(1,1);
      return;
    }
  tmp[u]=mp(0,N);
  for(int v1:v[u])//tmp is for those nodes which can reach u back
    {
      dfs(v1);
      if(tmp[v1].se<=k)//min. depth req. to reach here
	tmp[u]=mp(tmp[u].fi+tmp[v1].fi,min(tmp[u].se,tmp[v1].se));
    }
  tmp[u].se++;
  dp[u]=0;
  for(int v1:v[u])//reach v1 at last
    {
      if(tmp[v1].se<=k)
	dp[u]=max(dp[u],dp[v1]+tmp[u].fi-tmp[v1].fi);
      else
	dp[u]=max(dp[u],dp[v1]+tmp[u].fi);
    }
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n;
  cin>>n>>k;
  rep(i,2,n+1)
    {
      int x;
      cin>>x;
      v[x].pb(i);
    }
  dfs(1);
  cout<<dp[1]<<endl;
  return 0 ;
}
