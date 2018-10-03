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
typedef tree<pair<int, int> ,null_type,less<pair<int, int>>,rb_tree_tag,tree_order_statistics_node_update>ordered_set ;
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

const int N=500005,LN=20;
vi v[N],v2[N];
bool vis[N];
int p[LN][N],d[N];
void dfs(int u,int par=0)
{
  p[0][u]=par;
  for(int v1:v2[u])
    {
      if(v1==par) continue;
      d[v1]=d[u]+1;
      dfs(v1,u);
    }
}
ii lca(int x,int y)
{
  bool change=false;
  if(d[x]<d[y]) change=true,swap(x,y);
  int diff=d[x]-d[y];
  rep(i,0,LN)
    if(diff&(1<<i))
      x=p[i][x];
  if(x==y) return mp(x,x);
  repv(i,0,LN)
    if(p[i][x]!=p[i][y])
      x=p[i][x],y=p[i][y];
  if(change) return mp(y,x);
  return mp(x,y);
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,m,q;
  cin>>n>>m>>q;
  rep(i,1,m+1)
    {
      int x,y;
      cin>>x>>y;
      v[x].pb(y); v[y].pb(x);
    }
  rep(i,1,n+1) sort(all(v[i]));
  vis[1]=true;
  queue<int> qu;
  qu.push(1);
  while(!qu.empty())
    {
      int u=qu.front();
      qu.pop();
      for(int v1:v[u])
	{
	  if(vis[v1]) continue;
	  vis[v1]=true;
	  qu.push(v1);
	  v2[u].pb(v1);
	}
    }
  dfs(1,-1);
  rep(i,1,LN)
    rep(j,1,n+1) p[i][j]=p[i-1][p[i-1][j]];
  while(q--)
    {
      int x,y;
      cin>>x>>y;
      ii lc=lca(x,y);
      if(lc.fi==lc.se)
	cout<<abs(d[y]-d[x])<<endl;
      else
	{
	  int ans=d[y]-d[lc.fi]+d[x]-d[lc.se]+1;
	  int ind=lower_bound(all(v[lc.fi]),lc.se)-v[lc.fi].begin();
	  if(ind<sz(v[lc.fi]) && v[lc.fi][ind]==lc.se) ;
	  else ans++;
	  cout<<ans<<endl;
	}
    }
  return 0 ;
}
