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
/* answer is sum of floor(n/i), there are O(sqrt(n)) distinct values of n/i. First iterate till i=1 to sqrt(n). Then iterate over value of n/i from 1 to sqrt(n) */
ll calc(ll l,ll r)
{
  return (r*(r+1)-l*(l-1))/2;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n;
  while(cin>>n)
    {
      if(!n) break;
      int sq=sqrt(n);
      ll ans=0;
      rep(i,1,sq+1)
	{
	  ans+=(ll)(n/i)*i;
	  if(i==1) ans--;
	}
      rep(i,1,sq+1)
	{
	  ll l=1+n/(i+1),r=n/i;
	  l=max(l,(ll)sq+1);
	  if(l>r) continue;
	  ans+=calc(l,r)*i;
	}
      cout<<ans<<endl;
    }
  return 0 ;
}
