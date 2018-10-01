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
const int mod=1e9+7,N=2005;
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
int dp[N][N];//elements done from i to n, and no. of elements before i+1
int n,pre[N][N];
bool a[N];
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  cin>>n;
  rep(i,1,n)
    {
      int x;
      cin>>x;
      a[i]=x;
    }
  dp[n][0]=pre[n][0]=1;
  rep(j,1,n+1) pre[n][j]=pre[n][j-1]+dp[n][j];
  repv(i,1,n)
    {
      rep(j,0,n-i+1)
	{
	  if(a[i])//this comes before i+1
	    {
	      if(!j) dp[i][j]=pre[i+1][n];
	      else dp[i][j]=add(pre[i+1][n],-pre[i+1][j-1]);
	    }
	  else
	    {
	      if(j) dp[i][j]=pre[i+1][j-1];
	    }
	}
      pre[i][0]=dp[i][0];
      rep(j,1,n+1) pre[i][j]=add(pre[i][j-1],dp[i][j]);
    }
  int ans=0;
  rep(i,0,n) ans=add(ans,dp[1][i]);
  cout<<ans<<endl;
  return 0 ;
}
