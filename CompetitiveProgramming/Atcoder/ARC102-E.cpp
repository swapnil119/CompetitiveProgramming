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
const int N=8005,mod=998244353;
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
int ncr[N][N],pw[N];
int calc(int n,int r)
{
  return ncr[n+r-1][r-1];
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  rep(i,0,N) ncr[i][0]=1;
  rep(i,1,N)
    rep(j,1,i+1)
    ncr[i][j]=add(ncr[i-1][j],ncr[i-1][j-1]);
  pw[0]=1;
  rep(i,1,N) pw[i]=mult(pw[i-1],2);
  int n,k;
  cin>>n>>k;
  swap(n,k);
  rep(i,2,2*k+1)
    {
      int ans=0;
      if(i<=k)
	{
	  if(i&1)
	    {
	      int x=i/2,useless=k-i+1;
	      rep(j,0,x+1)//these many occur at least once
		ans=add(ans,mult(ncr[x][j],mult(pw[j],calc(n-j,useless+j))));
	    }
	  else
	    {
	      int x=i/2-1,useless=k-i+1;
	      rep(j,0,x+1)//these many occur at least once
		ans=add(ans,mult(ncr[x][j],mult(pw[j],calc(n-j,useless+j))));
	      rep(j,0,x+1)//these many occur at least once
		ans=add(ans,mult(ncr[x][j],mult(pw[j],calc(n-1-j,useless+j))));
	    }
	}
      else
	{
	  if(i&1)
	    {
	      int x=k-i/2,useless=k-2*x;
	      rep(j,0,x+1)//these many occur at least once
		ans=add(ans,mult(ncr[x][j],mult(pw[j],calc(n-j,useless+j))));
	    }
	  else
	    {
	      int x=k-i/2,useless=k-1-2*x;
	      rep(j,0,x+1)//these many occur at least once
		ans=add(ans,mult(ncr[x][j],mult(pw[j],calc(n-j,useless+j))));
	      rep(j,0,x+1)//these many occur at least once
		ans=add(ans,mult(ncr[x][j],mult(pw[j],calc(n-1-j,useless+j))));
	    }
	}
      cout<<ans<<endl;
    }
  return 0 ;
}
