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
//sqrt decomposition, take best sqrt nodes
const int N=200005,S=100;
vi v[N],v2[N];
vector<ii> best[N];
bool vis[N];
int d[N];
bool mark[N];
void dfs(int u)
{
  if(vis[u]) return;
  vis[u]=true;
  for(int v1:v2[u]) dfs(v1);
  for(int v1:v2[u])
    {
      d[v1]=0;
      for(auto it:best[v1]) d[it.se]=0;
    }
  for(int v1:v2[u])
    for(auto it:best[v1]) d[it.se]=max(d[it.se],it.fi+1);
  vector<ii> tmp;
  for(int v1:v2[u])
    {
      tmp.pb(mp(max(d[v1],1),v1));
      for(auto it:best[v1])
	tmp.pb(mp(d[it.se],it.se));
    }
  sort(all(tmp));
  tmp.erase(unique(all(tmp)),tmp.end());
  reverse(all(tmp));
  rep(i,0,min(S,sz(tmp)))
    best[u].pb(tmp[i]);
}
void dfs2(int u)
{
  if(vis[u]) return;
  vis[u]=true;
  for(int v1:v2[u]) dfs2(v1);
  for(int v1:v2[u])
    {
      if(d[v1]!=-1)
	d[u]=max(d[u],d[v1]+1);
      if(!mark[v1])
	d[u]=max(d[u],1);
    }
  if(!mark[u]) d[u]=max(d[u],0);
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
      v[x].pb(y); v2[y].pb(x);
    }
  //find best S nodes for each i, dist. wise
  rep(i,1,n+1) dfs(i);
  while(q--)
    {
      int x,k;
      cin>>x>>k;
      vi tmp;
      rep(i,1,k+1)
	{
	  int y;
	  cin>>y; mark[y]=true; tmp.pb(y);
	}
      if(k<S)
	{
	  int ans=-1;
	  for(auto it:best[x])
	    {
	      if(!mark[it.se])
		{
		  ans=it.fi;
		  break;
		}
	    }
	  if(!mark[x]) ans=max(ans,0);
	  cout<<ans<<endl;
	  for(int x:tmp) mark[x]=false;
	  continue;
	}
      rep(i,1,n+1) d[i]=-1,vis[i]=false;
      dfs2(x);
      cout<<d[x]<<endl;
      for(int x:tmp) mark[x]=false;
    }
  return 0 ;
}
