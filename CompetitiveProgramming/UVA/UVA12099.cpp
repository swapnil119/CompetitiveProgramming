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
const int N=75;
ii a[N];
/*index, thickness of 2nd shelf, thickness of 3rd shelf*/
int dp[2][N*30][N*30];
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int t;
  cin>>t;
  while(t--)
    {
      int n;
      cin>>n;
      rep(i,1,n+1) cin>>a[i].fi>>a[i].se;
      sort(a+1,a+n+1); reverse(a+1,a+n+1);
      rep(i,0,N*30) rep(j,0,N*30) dp[0][i][j]=dp[1][i][j]=1e9;
      dp[1][0][0]=a[1].fi;
      int sum=0,ans=1e9;
      rep(i,2,n+1)
	{
	  int bit=i&1;
	  rep(j,0,sum+1)
	    {
	      rep(k,0,sum-j+1)
		{
		  //give to first
		  dp[bit][j][k]=min(dp[bit][j][k],dp[1-bit][j][k]);
		  //give to second
		  if(j==0) dp[bit][j+a[i].se][k]=min(dp[bit][j+a[i].se][k],dp[1-bit][j][k]+a[i].fi);
		  else dp[bit][j+a[i].se][k]=min(dp[bit][j+a[i].se][k],dp[1-bit][j][k]);
		  //give to third
		  if(k==0)
		    dp[bit][j][k+a[i].se]=min(dp[bit][j][k+a[i].se],dp[1-bit][j][k]+a[i].fi);
		  else dp[bit][j][k+a[i].se]=min(dp[bit][j][k+a[i].se],dp[1-bit][j][k]);
		}
	    }
	  rep(j,0,sum+1)
	    rep(k,0,sum+1) dp[1-bit][j][k]=1e9;
	  sum+=a[i].se;
	}
      rep(i,1,sum+1)
	rep(j,1,sum-i+1)
	{
	  int mx=max(max(i,j),sum+a[1].se-i-j);
	  if(dp[n&1][i][j]==1e9) continue;
	  ans=min(ans,mx*dp[n&1][i][j]);
	}
      cout<<ans<<endl;
    }
  
  return 0 ;
}
