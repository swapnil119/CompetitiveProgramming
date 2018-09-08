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
/* make edge between two lifts if they meet at a position. use euclidean for that. now check if there is a path from a to b :)*/
ll egcd(ll a,ll b,ll &x,ll &y)
{ //Extended Euclid's Algorithm
  if(!a) {x=0;y=1;return b;}//ax+by=gcd(a,b) 
  ll ret=egcd(b%a,a,y,x); x=x-(b/a)*y; return ret;
}
pair<ll,ll> linear_diophantine(ll a,ll b,ll c)
{//returns x,y
  ll x,y;
  ll d=egcd(abs(a),abs(b),x,y);if(c%d!=0)return mp(-1,-1);//such that c=ax+by
  x*=c/d; y*=c/d;
  if(a<0) x=-x; if(b<0) y=-y;
  return mp(x,y);
}
void shift(ll &x,ll &y,ll a,ll b,ll cnt)
{
  x+=cnt*b;
  y-=cnt*a;
}
const int N=105;
int x[N],y[N];
vi v[N];
bool getsoln(ll a,ll b,ll c,ll x1,ll x2,ll y1,ll y2)
{
  pair<ll,ll> it=linear_diophantine(a,b,c);
  ll g=__gcd(abs(a),abs(b));
  if(c%g) return false;
  a/=g; b/=g; c/=g;
  ll x=it.fi,y=it.se;
  int signa=((a>0)?1:-1);
  int signb=((b>0)?1:-1);
  shift(x,y,a,b,(x1-x)/b);
  if(x<x1) shift(x,y,a,b,signb);
  if(x>x2) return false;
  ll l1=x;
  shift(x,y,a,b,(x2-x)/b);
  if(x>x2) shift(x,y,a,b,-signb);
  if(x<x1) return false;
  ll r1=x;
  shift(x,y,a,b,-(y1-y)/a);
  if(y<y1) shift(x,y,a,b,-signa);
  if(y>y2) return false;
  ll l2=x;
  shift(x,y,a,b,-(y2-y)/a);
  if(y>y2) shift(x,y,a,b,signa);
  if(y<y1) return false;
  ll r2=x;
  if(l2>r2) swap(l2,r2);
  ll lx=max(l1,l2),rx=min(r1,r2);
  if(lx>rx) return false;
  ll ans=(rx-lx)/abs(b)+1;
  if(ans) return true;
  return false;
}
int f,a,b,e;
bool vis[N];
void dfs(int u)
{
  if(vis[u]) return;
  vis[u]=true;
  for(int v1:v[u]) dfs(v1);
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int T;
  cin>>T;
  while(T--)
    {
      memset(vis,false,sizeof(vis));
      cin>>f>>e>>a>>b;
      rep(i,1,e+1)
	cin>>x[i]>>y[i];
      rep(i,1,e+1)
	{
	  rep(j,i+1,e+1)
	    {
	      int C=y[i]-y[j],A=x[j],B=-x[i];
	      ll l1=0,r1=(f-1-y[j])/x[j];
	      ll l2=0,r2=(f-1-y[i])/x[i];
	      if(getsoln(A,B,C,l1,r1,l2,r2))
		v[i].pb(j),v[j].pb(i);
	    }
	}
      rep(i,1,e+1)
	{
	  if(y[i]>a) continue;
	  int diff=(a-y[i]);
	  if(diff%x[i]==0)
	    v[0].pb(i);
	}
      rep(i,1,e+1)
	{
	  if(y[i]>b) continue;
	  int diff=(b-y[i]);
	  if(diff%x[i]==0)
	    v[i].pb(e+1);
	}
      dfs(0);
      rep(i,0,e+1) v[i].clear();
      if(!vis[e+1]) cout<<"The furniture cannot be moved."<<endl;
      else cout<<"It is possible to move the furniture."<<endl;
    }
  return 0 ;
}
