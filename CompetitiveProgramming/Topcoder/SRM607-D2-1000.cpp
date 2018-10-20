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
//http://apps.topcoder.com/wiki/display/tc/SRM+607?showComments=true#comments
const int N=55;
class CombinationLockDiv2
{
  int a[N],dp[N][N][2];
public:
  int fun(int ind,int num,bool up,int n)
  {
    if(ind==n) return 0;
    if(dp[ind][num][up]!=-1) return dp[ind][num][up];
    int ans=9*N;
    rep(i,0,2)
      rep(j,0,9*n)
      {
	if(i==0)//down
	  {
	    if((a[ind]+9*j)%10) continue;
	  }
	else
	  {
	    if((a[ind]+j)%10) continue;
	  }
	if(i==up)
	  ans=min(ans,max(0,j-num)+fun(ind+1,j,i,n));
	else
	  ans=min(ans,j+fun(ind+1,j,i,n));
      }
    return dp[ind][num][up]=ans;
  }
  int minimumMoves(string s,string t)
  {
    rep(i,0,sz(s))
      {
	a[i]=(int)((int)s[i]-(int)t[i]);
	a[i]%=10;
	if(a[i]<0) a[i]+=10;
      }
    memset(dp,-1,sizeof(dp));
    return fun(0,0,0,sz(s));
  }
};
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  CombinationLockDiv2 x;
  string s1,s2;
  cin>>s1>>s2;
  cout<<x.minimumMoves(s1,s2)<<endl;
  return 0 ;
}
