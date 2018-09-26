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
const int N=200005,mod=1e9+7;
int f[N],inv[N];
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
vector<ii> v;
int ans[N];
int fun(int x1,int y1,int x2,int y2)
{
  int x=x2-x1,y=y2-y1;
  int tmp=mult(inv[x],inv[y]);
  return mult(tmp,f[x+y]);
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  f[0]=inv[0]=1;
  rep(i,1,N) f[i]=mult(f[i-1],i);
  inv[N-1]=pow1(f[N-1],mod-2);
  repv(i,1,N-1)
    {
      inv[i]=mult(inv[i+1],i+1);
      assert(mult(inv[i],f[i])==1);
    }
  int h,w,n;
  cin>>h>>w>>n;
  rep(i,1,n+1)
    {
      int x,y;
      cin>>x>>y;
      v.pb(mp(x,y));
    }
  v.pb(mp(h,w));
  sort(all(v));
  rep(i,0,sz(v))
    ans[i]=fun(1,1,v[i].fi,v[i].se);
  rep(i,0,sz(v)-1)
    rep(j,i+1,sz(v))
    {
      if(v[j].se<v[i].se) continue;
      ans[j]=add(ans[j],-mult(ans[i],fun(v[i].fi,v[i].se,v[j].fi,v[j].se)));
    }
  cout<<ans[sz(v)-1]<<endl;
  return 0 ;
}
