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
const int N=1005;
ll bit[4][N][N];
int getid(int x,int y)
{
  int id=0;
  if(x&1) id++;
  if(y&1) id+=2;
  return id;
}
void update(int x,int y,ll val)
{
  int id=getid(x,y);
  while(x<N)
    {
      int tmp=y;
      while(y<N)
	{
	  bit[id][x][y]^=val;
	  y+=(y&(-y));
	}
      x+=(x&(-x));
      y=tmp;
    }
}
ll query(int x,int y)
{
  int id=getid(x,y);
  ll ans=0;
  while(x)
    {
      int tmp=y;
      while(y)
	{
	  ans^=bit[id][x][y];
	  y-=(y&(-y));
	}
      x-=(x&(-x));
      y=tmp;
    }
  return ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,q;
  cin>>n>>q;
  while(q--)
    {
      int type,x1,x2,y1,y2;
      ll val;
      cin>>type>>x1>>y1>>x2>>y2;
      if(type==1)
	{
	  ll ans=query(x2,y2);
	  ans^=query(x1-1,y2);
	  ans^=query(x2,y1-1);
	  ans^=query(x1-1,y1-1);
	  cout<<ans<<endl;
	}
      else
	{
	  cin>>val;
	  update(x1,y1,val);
	  update(x1,y2+1,val);
	  update(x2+1,y1,val);
	  update(x2+1,y2+1,val);
	}
    }
  return 0 ;
}
