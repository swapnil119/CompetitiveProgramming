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
//make states as dp(i,j,k) where i is whether face was up or down, j is you have reached l[j], and k is you have made k value of face down, now n^2*k is trivial, use segment tree to make it nklogn, as range of minimum is contiguous
const int K=105,N=100005,inf=1e9;
int l[K],r[K];
int n,k;
int dp[2][2][2*N],seg[2][2*2*N];
#define lc (pos)+(pos)
#define rc (lc)|1
void update(int ind,int val,int id)
{
  for(seg[id][ind+=(2*n+1)]=val; ind>1;ind>>=1)
    seg[id][ind>>1]=min(seg[id][ind],seg[id][ind^1]);
}
int query(int l,int r,int id)
{
  r++;
  int ans=inf;
  for(l+=(2*n+1),r+=(2*n+1);l<r;l>>=1,r>>=1)
    {
      if(l&1) ans=min(ans,seg[id][l++]);
      if(r&1) ans=min(ans,seg[id][--r]);
    }
  return ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  cin>>n>>k;
  rep(i,1,k+1)
    cin>>l[i]>>r[i];
  l[k+1]=2*n;
  rep(i,0,2)
    rep(j,0,2)
    rep(x,0,N) dp[i][j][x]=inf;
  dp[0][1][l[1]]=0;
  rep(i,0,4*N) seg[0][i]=seg[1][i]=inf;
  rep(j,0,2)
    rep(i,0,2*n+1) update(i,dp[j][1][i],j);
  rep(i,2,k+2)
    {
      int bit=(i&1);
      //no flips in previous range
      rep(j,0,2)
	rep(x,0,2*n+1)
	{
	  if(j) dp[j][bit][x]=dp[j][1-bit][x];
	  else if(x>=l[i]-l[i-1]) dp[j][bit][x]=dp[j][1-bit][x-(l[i]-l[i-1])];
	}
      //one flip in previous range
      rep(x,0,2*n+1)
	{
	  int low=max(0,x-(r[i-1]-l[i-1])),high=x;
	  dp[1][bit][x]=min(dp[1][bit][x],1+query(low,high,0));
	  low=max(0,x-(l[i]-l[i-1])),high=x-(l[i]-r[i-1]);
	  dp[0][bit][x]=min(dp[0][bit][x],1+query(low,high,1));
	}
      //two flips in previous range
      rep(x,0,2*n+1)
	{
	  int low=max(0,x-(r[i-1]-l[i-1]+l[i]-r[i-1])),high=x-(l[i]-r[i-1]);
	  dp[0][bit][x]=min(dp[0][bit][x],2+query(low,high,0));
	  low=max(0,x-(r[i-1]-l[i-1])),high=x;
	  dp[1][bit][x]=min(dp[1][bit][x],2+query(low,high,1));
	}
      rep(j,0,4*N) seg[0][j]=seg[1][j]=inf;
      rep(j,0,2)
	rep(x,0,2*n+1)
	update(x,dp[j][bit][x],j);
      rep(j,0,2*n+1) dp[0][1-bit][j]=dp[1][1-bit][j]=inf;
    }
  int ans=min(dp[0][(k+1)&1][n],dp[1][(k+1)&1][n]);
  if(ans>=inf)
    {
      cout<<"Hungry"<<endl;
      return 0;
    }
  cout<<"Full"<<endl<<ans<<endl;
  return 0 ;
}
