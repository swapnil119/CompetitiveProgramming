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
/*Linearity of Expectation.
Count when each number will occur as max. in loop.
for element x, it will be summation ((n-x)! * (x-1)! * f(x) )/ (n!)
f(x) is placing x-1 elements if elements from x+1 to n occur after x. so now there are n-x+2 places and x-1 elements to fill. This can be done using integral solution. x1+x2+x3+..+xr=k, no. of ways = ncr(k+r-1,r-1)
f(x)=ncr(n,i-1)
Hence answer for x is 1/(n-x+1)*/
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int t,n;
  cin>>t;
  while(t--)
    {
      int n;
      cin>>n;
      db ans=0.0;
      rep(i,1,n+1) ans+=1.0/(db)(n-i+1);
      cout<<setprecision(10)<<fixed<<ans<<endl;
    }
  return 0 ;
}
