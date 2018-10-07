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
vi p;
int l,r,k;
ll ans;
void fun(int ind,int prod,int cnt)
{
  if(ind==sz(p))
    {
      if(cnt)
	{
	  if(cnt&1) ans+=r/prod-(l-1)/prod;
	  else ans-=r/prod-(l-1)/prod;
	  if(cnt==1 && l<=prod && r>=prod) ans--;
	}
      return;
    }
  if(prod<=r/p[ind])
    {
      fun(ind+1,prod*p[ind],cnt+1);
      fun(ind+1,prod,cnt);
    }
  else
    {
      if(cnt)
	{
	  if(cnt&1) ans+=r/prod-(l-1)/prod;
	  else ans-=r/prod-(l-1)/prod;
	  if(cnt==1 && l<=prod && r>=prod) ans--;
	}
      return;
    }
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  cin>>l>>r>>k;
  r+=l; l++;
  rep(i,2,k+2)
    {
      int sq=sqrt(i);
      bool ok=true;
      rep(j,2,sq+1)
	if(i%j==0) ok=false;
      if(ok) p.pb(i);
    }
  fun(0,1,0);
  ans=r-l+1-ans;
  cout<<ans<<endl;
  return 0 ;
}
