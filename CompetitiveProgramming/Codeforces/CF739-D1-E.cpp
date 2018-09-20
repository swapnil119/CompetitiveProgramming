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
const int N=2005,iter=55;
db p[N],u[N],pu[N],dp[N];
int best[N],n;
ii fun(db mid,db mid2)
{
  rep(i,1,n+1)
    {
      dp[i]=dp[i-1];
      best[i]=0;
      if(dp[i-1]+p[i]-mid>dp[i])
	{
	  dp[i]=dp[i-1]+p[i]-mid;
	  best[i]=1;
	}
      if(dp[i-1]+u[i]-mid2>dp[i])
	{
	  dp[i]=dp[i-1]+u[i]-mid2;
	  best[i]=2;
	}
      if(dp[i-1]+pu[i]-mid-mid2>dp[i])
	{
	  dp[i]=dp[i-1]+pu[i]-mid-mid2;
	  best[i]=3;
	}
    }
  ii ans=mp(0,0);
  rep(i,1,n+1)
    {
      if(best[i]>=2) ans.se++;
      if(best[i]&1) ans.fi++;
    }
  return ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int a,b;
  cin>>n>>a>>b;
  rep(i,1,n+1) cin>>p[i];
  rep(i,1,n+1) cin>>u[i];
  rep(i,1,n+1) pu[i]=p[i]+u[i]-p[i]*u[i];
  db low=0,high=1.0,low2,high2;
  rep(i,0,iter)
    {
      db mid=(low+high)/2.0;
      low2=0.0,high2=1.0;
      rep(j,0,iter)
	{
	  db mid2=(low2+high2)/2.0;
	  if(fun(mid,mid2).se>b) low2=mid2;
	  else high2=mid2;
	}
      if(fun(mid,high2).fi>a) low=mid;
      else high=mid;
    }
  fun(high,high2);
  cout<<setprecision(10)<<fixed<<dp[n]+high2*b+high*a<<endl;
  return 0 ;
}
