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
const int X=50005;
const int N=(1<<16),N1=(1<<8),L=8;
int a[X],b[X],c[X];
ll dp[N1][N1][L+1],a1[X],a2[X];
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n;
  cin>>n;
  rep(i,1,n+1) cin>>a[i];
  rep(i,1,n+1) cin>>b[i];
  rep(i,1,n+1) cin>>c[i];
  //first calculate no. of pairs j,i such that (a[i]&a[j])=b[j]
  rep(i,1,n+1)
    {
      int fh=(a[i]&(N1-1));
      int sh=(a[i]>>8);
      rep(j,0,N1)
	{
	  int tmp=(fh&j),tmp2=__builtin_popcount(tmp);
	  if(tmp2>b[i] || b[i]-tmp2>8) continue;
	  a1[i]+=dp[j][sh][b[i]-tmp2];
	}
      rep(j,0,N1)
	{
	  int tmp=(sh&j);
	  dp[fh][j][__builtin_popcount(tmp)]++;
	}
    }
  //now calculate no. of pairs j,k such that (a[j]&a[k])=c[k]
  memset(dp,0,sizeof(dp));
  rep(i,1,n+1)
    {
      int fh=(a[i]&(N1-1));
      int sh=(a[i]>>8);
      rep(j,0,N1)
	{
	  int tmp=(fh|j),tmp2=__builtin_popcount(tmp);
	  if(tmp2>c[i] || c[i]-tmp2>8) continue;
	  a2[i]+=dp[j][sh][c[i]-tmp2];
	}
      rep(j,0,N1)
	{
	  int tmp=(sh|j);
	  dp[fh][j][__builtin_popcount(tmp)]+=a1[i];
	}
    }
  //now calculate no. of pairs k,l such that (a[k]&a[l])=b[l]
  ll ans=0;
  memset(dp,0,sizeof(dp));
  rep(i,1,n+1)
    {
      int fh=(a[i]&(N1-1));
      int sh=(a[i]>>8);
      rep(j,0,N1)
	{
	  int tmp=(fh&j),tmp2=__builtin_popcount(tmp);
	  if(tmp2>b[i] || b[i]-tmp2>8) continue;
	  ans+=dp[j][sh][b[i]-tmp2];
	}
      rep(j,0,N1)
	{
	  int tmp=(sh&j);
	  dp[fh][j][__builtin_popcount(tmp)]+=a2[i];
	}
    }
  cout<<ans<<endl;
  return 0 ;
}
