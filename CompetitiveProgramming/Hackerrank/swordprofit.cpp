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
const ll is_query = -(1LL<<62); //maxhull
struct convex_line { ll m,b;
  mutable function<const convex_line*()> succ;
  bool operator<(const convex_line& rhs) const {
    if(rhs.b!=is_query) return m < rhs.m;
    const convex_line* s=succ(); if(s==NULL) return 0;
    ll x=rhs.m; return 1.0*(b-s->b)<1.0*(s->m-m)*x;
  }
};//declare variable of dcht struct
struct dcht : public multiset<convex_line> {
  bool invalid(iterator y) { auto z=next(y);
    if(y==begin()) {
      if (z==end()) return 0; return y->m==z->m && y->b<=z->b;
    } auto x=prev(y);
    if(z==end()) return y->m==x->m && y->b<=x->b;
    return 1.0*(x->b-y->b)*(z->m-y->m)>=1.0*(y->b-z->b)*(y->m-x->m);
  }void insert_line(ll m,ll b) {//insert any line
    auto y = insert({m,b});
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (invalid(y)) { erase(y); return; }
    while (next(y) != end() && invalid(next(y))) erase(next(y));
    while (y != begin() && invalid(prev(y))) erase(prev(y));
  } void remove_line(ll m,ll b) {//erase line if possible
    auto y=find({m,b}); if(y==end()) return; erase(y);
  } ll eval(ll x) {//call eval to find value at any x
    auto l=lower_bound({x, is_query});return (*l).m * x + (*l).b;
  }
};
const int N=300005,mod=1e9+7;
ll a[N],b[N],r[N],d[N],q[N],mxsp[N];
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
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n;
  cin>>n;
  dcht dp;
  rep(i,1,n+1) cin>>q[i]>>a[i]>>b[i]>>r[i]>>d[i];
  repv(i,1,n+1)
    {
      dp.insert_line(-i,-r[i]);
      mxsp[i]=max((ll)0,q[i]+d[i]*i+dp.eval(d[i]));
    }
  ll ans=0;
  const int den=pow1(2,mod-2);
  rep(i,1,n+1)
    {
      ll lim=(mxsp[i]-a[i])/b[i];
      lim=max(lim,(ll)0);
      mxsp[i]%=mod; lim%=mod;
      ans=add(ans,mult(lim,mxsp[i]));
      ans=add(ans,-mult(a[i],lim));
      int tmp=mult(lim,(lim+1)%mod);
      tmp=mult(tmp,den);
      ans=add(ans,-mult(tmp,b[i]));
    }
  cout<<ans<<endl;
  return 0 ;
}
