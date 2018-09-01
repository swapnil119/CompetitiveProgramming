#include <bits/stdc++.h>
using namespace std;

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
/*Find any solution and then find valid ranges for x such that x lies b/w x1,x2 and y lies b/w y1,y2*/
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
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  ll a,b,c,x1,x2,y1,y2;
  int T;
  cin>>T;
  rep(t,1,T+1)
    {
      cin>>a>>b>>c>>x1>>x2>>y1>>y2;
      cout<<"Case "<<t<<": ";
      if(a==0 && b==0)
	{
	  if(c==0)
	    cout<<(x2-x1+1)*(y2-y1+1)<<endl;
	  else
	    cout<<0<<endl;
	  continue;
	}
      if(a==0)
	{
	  if(c%b) cout<<0<<endl;
	  else if(-c/b>=y1 && -c/b<=y2) cout<<x2-x1+1<<endl;
	  else cout<<0<<endl;
	  continue;
	}
      if(b==0)
	{
	  if(c%a) cout<<0<<endl;
	  else if((-c/a)>=x1 && (-c/a)<=x2) cout<<y2-y1+1<<endl;
	  else cout<<0<<endl;
	  continue;
	}
      pair<ll,ll> it=linear_diophantine(a,b,-c);
      ll g=__gcd(abs(a),abs(b));
      if(c%g!=0)
	{
	  cout<<0<<endl;
	  continue;
	}
      a/=g; b/=g; c/=g;
      ll x=it.fi,y=it.se;
      int signa=((a>0)?1:-1);
      int signb=((b>0)?1:-1);
      shift(x,y,a,b,(x1-x)/b);
      if(x<x1) shift(x,y,a,b,signb);
      if(x>x2)
	{
	  cout<<0<<endl;
	  continue;
	}
      ll l1=x;
      shift(x,y,a,b,(x2-x)/b);
      if(x>x2) shift(x,y,a,b,-signb);
      if(x<x1)
	{
	  cout<<0<<endl;
	  continue;
	}
      ll r1=x;
      shift(x,y,a,b,-(y1-y)/a);
      if(y<y1) shift(x,y,a,b,-signa);
      if(y>y2)
	{
	  cout<<0<<endl;
	  continue;
	}
      ll l2=x;
      shift(x,y,a,b,-(y2-y)/a);
      if(y>y2) shift(x,y,a,b,signa);
      if(y<y1)
	{
	  cout<<0<<endl;
	  continue;
	}
      ll r2=x;
      if(l2>r2) swap(l2,r2);
      ll lx=max(l1,l2),rx=min(r1,r2);
      if(lx>rx)
	{
	  cout<<0<<endl;
	  continue;
	}
      cout<<(rx-lx)/abs(b)+1<<endl;
    }
  return 0 ;
}
