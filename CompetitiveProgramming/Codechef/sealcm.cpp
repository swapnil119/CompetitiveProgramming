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
const int mod=1e9+7,N=16;
struct matrix
{
  int a[N][N];
  matrix()
  {
    rep(i,0,N) rep(j,0,N) a[i][j]=0;
  }
  matrix(int n)
  {
    rep(i,0,N) rep(j,0,N) a[i][j]=0;
    rep(i,0,n) a[i][i]=1;
  }
};
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
matrix multmat(matrix a,matrix b,int sz)
{
  matrix c;
  rep(k,0,sz)
    rep(i,0,sz)
    rep(j,0,sz)
    c.a[i][j]=add(c.a[i][j],mult(a.a[i][k],b.a[k][j]));
  return c;
}
matrix powmat(matrix a,int n,int sz)
{
  matrix ans(sz);
  while(n)
    {
      if(n&1) ans=multmat(ans,a,sz);
      a=multmat(a,a,sz);
      n>>=1;
    }
  return ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,m,t,l,r;
  cin>>t;
  while(t--)
    {
      cin>>n>>m>>l>>r;
      int ans=0;
      rep(i,l,r+1)
	{
	  if(i==1)
	    {
	      ans=add(ans,pow1(m,n));
	      continue;
	    }
	  int sq=sqrt(i),tmp=i;
	  vector<ii> v;
	  rep(j,2,sq+1)
	    {
	      if(tmp%j) continue;
	      int cnt=0;
	      while(tmp%j==0) tmp/=j,cnt++;
	      v.pb(mp(j,cnt));
	    }
	  if(tmp!=1) v.pb(mp(tmp,1));
	  assert(sz(v)<=4);
	  const int sz=sz(v);
	  matrix a;
	  int x[(1<<sz)];
	  rep(i,0,(1<<sz))
	    {
	      rep(j,1,m+1)
		{
		  int mask=i,ind=0;
		  for(auto it:v)
		    {
		      int tmp=j,cnt=0;
		      while(tmp%it.fi==0) tmp/=it.fi,cnt++;
		      if(cnt>=it.se) mask|=(1<<ind);
		      ind++;
		    }
		  a.a[i][mask]++;
		}
	    }
	  rep(i,0,(1<<sz)) x[i]=0;
	  rep(i,1,m+1)
	    {
	      int mask=0,ind=0;
	      for(auto it:v)
		{
		  int tmp=i,cnt=0;
		  while(tmp%it.fi==0) tmp/=it.fi,cnt++;
		  if(cnt>=it.se) mask|=(1<<ind);
		  ind++;
		}
	      x[mask]++;
	    }
	  a=powmat(a,n-1,(1<<sz));
	  rep(i,0,(1<<sz))
	    ans=add(ans,mult(x[i],a.a[i][(1<<sz)-1]));
	}
      cout<<ans<<endl;
    }
  return 0 ;
}
