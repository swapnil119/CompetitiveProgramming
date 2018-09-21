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
const int N=35,K=205;
bool vis[N][N][K];
db dp[N][N][K];//prob. that smaller is at pos. i, large at j, and k rounds and smaller will be after larger
int p[N],n;
db fun(int i,int j,int k)
{
  if(k==0) return ((i>j)?1.0:0.0);
  if(vis[i][j][k]) return dp[i][j][k];
  vis[i][j][k]=true;
  db tot=n*(n-1); tot/=2.0; tot+=n;
  db ans=0.0;
  rep(i1,1,n+1)
    rep(j1,i1,n+1)
    {
      if(i<j)
	{
	  if(i1<=i)
	    {
	      if(j1<i) ans+=fun(i,j,k-1);
	      else if(j1<j) ans+=fun(j1-i+i1,j,k-1);
	      else ans+=fun(j1-i+i1,j1-j+i1,k-1);
	    }
	  else if(i1<=j)
	    {
	      if(j1<j) ans+=fun(i,j,k-1);
	      else ans+=fun(i,j1-j+i1,k-1);
	    }
	  else
	    ans+=fun(i,j,k-1);
	}
      else
	{
	  if(i1<=j)
	    {
	      if(j1<j) ans+=fun(i,j,k-1);
	      else if(j1<i) ans+=fun(i,j1-j+i1,k-1);
	      else ans+=fun(j1-i+i1,j1-j+i1,k-1);
	    }
	  else if(i1<=i)
	    {
	      if(j1<i) ans+=fun(i,j,k-1);
	      else ans+=fun(j1-i+i1,j,k-1);
	    }
	  else
	    ans+=fun(i,j,k-1);
	}
    }
  ans/=tot;
  return dp[i][j][k]=ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int k;
  cin>>n>>k;
  rep(i,1,n+1) cin>>p[i];
  db ans=0.0;
  rep(i,1,n+1)
    rep(j,i+1,n+1)
    {
      if(p[i]<p[j]) ans+=fun(i,j,k);
      else ans+=fun(j,i,k);
    }
  cout<<setprecision(10)<<fixed<<ans<<endl;
  return 0 ;
}
