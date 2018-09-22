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
const int N=205,K=1005,mod=1e9+7;
int dp[N][N][K];//till ith index, j elements are left to map, and k is cost
int a[N];
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
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,k;
  cin>>n>>k;
  rep(i,1,n+1) cin>>a[i];
  sort(a+1,a+n+1);
  dp[1][0][0]=1;
  dp[1][1][0]=1;
  rep(i,2,n+1)
    {
      int diff=a[i]-a[i-1];
      rep(j,0,i)//these elements are left to map
	{
	  rep(l,0,k+1)//this cost is done
	    {
	      int nxt=l+diff*j;
	      if(nxt>k) continue;
	      //map it with 1 element
	      if(j)
		{
		  //this is end of this group
		  dp[i][j-1][nxt]=add(dp[i][j-1][nxt],mult(dp[i-1][j][l],j));
		  //this group will go ahead
		  dp[i][j][nxt]=add(dp[i][j][nxt],mult(dp[i-1][j][l],j));
		}
	      //make new group
	      //end it here
	      dp[i][j][nxt]=add(dp[i][j][nxt],dp[i-1][j][l]);
	      //this will go ahead
	      dp[i][j+1][nxt]=add(dp[i][j+1][nxt],dp[i-1][j][l]);
	    }
	}
    }
  int ans=0;
  rep(i,0,k+1) ans=add(ans,dp[n][0][i]);
  cout<<ans<<endl;
  return 0 ;
}
