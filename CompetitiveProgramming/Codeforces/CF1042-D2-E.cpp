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
//consider expected val of smallest element as 0, then calculate values from smallest to largest
const int mod=998244353,N=1005;
int a[N][N];
int add(int x,int y)
{
  x+=y;
  if(x>=mod) x-=mod;
  if(x<0) x+=mod;
  return x;
}
int mult(int x,int y)
{
  ll tmp=(ll)x*y;
  if(tmp>=mod) tmp%=mod;
  return tmp;
}
int pow1(int x,int y)
{
  int ans=1;
  while(y)
    {
      if(y&1) ans=mult(ans,x);
      x=mult(x,x);
      y>>=1;
    }
  return ans;
}
map<int,vector<ii> > x;
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,m,mn=INT_MAX;
  cin>>n>>m;
  rep(i,1,n+1)
    rep(j,1,m+1)
    {
      cin>>a[i][j];
      x[a[i][j]].pb(mp(i,j));
      mn=min(mn,a[i][j]);
    }
  int r,c;
  cin>>r>>c;
  if(a[r][c]==mn)
    {
      cout<<0<<endl;
      return 0;
    }
  int cnt=0;
  int sumsq=0,sumi1=0,sumj1=0,sum=0;
  for(auto it:x[mn])
    {
      cnt++;
      int tmp=add(mult(it.fi,it.fi),mult(it.se,it.se));
      sumsq=add(sumsq,tmp);
      sumi1=add(sumi1,-mult(2,it.fi));
      sumj1=add(sumj1,-mult(2,it.se));
    }
  x.erase(x.find(mn));
  for(auto it2:x)
    {
      int tmps=0;
      for(auto it:it2.se)
	{
	  int tmp=add(mult(it.fi,it.fi),mult(it.se,it.se));
	  int curr=mult(cnt,tmp);
	  curr=add(curr,sumsq);
	  curr=add(curr,mult(sumi1,it.fi));
	  curr=add(curr,mult(sumj1,it.se));
	  curr=add(curr,sum);
	  curr=mult(curr,pow1(cnt,mod-2));
	  if(it.fi==r && it.se==c)
	    {
	      cout<<curr<<endl;
	      return 0;
	    }
	  tmps=add(tmps,curr);
	}
      for(auto it:it2.se)
	{
	  cnt++;
	  int tmp=add(mult(it.fi,it.fi),mult(it.se,it.se));
	  sumsq=add(sumsq,tmp);
	  sumi1=add(sumi1,-mult(2,it.fi));
	  sumj1=add(sumj1,-mult(2,it.se));
	}
      sum=add(sum,tmps);
    }
  assert(false);
  return 0 ;
}
