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
/*store queries offline. For each garland update its weight in 2-D BIT. Now update answer of query using 2-D range query corresponding to each garland*/
const int N=2005;
ll bit[N][N];
vector<pair<ii,int> > garlands[N];
bool mark[N];
bool currq[N][N];
pair<ii,ii> qs[N];
ll ans[N];
void update(int x,int y,int w)
{
  while(x<N)
    {
      int ny=y;
      while(y<N)
	{
	  bit[x][y]+=w;
	  y+=(y&(-y));
	}
      y=ny;
      x+=(x&(-x));
    }
}
ll query(int x,int y)
{
  ll ans=0;
  while(x)
    {
      int ny=y;
      while(y)
	{
	  ans+=bit[x][y];
	  y-=(y&(-y));
	}
      y=ny;
      x-=(x&(-x));
    }
  return ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,m,k;
  cin>>n>>m>>k;
  rep(i,1,k+1)
    {
      int len;
      cin>>len;
      rep(j,1,len+1)
	{
	  int x,y,w;
	  cin>>x>>y>>w;
	  garlands[i].pb(mp(mp(x,y),w));
	}
    }
  int q,ind=0;
  rep(i,1,k+1) mark[i]=true;
  cin>>q;
  rep(i,1,q+1)
    {
      string s;
      cin>>s;
      if(s[0]=='S')
	{
	  int x;
	  cin>>x;
	  mark[x]=(!mark[x]);
	}
      else
	{
	  int x1,y1,x2,y2;
	  cin>>x1>>y1>>x2>>y2;
	  qs[++ind]=mp(mp(x1,y1),mp(x2,y2));
	  rep(j,1,k+1) currq[ind][j]=mark[j];
	}
    }
  rep(i,1,k+1)
    {
      for(auto it:garlands[i])
	update(it.fi.fi,it.fi.se,it.se);
      rep(j,1,ind+1)
	{
	  if(currq[j][i])
	    {
	      auto it=qs[j];
	      ans[j]+=query(it.se.fi,it.se.se)-query(it.se.fi,it.fi.se-1)-query(it.fi.fi-1,it.se.se)+query(it.fi.fi-1,it.fi.se-1);
	    }
	}
      for(auto it:garlands[i])
	update(it.fi.fi,it.fi.se,-it.se);
    }
  rep(i,1,ind+1) cout<<ans[i]<<'\n';
  return 0 ;
}
