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
/*represent k%i as k-(k/i)*i then iterate values of k/i*/
ll calc(ll l,ll r)
{
  return (r*(r+1)-l*(l-1))/2;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,k;
  while(cin>>n>>k)
    {
      int sq=sqrt(k);
      ll ans=(ll)k*n;
      rep(i,1,min(n,sq)+1)
	ans-=(ll)(k/i)*i;
      if(sq>=n)
	{
	  cout<<ans<<endl;
	  continue;
	}
      rep(i,1,sq+1)
	{
	  int l=k/(i+1)+1,r=k/i;
	  l=max(l,sq+1);
	  r=min(r,n);
	  if(l>r) continue;
	  ans-=(ll)i*calc(l,r);
	}
      cout<<ans<<endl;
    }
  return 0 ;
}
