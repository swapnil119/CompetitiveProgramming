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
const int mod=1e9+7,N=605;
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
int ncr(int x,int y)
{
  if(y>x || y<0) return 0;
  return mult(f[x],mult(inv[y],inv[x-y]));
}
bool done[N];
vi v[N];
int a[N],dp[N][N];//dp is number of elements done, no. of bad pairs
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
      assert(mult(f[i],inv[i])==1);
    }
  int cnt=0;
  int n;
  cin>>n;
  rep(i,1,n+1) cin>>a[i];
  rep(i,1,n+1)
    {
      if(done[i]) continue;
      cnt++;
      v[cnt].pb(i);
      rep(j,i+1,n+1)
	{
	  ll tmp=(ll)a[i]*a[j];
	  ll sq=sqrt(tmp);
	  if(sq*sq==tmp)
	    {
	      assert(done[j]==false);
	      done[j]=true;
	      v[cnt].pb(j);
	    }
	}
    }
  dp[0][0]=1;
  int sum=0;
  rep(i,1,cnt+1)
    {
      const int sz=sz(v[i]);
      rep(j,0,sum+1)//no. of bad pairs prev.
	{
	  rep(k,1,min(sz,sum+1)+1)//no. of partition of this group
	    rep(l,0,min(j,k)+1)//eliminate these many pairs
	    {
	      int nxt=j-l+sz-k;
	      int tmp=mult(ncr(sz-1,k-1),mult(ncr(j,l),ncr(sum+1-j,k-l)));
	      tmp=mult(tmp,f[sz]);
	      dp[i][nxt]=add(dp[i][nxt],mult(dp[i-1][j],tmp));
	    }
	}
      sum+=sz;
    }
  cout<<dp[cnt][0]<<endl;
  return 0 ;
}
