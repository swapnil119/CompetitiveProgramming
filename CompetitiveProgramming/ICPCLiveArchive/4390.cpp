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
const int N=500005;
int mult(int x,int y,int mod)
{
  ll tmp=(ll)x*y;
  tmp%=mod;
  return tmp;
}
int pow1(int x,int y,int mod)
{
  int ans=1;
  while(y)
    {
      if(y&1) ans=mult(ans,x,mod);
      x=mult(x,x,mod);
      y>>=1;
    }
  return ans;
}
vi ad[N];
vector<ii> v;
int f[N],inv[N],child[N],ans;
int calc(int x,int y)
{
  int pw=y,cnt=0;
  while(pw<=x)
    {
      cnt+=x/pw;
      if(pw>x/y) break;
      pw*=y;
    }
  return cnt;
}
int ncr(int x,int y,int m)
{
  int curr=1;
  for(auto it:v)
    {
      int tmp=calc(x,it.fi)-calc(y,it.fi)-calc(x-y,it.fi);
      curr=mult(curr,pow1(it.fi,tmp,m),m);
    }
  curr=mult(curr,f[x],m);
  curr=mult(curr,inv[y],m);
  curr=mult(curr,inv[x-y],m);
  return curr;
}
void dfs(int u,int m)
{
  child[u]=1;
  for(int v1:ad[u])
    {
      dfs(v1,m);
      child[u]+=child[v1];
    }
  int rem=child[u]-1;
  for(int v1:ad[u])
    {
      ans=mult(ans,ncr(rem,child[v1],m),m);
      rem-=child[v1];
    }
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int t;
  cin>>t;
  while(t--)
    {
      ans=1;
      v.clear();
      int n,m,phi=1;
      cin>>n>>m;
      int sq=sqrt(m);
      int tmp=m;
      rep(i,2,sq+1)
	{
	  if(tmp%i) continue;
	  int cnt=0,pw=1;
	  while(tmp%i==0) tmp/=i,cnt++,pw*=i;
	  v.pb(mp(i,cnt));
	  phi*=(pw-pw/i);
	}
      if(tmp!=1) v.pb(mp(tmp,1));
      f[0]=inv[0]=f[1]=inv[1]=1; 
      rep(i,2,n+1)
	{
	  tmp=i;
	  for(auto it:v)
	    while(tmp%it.fi==0) tmp/=it.fi;
	  f[i]=mult(f[i-1],tmp,m);
	  inv[i]=pow1(f[i],phi-1,m);
	}
      rep(i,2,n+1)
	{
	  int x;
	  cin>>x;
	  ad[x].pb(i);
	}
      dfs(1,m);
      rep(i,1,n+1) ad[i].clear();
      cout<<ans<<endl;
    }
  return 0 ;
}
