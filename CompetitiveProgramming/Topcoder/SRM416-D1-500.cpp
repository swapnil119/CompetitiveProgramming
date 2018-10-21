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
const int mod=(1e9+7);
const int N=100005;
class CustomDice
{
  int dp[2][6*N];
public:
  int countDice(int m)
  {
    m*=6;
    m-=21;
    if(m<0) return 0;
    int ans=0;
    rep(i,0,m+1) dp[0][i]=1;
    rep(i,1,7)
      {
	int bit=(i&1);
	rep(j,0,m+1)
	  {
	    dp[bit][j]=dp[1-bit][j];
	    if(j>=i) dp[bit][j]+=dp[bit][j-i];
	    dp[bit][j]%=mod;
	  }
      }
    ll ret=(ll)dp[0][m]*30;
    ret%=mod;
    return ret;
  }
};
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  CustomDice x;
  int m; cin>>m;
  cout<<x.countDice(m)<<endl;
  return 0 ;
}
