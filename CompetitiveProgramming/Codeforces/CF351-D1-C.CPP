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
const int N=42;
const ll inf=(ll)1e15;
struct matrix
{
  ll a[N][N];
  matrix()
  {
    rep(i,0,N) rep(j,0,N) a[i][j]=inf;
  }
};
matrix multmat(matrix x,matrix y)
{
  matrix c;
  rep(k,0,N)
  rep(i,0,N)
    rep(j,0,N)
    c.a[i][j]=min(c.a[i][j],x.a[i][k]+y.a[k][j]);
  return c;
}
matrix powmat(matrix x,int y)
{
  matrix ans;
  rep(i,0,N) rep(j,0,N) ans.a[i][j]=x.a[i][j]; y--;
  while(y)
    {
      if(y&1) ans=multmat(ans,x);
      x=multmat(x,x);
      y>>=1;
    }
  return ans;
}
int a[N],b[N];
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,m;
  cin>>n>>m;
  rep(i,1,n+1) cin>>a[i];
  rep(i,1,n+1) cin>>b[i];
  matrix x;
  rep(i,0,(1<<n))
    {
      int cost=0,depth=0,mndepth=0;
      rep(j,0,n)
	{
	  if(i&(1<<j))
	    {
	      cost+=a[j+1];
	      depth++; 
	    }
	  else
	    {
	      cost+=b[j+1];
	      depth--;
	    }
	  mndepth=min(mndepth,depth);
	}
      rep(j,0,N)
	{
	  if(j+depth<0 || j+depth>=N) continue;
	  if(j+mndepth<0) continue;
	  x.a[j][j+depth]=min(x.a[j][j+depth],(ll)cost);
	}
    }
  x=powmat(x,m);
  cout<<x.a[0][0]<<endl;
  return 0 ;
}
