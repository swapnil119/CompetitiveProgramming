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
const int N=1005,iter=105;
db dp[N][N];
db fun(db x,db y)
{
  return ((1.0+(1.0-x)*y)/(1.0-x));
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,m;
  cin>>n>>m;
  int x,y;
  cin>>x>>y;
  cout<<setprecision(10)<<fixed;
  if(m==1)
    {
      db ans=2*(n-x);
      cout<<ans<<endl;
      return 0;
    }
  rep(i,1,m+1) dp[n][i]=0.0;
  repv(i,x,n)
    {
      rep(k,0,iter)
	{
	  dp[i][1]=1.0+(dp[i][1]+dp[i+1][1]+dp[i][2])/3.0;
	  dp[i][m]=1.0+(dp[i][m]+dp[i+1][m]+dp[i][m-1])/3.0;
	  rep(j,2,m)
	    dp[i][j]=1.0+(dp[i][j]+dp[i][j-1]+dp[i][j+1]+dp[i+1][j])/4.0;
	}
    }
  cout<<dp[x][y]<<endl;
  return 0 ;
}
