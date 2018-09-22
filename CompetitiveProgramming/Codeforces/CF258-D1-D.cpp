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
//denote p[i][j] as prob. that a[i]>a[j]
const int N=1005;
db p[N][N];
int a[N];
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,m;
  cin>>n>>m;
  rep(i,0,n) cin>>a[i];
  rep(i,0,n) rep(j,i+1,n) p[i][j]=(a[i]>a[j]);
  while(m--)
    {
      int x,y;
      cin>>x>>y; x--; y--;
      if(x>y) swap(x,y);
      rep(i,0,x) p[i][x]=p[i][y]=0.5*p[i][x]+0.5*p[i][y];
      rep(i,y+1,n) p[x][i]=p[y][i]=0.5*p[x][i]+0.5*p[y][i];
      rep(i,x+1,y)
	{
	  db tmp=p[x][i];
	  p[x][i]=0.5*p[x][i]+0.5*(1.0-p[i][y]);
	  p[i][y]=0.5*(1.0-tmp)+0.5*p[i][y];
	}
      p[x][y]=0.5;
    }
  db ans=0.0;
  rep(i,0,n)
    rep(j,i+1,n) ans+=p[i][j];
  cout<<setprecision(10)<<fixed;
  cout<<ans<<endl;
  return 0 ;
}
