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
//use alien's trick, direct dp
const int N=200005,LN=20;
const ll inf=(ll)1e15;
int a[N],val[LN][N],logs[N];
vector<ii> arr[N];
ll dp[N];
int cnt[N],n;
int query(int l,int r)
{
  int ln=logs[r-l+1];
  return (val[ln][l]|val[ln][r-(1<<ln)+1]);
}
int fun(ll val)
{
  dp[0]=cnt[0]=0;
  rep(i,1,n+1)
    {
      dp[i]=-inf;
      for(auto it:arr[i])
	{
	  if(dp[it.fi-1]+it.se-val>dp[i])
	    dp[i]=dp[it.fi-1]+it.se-val,cnt[i]=cnt[it.fi-1]+1;
	  else if(dp[it.fi-1]+it.se-val==dp[i])
	    cnt[i]=max(cnt[i],cnt[it.fi-1]+1);
	}
      if(query(1,i)-val>dp[i])
	dp[i]=query(1,i)-val,cnt[i]=1;
      else if(query(1,i)-val==dp[i])
	cnt[i]=max(cnt[i],1);
    }
  return cnt[n];
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  rep(i,1,N) logs[i]=(int)log2(i);
  int k;
  cin>>n>>k;
  rep(i,1,n+1) cin>>a[i],val[0][i]=a[i];
  for(int i=1;(1<<i)<=n;i++)
    for(int j=1;(j+(1<<i)-1)<=n;j++)
      val[i][j]=(val[i-1][j]|val[i-1][j+(1<<(i-1))]);
  rep(i,1,n+1)
    {
      int curr=i;
      while(curr>=1)
	{
	  int low=1,high=curr;
	  int tmp=query(curr,i);
	  while(low<high)
	    {
	      int mid=(low+high)>>1;
	      if(query(mid,i)==tmp) high=mid;
	      else low=mid+1;
	    }
	  arr[i].pb(mp(curr,tmp));
	  curr=low-1;
	}
      reverse(all(arr[i]));
    }
  ll low=0,high=1e9;
  while(low<high)
    {
      ll mid=(low+high+1)>>1;
      if(fun(mid)>=k) low=mid;
      else high=mid-1;
    }
  fun(high);
  cout<<dp[n]+high*k<<endl;
  return 0 ;
}
