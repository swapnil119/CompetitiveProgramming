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
vector<ii> v;
//i is in answer if ncr(n-1,i-1)%m=0
int calc(int n,int val)
{
  ll ans=0,pw=val;
  while(n>=pw)
    {
      ans+=n/pw;
      pw*=val;
    }
  return ans;
}
bool check(int n,int r)
{
  bool ok=true;
  for(auto it:v)
    {
      int pw=calc(n,it.fi)-calc(r,it.fi)-calc(n-r,it.fi);
      if(pw<it.se) ok=false;
    }
  return ok;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,m;
  while(cin>>n>>m)
    {
      v.clear();
      int sq=sqrt(m);
      rep(i,2,sq+1)
	{
	  if(m%i) continue;
	  int cnt=0;
	  while(m%i==0) m/=i,cnt++;
	  v.pb(mp(i,cnt));
	}
      if(m!=1) v.pb(mp(m,1));
      vi ans;
      rep(i,1,n+1)
	if(check(n-1,i-1)) ans.pb(i);
      cout<<sz(ans)<<endl;
      for(int x:ans)
	{
	  cout<<x;
	  if(x==ans.back()) cout<<endl;
	  else cout<<" ";
	}
      if(!sz(ans)) cout<<endl;
    }
  return 0 ;
}
