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
map<int,vi> m;
map<int,bool> done;
int nim[30] = {0, 1, 2, 1, 4, 3, 2, 1, 5, 6, 2, 1, 8, 7, 5, 9, 8, 7, 3, 4, 7, 4, 2, 1, 10, 9, 3, 6, 11, 12};
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n;
  cin>>n;
  int sq=sqrt(n);
  int cnt=0;
  rep(i,2,sq+1)
    {
      if(done.count(i)) continue;
      for(int pw=i;pw<=n;pw*=i)
	{
	  m[i].pb(pw),cnt++,done[pw];
	  if(pw>n/i) break;
	}
    }
  int rem=n-cnt;
  int grundy=0;
  for(auto it:m)
    {
      int sz=sz(it.se);
      grundy^=nim[sz];
    }
  if(rem&1) grundy^=1;
  if(grundy) cout<<"Vasya"<<endl;
  else cout<<"Petya"<<endl;
  return 0 ;
}
