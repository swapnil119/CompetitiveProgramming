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
const int N=200005,LN=22,mod=(int)1e9+7,N1=2005;
int add(int x,int y)
{
  x+=y;
  if(x>=mod) x-=mod;
  if(x<0) x+=mod;
  return x;
}
int mult(int x,int y)
{
  ll tmp=(ll)x*y;
  if(tmp>=mod) tmp%=mod;
  return tmp;
}
int pow1(int x,int y)
{
  int ans=1;
  while(y)
    {
      if(y&1) ans=mult(ans,x);
      x=mult(x,x);
      y>>=1;
    }
  return ans;
}
ii a[N];
int ways[N1][N1],f[N],inv[N],dp[LN][N1];
//dp(i,j) is no. of ways to reach cell j with i anomalies
int fun(int x1,int y1,int x2,int y2)
{
  int x=x2-x1,y=y2-y1;
  return mult(f[x+y],mult(inv[x],inv[y]));
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  f[0]=inv[0]=1;
  rep(i,1,N) f[i]=mult(f[i-1],i);
  inv[N-1]=pow1(f[N-1],mod-2);
  repv(i,1,N-1) inv[i]=mult(inv[i+1],i+1);
  int n,m,k,s;
  cin>>n>>m>>k>>s;
  rep(i,1,k+1)
    cin>>a[i].fi>>a[i].se;
  a[++k]=mp(n,m);
  sort(a+1,a+k+1);
  //this is for computing number of ways to reach ith anomaly without touching another anomaly
  rep(i,1,k+1) dp[1][i]=fun(1,1,a[i].fi,a[i].se);
  rep(i,1,k)
    rep(j,i+1,k+1)
    {
      if(a[j].se<a[i].se) continue;
      dp[1][j]=add(dp[1][j],-mult(dp[1][i],fun(a[i].fi,a[i].se,a[j].fi,a[j].se)));
    }
  dp[0][k]=dp[1][k]; dp[1][k]=0;//this is (n,m)
  //for calculating ways to touch exactly i anomalies
  rep(i,2,LN)
    {
      rep(j,1,k)
	{
	  dp[i][j]=fun(1,1,a[j].fi,a[j].se);//consider all paths
	  rep(l,1,j)//this removes all paths with at least i+1 anomalies
	    {
	      if(a[j].se<a[l].se || i==LN-1) continue;
	      dp[i][j]=add(dp[i][j],-mult(dp[i][l],fun(a[l].fi,a[l].se,a[j].fi,a[j].se)));
	    }
	  //this removes all paths with exactly l anomalies
	  rep(l,0,i) dp[i][j]=add(dp[i][j],-dp[l][j]);
	}
    }
  //for (n,m)
  rep(i,1,LN)
    {
      dp[i][k]=fun(1,1,n,m);
      rep(j,1,k)//this removes all paths with at least i+1 anomalies
	{
	  if(i!=LN-1)
	    dp[i][k]=add(dp[i][k],-mult(dp[i+1][j],fun(a[j].fi,a[j].se,n,m)));
	}
      //this removes all paths with exactly l anomalies
      rep(j,0,i)
	dp[i][k]=add(dp[i][k],-dp[j][k]);
    }
  int ans=0;
  rep(i,0,LN)
    {
      ans=add(ans,mult(s,dp[i][k]));
      s=(s+1)/2;
    }
  ans=mult(ans,pow1(fun(1,1,n,m),mod-2));
  cout<<ans<<endl;
  return 0;
}
