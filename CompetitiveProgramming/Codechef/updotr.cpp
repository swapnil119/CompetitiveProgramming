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
const int N=1000005,LN=20;
vi v[N];
int pre[N],mx[N],d[N],a[N],p[LN][N];
int mx2[LN][N];
void dfs(int u,int par=0)
{
  mx[u]=max(mx[u],a[u]);
  if(par) mx2[0][u]=mx[par];
  p[0][u]=par;
  for(int v1:v[u])
    {
      if(v1==par) continue;
      d[v1]=d[u]+1;
      pre[v1]=pre[u];
      if(a[v1]>mx[u]) pre[v1]++;
      mx[v1]=mx[u];
      dfs(v1,u);
    }
}
int fun(int u,int x)
{
  rep(i,0,LN)
    if(x&(1<<i)) u=p[i][u];
  return u;
}
int main()
{
  int t;
  scanf("%d",&t);
  while(t--)
    {
      int n;
      scanf("%d",&n);
      rep(i,1,n+1) scanf("%d",&a[i]);
      rep(i,2,n+1)
	{
	  int x;
	  scanf("%d",&x);
	  v[x].pb(i); v[i].pb(x);
	}
      dfs(1);
      rep(i,1,LN)
	rep(j,1,n+1)
	p[i][j]=p[i-1][p[i-1][j]];
      rep(i,1,LN)
	rep(j,1,n+1) mx2[i][j]=mx2[i-1][p[i-1][j]];
      int q,curr=0;
      scanf("%d",&q);
      while(q--)
	{
	  int x,y;
	  scanf("%d %d",&x,&y);
	  x^=curr; y^=curr;
	  int ans=0;
	  if(a[1]==y) ans=pre[x];
	  else if(a[1]>y) ans=pre[x]+1;
	  else if(mx[x]<=y) ans=0;
	  else
	    {
	      int diff=d[x]+1,x1=x;
	      repv(i,0,LN)
		{
		  if(mx2[i][x1]==0) continue;
		  if(mx2[i][x1]>y) x1=p[i][x1];
		}
	      int tmp=fun(x,d[x]-d[x1]);
	      assert(tmp==x1);
	      ans=pre[x]-pre[tmp]+1;
	    }
	  printf("%d\n",ans);
	  curr=ans;
	}
      rep(i,1,n+1) pre[i]=0,mx[i]=0,v[i].clear();
    }
  return 0 ;
}
