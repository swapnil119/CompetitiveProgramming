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
/*answer is always 2 or 3. because there is always a node with degree <=3 as there are 2*n-2 edges. Now try removing 1 edge from both the trees*/
const int N=100005,LN=20;
vector<vi> v,v2;
int p[LN][N],d[N],val[LN][N];
void dfs(int u,vector<vi> &rv,int par=0)
{
  p[0][u]=par; 
  for(int v1:rv[u])
    {
      if(v1==par) continue;
      d[v1]=d[u]+1;
      dfs(v1,rv,u);
    }
}
int lca(int x,int y)
{
  if(d[x]<d[y]) swap(x,y);
  int diff=d[x]-d[y];
  rep(i,0,LN)
    {
      if(diff&(1<<i))
	x=p[i][x];
    }
  if(x==y) return x;
  repv(i,0,LN)
    {
      if(p[i][x]!=p[i][y])
	x=p[i][x],y=p[i][y];
    }
  return p[0][x];
}
int n;
ii solve(vector<vi> &rv,vector<vi> &rv2)
{
  memset(val,0,sizeof(val));
  dfs(1,rv);
  rep(i,1,LN)
    rep(j,1,n+1) p[i][j]=p[i-1][p[i-1][j]];
  rep(i,1,n+1)
    {
      for(int v1:rv2[i])
	{
	  if(v1<i) continue;
	  int lc=lca(v1,i);
	  repv(j,0,LN)
	    {
	      if(d[v1]-(1<<j)>=d[lc])
		{
		  val[j][v1]++;
		  v1=p[j][v1];
		}
	    }
	  v1=i;
	  repv(j,0,LN)
	    {
	      if(d[v1]-(1<<j)>=d[lc])
		{
		  val[j][v1]++;
		  v1=p[j][v1];
		}
	    }
	}
    }
  repv(i,1,LN)
    {
      rep(j,1,n+1)
	{
	  val[i-1][j]+=val[i][j];
	  val[i-1][p[i-1][j]]+=val[i][j];
	}
    }
  int mn=n+1,cnt=0;
  rep(i,2,n+1) mn=min(mn,val[0][i]);
  rep(i,2,n+1) cnt+=(val[0][i]==mn);
  return mp(mn,cnt);
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  cin>>n;
  v.resize(n+2); v2.resize(n+2);
  rep(i,1,n)
    {
      int x,y;
      cin>>x>>y;
      v[x].pb(y); v[y].pb(x);
    }
  rep(i,1,n)
    {
      int x,y;
      cin>>x>>y;
      v2[x].pb(y); v2[y].pb(x);
    }
  ii ans1=solve(v,v2);
  ii ans2=solve(v2,v);
  cout<<min(ans1.fi,ans2.fi)+1<<" ";
  if(min(ans1.fi,ans2.fi)==1)
    cout<<ans1.se<<endl;
  else
    cout<<ans1.se+ans2.se<<endl;
  return 0 ;
}
