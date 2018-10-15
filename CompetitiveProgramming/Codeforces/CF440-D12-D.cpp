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
const int N=405;
int dp[2][N][N];//min. cost with group at u of size j dp(k,u,j)
int k,n,child[N],a[N],b[N],dp2[2][2][N][N];
vi ret[2][N][N];
vi v[N];
int fun(int ind,int par,int rem,bool kdone,int u,bool done=false)
{
  if(ind==sz(v[u]))
    {
      if((kdone==done) && (rem==0)) return 0;
      return N;
    }
  if(dp2[kdone][done][ind][rem]!=-1) return dp2[kdone][done][ind][rem];
  int idx=v[u][ind];
  int v1=(a[idx]^b[idx]^u);
  if(v1==par) return fun(ind+1,par,rem,kdone,u,done);
  int ans=N;
  //take nothing from here
  rep(i,1,child[v1]+1)//there were i nodes at this node
    {
      if(!kdone)
	{
	  if(i!=k)
	    ans=min(ans,1+dp[0][v1][i]+fun(ind+1,par,rem,kdone,u,done));
	  continue;
	}
      if(i==k)
	ans=min(ans,1+min(dp[1][v1][i],dp[0][v1][i])+fun(ind+1,par,rem,kdone,u,true));
      else
	{
	  ans=min(ans,1+dp[1][v1][i]+fun(ind+1,par,rem,kdone,u,true));
	  ans=min(ans,1+dp[0][v1][i]+fun(ind+1,par,rem,kdone,u,done));
	}
    }
  //take some nodes
  rep(i,1,min(rem,child[v1])+1)
    {
      ans=min(ans,dp[1][v1][i]+fun(ind+1,par,rem-i,kdone,u,true));
      ans=min(ans,dp[0][v1][i]+fun(ind+1,par,rem-i,kdone,u,done));
    }
  return dp2[kdone][done][ind][rem]=ans;
}
vi fun2(int ind,int par,int rem,bool kdone,int u,bool done=false)
{
  if(ind==sz(v[u]))
    {
      vi tmp;
      return tmp;
    }
  int curr=dp2[kdone][done][ind][rem];
  int idx=v[u][ind];
  int v1=(a[idx]^b[idx]^u);
  if(v1==par) return fun2(ind+1,par,rem,kdone,u,done);
  //take nothing from here
  rep(i,1,child[v1]+1)//there were i nodes at this node
    {
      if(!kdone)
	{
	  if(i!=k)
	    if(1+dp[0][v1][i]+fun(ind+1,par,rem,kdone,u,done)==curr)
	      {
		vi tmp=fun2(ind+1,par,rem,kdone,u,done);
		for(int x:ret[0][v1][i])
		  tmp.pb(x);
		tmp.pb(idx);
		return tmp;
	      }
	  continue;
	}
      if(i==k)
	{
	  if(1+dp[1][v1][i]+fun(ind+1,par,rem,kdone,u,true)==curr)
	    {
	      vi tmp=fun2(ind+1,par,rem,kdone,u,true);
	      for(int x:ret[1][v1][i])
		tmp.pb(x);
	      tmp.pb(idx);
	      return tmp;
	    }
	  if(1+dp[0][v1][i]+fun(ind+1,par,rem,kdone,u,true)==curr)
	    {
	      vi tmp=fun2(ind+1,par,rem,kdone,u,true);
	      for(int x:ret[0][v1][i])
		tmp.pb(x);
	      tmp.pb(idx);
	      return tmp;
	    }
	}
      else
	{
	  if(1+dp[1][v1][i]+fun(ind+1,par,rem,kdone,u,true)==curr)
	    {
	      vi tmp=fun2(ind+1,par,rem,kdone,u,true);
	      for(int x:ret[1][v1][i])
		tmp.pb(x);
	      tmp.pb(idx);
	      return tmp;
	    }
	  if(1+dp[0][v1][i]+fun(ind+1,par,rem,kdone,u,done)==curr)
	    {
	      vi tmp=fun2(ind+1,par,rem,kdone,u,done);
	      for(int x:ret[0][v1][i])
		tmp.pb(x);
	      tmp.pb(idx);
	      return tmp;
	    }
	}
    }
  //take some nodes
  rep(i,1,min(rem,child[v1])+1)
    {
      if(dp[1][v1][i]+fun(ind+1,par,rem-i,kdone,u,true)==curr)
	{
	  vi tmp=fun2(ind+1,par,rem-i,kdone,u,true);
	  for(int x:ret[1][v1][i])
	    tmp.pb(x);
	  return tmp;
	}
      if(dp[0][v1][i]+fun(ind+1,par,rem-i,kdone,u,done)==curr)
	{
	  vi tmp=fun2(ind+1,par,rem-i,kdone,u,done);
	  for(int x:ret[0][v1][i])
	    tmp.pb(x);
	  return tmp;
	}
    }
  assert(false);
}
void dfs(int u,int par=-1)
{
  child[u]=1;
  for(int ind:v[u])
    {
      int v1=(a[ind]^b[ind]^u);
      if(v1==par) continue;
      dfs(v1,u);
      child[u]+=child[v1];
    }
  rep(i,0,sz(v[u])+1)
    rep(j,0,child[u]+1)
    rep(l,0,2)
    rep(m,0,2)
    dp2[l][m][i][j]=-1;
  rep(i,1,child[u]+1)
    {
      dp[1][u][i]=fun(0,par,i-1,true,u);
      dp[0][u][i]=fun(0,par,i-1,false,u);
    }
  rep(i,1,child[u]+1)
    {
      if(dp[1][u][i]!=N) ret[1][u][i]=fun2(0,par,i-1,true,u);
      if(dp[0][u][i]!=N) ret[0][u][i]=fun2(0,par,i-1,false,u);
    }
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  cin>>n>>k;
  rep(i,1,n)
    {
      int x,y;
      cin>>x>>y;
      a[i]=x; b[i]=y;
      v[x].pb(i); v[y].pb(i);
    }
  dfs(1);
  int ans=N;
  vi ansv;
  rep(i,1,n+1)
    {
      if(i==k)
	{
	  if(dp[0][1][i]<ans)
	    ansv=ret[0][1][i],ans=dp[0][1][i];
	  else if(dp[1][1][i]<ans)
	    ansv=ret[1][1][i],ans=dp[1][1][i];
	}
      else
	{
	  if(dp[1][1][i]<ans)
	    ansv=ret[1][1][i],ans=dp[1][1][i];
	}
    }
  cout<<ans<<endl;
  for(int x:ansv) cout<<x<<" "; cout<<endl;
  return 0 ;
}
