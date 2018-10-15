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
ll getsoln(ll a,ll b,ll c,ll x1,ll x2,ll y1,ll y2)
{
  if(a==0)
    {
      if(b==0 && c==0)//all possible
	return (ll)(x2-x1+1)*(y2-y1+1);
      if(b==0) return 0;//not possible
      if(c==0)
	{
	  if(y1<=0 && y2>=0) return x2-x1+1;
	  return 0;
	}
      if(c%b) return 0;
      ll x=c/b;
      if(y1<=x && y2>=x) return x2-x1+1;
      return 0;
    }
  if(b==0)
    {
      if(a==0 && c==0)//all possible
	return (ll)(x2-x1+1)*(y2-y1+1);
      if(a==0) return 0;//not possible
      if(c==0)
	{
	  if(x1<=0 && x2>=0) return y2-y1+1;
	  return 0;
	}
      if(c%a) return 0;
      ll x=c/a;
      if(x1<=x && x2>=x) return y2-y1+1;
      return 0;
    }
  pair<ll,ll> it=linear_diophantine(a,b,c);
  ll g=__gcd(abs(a),abs(b));
  if(c%g) return 0;
  a/=g; b/=g; c/=g;
  ll x=it.fi,y=it.se;
  int signa=((a>0)?1:-1);
  int signb=((b>0)?1:-1);
  shift(x,y,a,b,(x1-x)/b);
  if(x<x1) shift(x,y,a,b,signb);
  if(x>x2) return 0;
  ll l1=x;
  shift(x,y,a,b,(x2-x)/b);
  if(x>x2) shift(x,y,a,b,-signb);
  if(x<x1) return 0;
  ll r1=x;
  shift(x,y,a,b,-(y1-y)/a);
  if(y<y1) shift(x,y,a,b,-signa);
  if(y>y2) return 0;
  ll l2=x;
  shift(x,y,a,b,-(y2-y)/a);
  if(y>y2) shift(x,y,a,b,signa);
  if(y<y1) return 0;
  ll r2=x;
  if(l2>r2) swap(l2,r2);
  ll lx=max(l1,l2),rx=min(r1,r2);
  if(lx>rx) return 0;
  ll ans=(rx-lx)/abs(b)+1;
  return ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int a,b,c,x1,x2,y1,y2;
  cin>>a>>b>>c>>x1>>x2>>y1>>y2;
  c*=-1;
  cout<<getsoln(a,b,c,x1,x2,y1,y2)<<endl;
  return 0 ;
}
