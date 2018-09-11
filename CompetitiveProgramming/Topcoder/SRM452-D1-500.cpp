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
/*count no. of non IOIs string as they are very less
  a string is non IOI if diff. in pos of Is is same and is odd
  check for each starting pos. and diff.
  no. of possible non IOIstrings are n*summation(n/i) = n^2 logn
*/
const int N=2505,mod=1e9+7;
class IOIString
{
public:
  int preo[N],prei[N];
  int countIOIs(vector<string> mask)
  {
    string curr="";
    for(auto it:mask) curr+=it;
  	preo[0]=(curr[0]=='O'); prei[0]=(curr[0]=='I');
    rep(i,1,sz(curr))
      {
	preo[i]=preo[i-1]+(curr[i]=='O');
	prei[i]=prei[i-1]+(curr[i]=='I');
      }
    int cnt=0;
    if(prei[sz(curr)-1]==0) cnt=1;//all Os
    rep(i,0,sz(curr))
      {
	//no I from 0 to i-1
	if(i && prei[i-1]) break;
	if(curr[i]=='O') continue;
	if(prei[sz(curr)-1]-prei[i]==0) cnt++;
	for(int j=1;j<=sz(curr);j+=2)
	  {
	    for(int k=i+j;k<sz(curr);k+=j)
	      {
		int tmp=prei[k-1]-prei[k-j];
		if(tmp) break;//some I is in b/w k and k-j
		if(curr[k]=='O') break;//here O is present
		if(prei[sz(curr)-1]-prei[k]) continue;//some I after this
		cnt++;
	      }
	  }
      }
    int ans=1;
    int qs=sz(curr)-prei[sz(curr)-1]-preo[sz(curr)-1];
    rep(i,1,qs+1)
      {
	ans+=ans;
	if(ans>=mod) ans-=mod;
      }
    ans-=cnt;
    if(ans<0) ans+=mod;
    return ans;
  }
};
