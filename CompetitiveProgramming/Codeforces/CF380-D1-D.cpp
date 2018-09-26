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
const int mod=1e9+7,N=100005;
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
int a[N],pre[N],f[N],inv[N],pw[N];
int ncr(int x,int y)
{
  return mult(f[x],mult(inv[x-y],inv[y]));
}
int fun(int l,int r)
{
  assert(l<=r);
  if(pre[r]==pre[l-1]) return pw[r-l];
  int st=-1,en=-1;
  rep(i,l,r+1)
    if(a[i]) { st=i; break; }
  repv(i,l,r+1)
    if(a[i]) { en=i; break; }
  if(st==en && a[st]==1)
    return ncr(st-l+r-en,r-en);
  int ans=0;
  if(a[st]>=a[en])
    {
      int l1=st+1,r1=st+a[st]-1;
      if(r1>=en && r1<=r) ans=add(ans,mult(fun(l1,r1),ncr(st-l+r-r1,r-r1)));
    }
  if(a[st]<=a[en])
    {
      int l1=en-a[en]+1,r1=en-1;
      if(l1>=l && l1<=st) ans=add(ans,mult(fun(l1,r1),ncr(l1-l+r-en,l1-l)));
    }
  return ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  f[0]=inv[0]=pw[0]=1;
  rep(i,1,N) pw[i]=mult(pw[i-1],2);
  rep(i,1,N) f[i]=mult(f[i-1],i);
  inv[N-1]=pow1(f[N-1],mod-2);
  repv(i,1,N-1) inv[i]=mult(inv[i+1],i+1);
  int n;
  cin>>n;
  rep(i,1,n+1) cin>>a[i],pre[i]=pre[i-1]+(a[i]!=0);
  cout<<fun(1,n)<<endl;
  return 0 ;
}
