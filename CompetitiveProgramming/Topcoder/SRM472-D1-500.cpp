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

/*make a graph where vertex are numbers and edges are cards, now graph is a set of cycles, with each node as part of only one cycle.
  start placing cycles. let cycle(n) be answer for one cycle
cycle(n)=summation f(n,i) where i is number of elements occuring twice i<=n/2
To calculate f(n,k)
if x appears t times, write t in vertex x
0 and 2 appear alternatinvely. ways to write k zeroes, k twos and (n-2*k ones) is ncr(n,2k) * (k==0?1:2) .
Number of ways to arrange them is n!/(2!)^k
*/
class TwoSidedCards
{
  int f[N],inv[N],pw[N],invpw[N];
  bool vis[N];
  vi v[N];
public:
    const int mod=1e9+7,N=105;
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
  void dfs(int u,int &cnt)
  {
    if(vis[u]) return;
    cnt++; vis[u]=true;
    for(int v1:v[u]) dfs(v1,cnt);
  }
  int ncr(int n,int k)
  {
    if(k<0 || n<k) return 0;
    return mult(f[n],mult(inv[k],inv[n-k]));
  }
  int theCount(vi taro,vi hanako)
  {
    f[0]=inv[0]=pw[0]=invpw[0]=1;
    rep(i,1,N) f[i]=mult(f[i-1],i),pw[i]=mult(pw[i-1],2);
    inv[N-1]=pow1(f[N-1],mod-2);
    invpw[N-1]=pow1(pw[N-1],mod-2);
    repv(i,1,N-1) inv[i]=mult(inv[i+1],i+1),invpw[i]=mult(invpw[i+1],2);
    int n=sz(taro);
    memset(vis,false,sizeof(vis));
    rep(i,0,n)
      {
	v[taro[i]].pb(hanako[i]);
	v[hanako[i]].pb(taro[i]);
      }
    int rem=n,ans=1;
    rep(i,1,n+1)
      {
	if(vis[i]) continue;
	int cnt=0;
	dfs(i,cnt);
	//select cnt places from remaining places
	int tmp=ncr(rem,cnt),sum=0;
	rep(j,0,cnt/2+1)
	  {
	    //select them by assigning 0,1,2
	    int tmp2=ncr(cnt,2*j);
	    if(j) tmp2=mult(tmp2,2);
	    //arrange them
	    tmp2=mult(tmp2,f[cnt]);
	    tmp2=mult(tmp2,invpw[j]);
	    sum=add(sum,tmp2);
	  }
	ans=mult(ans,mult(sum,tmp));
	rem-=cnt;
      }
    return ans;
  }
};
