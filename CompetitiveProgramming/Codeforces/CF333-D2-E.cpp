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
const int N=105,M=1005;
int val[N],n,m;
db dp[2][N*M],dpsum[2][N*M];
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int sum=0;
  cin>>n>>m;
  if(m==1)
    {
      cout<<1.0<<endl;
      return 0;
    }
  rep(i,1,n+1) cin>>val[i],sum+=val[i];
  dp[0][0]=1.0;
  rep(i,0,m+1) dpsum[0][i]=1.0;
  const db tmp=1.0/(db)(m-1);
  rep(i,1,n+1)
    {
      int bit=(i&1);
      rep(j,1,i*m+1)
	{
	  int pre=max(j-m,0);
	  if(!pre) dp[bit][j]=tmp*dpsum[1-bit][j-1];
	  else dp[bit][j]=tmp*(dpsum[1-bit][j-1]-dpsum[1-bit][pre-1]);
	  if(j-val[i]>=0) dp[bit][j]-=tmp*dp[1-bit][j-val[i]];
	}
      rep(j,0,(i+1)*m+1) dpsum[bit][j]=((j==0)?dp[bit][j]:dpsum[bit][j-1]+dp[bit][j]);
      rep(j,0,(i+1)*m+1) dp[1-bit][j]=dpsum[1-bit][j]=0.0;
    }
  db ans=0.0;
  rep(i,0,sum) ans+=dp[n&1][i];
  ans*=(db)(m-1);
  cout<<setprecision(14)<<fixed<<ans+1.0<<endl;
  return 0 ;
}
