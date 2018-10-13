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
//keep state of previous row, but number of states for previous row will be equal to O(2^12) as it will have state corresponding to last to last row. And then at current row, try all possibilities. Hence complexity would be O(r*2^(3*c))
map<vi,int> dp[7][10];
int r,c;
int fun(int row,vi &pre,int m)
{
  if(dp[row][m].count(pre)) return dp[row][m][pre];
  int ans=-1000;
  vi tmp2;
  rep(i,0,(1<<c))
    {
      vi tmp(c,0);
      rep(j,0,c)
	if(!(i&(1<<j)))
	  tmp[j]=-1;
      rep(j,0,c)
	{
	  if(tmp[j]<0) continue;
	  int cnt=0;
	  if(j) cnt+=(tmp[j-1]<0);
	  if(j<c-1) cnt+=(tmp[j+1]<0);
	  tmp[j]=cnt;
	}
      bool ok=true;
      rep(j,0,c)
	{
	  if(pre[j]<0)//for mines
	    {
	      int cnt=-pre[j]-1;
	      if(j) cnt+=(tmp[j-1]>=0);
	      if(j<c-1) cnt+=(tmp[j+1]>=0);
	      cnt+=(tmp[j]>=0);
	      if(!cnt) ok=false;
	      continue;
	    }//for normal
	  int cnt=pre[j];
	  if(j) cnt+=(tmp[j-1]<0);
	  if(j<c-1) cnt+=(tmp[j+1]<0);
	  cnt+=(tmp[j]<0);
	  if(cnt>m) ok=false;
	}
      rep(j,0,c)
	{
	  if(tmp[j]<0)
	    {
	      int cnt=0;
	      if(j) 
		{
		  cnt+=(tmp[j-1]>=0);
		  cnt+=(pre[j-1]>=0);
		}
	      cnt+=(pre[j]>=0);
	      if(j<c-1)
		{
		  cnt+=(tmp[j+1]>=0);
		  cnt+=(pre[j+1]>=0);
		}
	      tmp[j]=-cnt-1;
	      continue;
	    }
	  int cnt=tmp[j];
	  if(j) cnt+=(pre[j-1]<0);
	  if(j<c-1) cnt+=(pre[j+1]<0);
	  cnt+=(pre[j]<0);
	  tmp[j]=cnt;
	  if(cnt>m) ok=false;
	}
      if(!ok) continue;
      if(row==r)
	{
	  rep(i,0,c)
	    if(tmp[i]==-1) ok=false;
	  if(!ok) continue;
	  ans=max(ans,c-__builtin_popcount(i));
	  continue;
	}
      ans=max(ans,fun(row+1,tmp,m)+c-__builtin_popcount(i));
    }
  return dp[row][m][pre]=ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int t;
  cin>>t;
  while(t--)
    {
      rep(i,0,7)
	rep(j,0,10) dp[i][j].clear();
      int m;
      cin>>r>>c>>m;
      int ans=0;
      rep(i,0,(1<<c))
	{
	  vi tmp(c,0);
	  rep(j,0,c)
	    if(!(i&(1<<j)))
	      tmp[j]=-1;
	  rep(j,0,c)
	    {
	      int cnt=0;
	      if(tmp[j]<0)
		{
		  if(j) cnt+=(tmp[j-1]>=0);
		  if(j<c-1) cnt+=(tmp[j+1]>=0);
		  tmp[j]=-cnt-1;
		  continue;
		}
	      if(j) cnt+=(tmp[j-1]<0);
	      if(j<c-1) cnt+=(tmp[j+1]<0);
	      tmp[j]=cnt;
	    }
	  if(r==1)
	    {
	      bool ok=true;
	      rep(j,0,c)
		if(tmp[j]>m || tmp[j]==-1) ok=false;
	      if(ok) ans=max(ans,c-__builtin_popcount(i));
	      continue;
	    }
	  ans=max(ans,fun(2,tmp,m)+c-__builtin_popcount(i));
	}
      cout<<ans<<endl;
    }
  return 0 ;
}
