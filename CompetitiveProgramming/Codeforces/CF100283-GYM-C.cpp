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
//After each time instant, find for next time instant how many times will it occur in the grid, that can be represented as a submatrix sum
const int N=605,mod=1e9+7,offset=N/3;
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
int a[N][N],val[N][N],pre[N][N],curr[N][N];
int query(int x1,int y1,int x2,int y2)
{
  return add(add(pre[x2][y2],-pre[x1-1][y2]),add(pre[x1-1][y1-1],-pre[x2][y1-1]));
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  freopen("treasures.in","r",stdin);
  int T;
  cin>>T;
  rep(t,1,T+1)
    {
      int n,m,s,r,c;
      cin>>n>>m>>s>>r>>c;
      rep(i,1,n+1) rep(j,1,m+1) curr[i][j]=0,cin>>a[i][j];
      rep(i,0,N) rep(j,0,N) val[i][j]=0;
      val[r-c+offset][r+c+offset]=1;
      curr[r][c]=1;
      repv(S,2,s+1)
	{
	  rep(i,1,N)
	    rep(j,1,N)
	    pre[i][j]=add(add(val[i][j],pre[i-1][j]),add(pre[i][j-1],-pre[i-1][j-1]));
	  rep(i,0,N)
	    rep(j,0,N) val[i][j]=0;
	  rep(i,1,n+1)
	    rep(j,1,m+1)
	    {
	      //x+y should be (i+j-S,i+j+S)
	      //x-y should be(i-j-S,i-j+S)
	      int x1=i-j-S+offset+1,x2=i-j+S+offset-1;
	      int y1=i+j-S+offset+1,y2=i+j+S+offset-1;
	      val[i-j+offset][i+j+offset]=add(val[i-j+offset][i+j+offset],query(x1,y1,x2,y2));
	      curr[i][j]=query(x1,y1,x2,y2);
	    }
	}
      int ans=0;
      rep(i,1,n+1)
	rep(j,1,m+1)
	ans=add(ans,mult(curr[i][j],a[i][j]));
      cout<<"Case "<<t<<": "<<ans<<endl;
    }
  return 0 ;
}
