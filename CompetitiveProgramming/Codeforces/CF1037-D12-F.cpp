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
const int N=1000005,mod=1e9+7;
int a[N],l[N],r[N];
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
int calc(int len,int k)
{
  //for length i, answer is len-i+1
  //lengths are 1+i*(k-1)
  //answer for ith is len-i*(k-1)
  int lim=len/(k-1);
  ll tmp=(ll)lim*(ll)(lim+1);
  tmp>>=1; tmp%=mod;
  return add(mult(lim,len),-mult(k-1,tmp));
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,k;
  cin>>n>>k;
  rep(i,1,n+1)
    cin>>a[i];
  stack<int> s;
  rep(i,1,n+1)
    {
      while(!s.empty() && a[s.top()]<=a[i]) s.pop();
      l[i]=((s.empty())?1:(s.top()+1));
      s.push(i);
    }
  while(!s.empty()) s.pop();
  repv(i,1,n+1)
    {
      while(!s.empty() && a[s.top()]<a[i]) s.pop();
      r[i]=((s.empty())?n:(s.top()-1));
      s.push(i);
    }
  /* for each i calculate how many intervals in [l[i],r[i]] contain i*/
  int ans=0;
  rep(i,1,n+1)
    {
      int curr=add(calc(r[i]-l[i]+1,k),-calc(i-l[i],k));
      curr=add(curr,-calc(r[i]-i,k));
      ans=add(ans,mult(curr,a[i]));
    }
  cout<<ans<<endl;
  return 0 ;
}
