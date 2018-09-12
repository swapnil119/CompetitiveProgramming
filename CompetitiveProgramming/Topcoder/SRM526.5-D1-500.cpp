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
//http://apps.topcoder.com/wiki/display/tc/SRM+526.5
/* Approach 1
Throw snowballs one by one and in inc. order of range
Suppose i balls are already thrown. Now we need to throw (i+1)th ball
When we add new ball beauty is increased by (x+1)^2 - x^2 = 2*x+1
So find expected value of x
x is i/(2R+1)^2 , suppose all balls earlier had range x, so x is 
(i/(2r+1)^2)*(2r+1)^2/(2R+1)^2 = i/(2R+1)^2*/
class MagicBlizzard
{
public:
  db expectation(vi range,vi amount)
  {
    int n=sz(range);
    db ans=0.0;
    vi ind(n);
    rep(i,0,n) ind[i]=i;
    sort(all(ind),[&](int i,int j) {return range[i]<range[j];});
    int cnt=0;
    rep(i,0,n)
      {
	rep(j,0,amount[ind[i]])
	  ans+=2.0*(cnt++)/((2.0*range[ind[i]]+1.0)*(2.0*range[ind[i]]+1.0))+1.0;
      }
    return ans;
  }
};
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  vi range,amount;
  range.pb(1); range.pb(0);
  amount.pb(2); amount.pb(1);
  MagicBlizzard d;
  cout<<setprecision(10)<<fixed;
  cout<<d.expectation(range,amount)<<endl;
  return 0 ;
}
