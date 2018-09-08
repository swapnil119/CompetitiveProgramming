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
const int N=2005;
bitset<N> dp[N],dp2[N];
string s;
string solve(int l,int r)
{
  if(r==l+1) return "()";
  repv(i,l+1,r+1)
    {
      if(s[l]!=s[i]) continue;
      if(i==r)
	{
	  if(dp[l+1].test(r-1))
	    {
	      string ans="(";
	      ans+=solve(l+1,r-1);
	      ans+=")";
	      return ans;
	    }
	}
      else if(i==l+1)
	{
	  if(dp[l+2].test(r))
	    {
	      string ans="()";
	      ans+=solve(l+2,r);
	      return ans;
	    }
	}
      else if(dp[l+1].test(i-1) && dp[i+1].test(r))
	{
	  string ans="(";
	  ans+=solve(l+1,i-1);
	  ans+=")";
	  ans+=solve(i+1,r);
	  return ans;
	}
    }
  assert(false);
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  cin>>s;
  int n=sz(s);
  s="#"+s;
  rep(i,1,n)
    if(s[i]==s[i+1]) dp[i].set(i+1),dp2[i+1].set(i-1);
  rep(i,3,n+1)
    {
      rep(j,1,n-i+2)
	{
	  int l=j,r=j+i-1;
	  if(dp[l+1].test(r-1) && s[l]==s[r])
	    {
	      dp[l].set(r); dp2[r].set(l-1);
	      continue;
	    }
	  if((dp[l]&dp2[r]).count())
	    dp[l].set(r),dp2[r].set(l-1);
	}
    }
  if(!dp[1].test(n))
    {
      cout<<-1<<endl;
      return 0;
    }
  cout<<solve(1,n)<<endl;
  return 0 ;
}
