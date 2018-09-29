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
const int mod=1e9+7,N=100005;
vi divs[N];
int mu[N];
void MF()
{
  ll temp;
  mu[1] = 2 ;
  rep(i,2,N) if(!mu[i])
    {
      mu[i] = 1; temp = (ll)i*(ll)i ;
      if(temp<N) for(int j=temp ;j<N;j+=temp) mu[j]=-1 ;
      for(int j = i<<1;j<N;j+=i) if(mu[j]!=-1) ++mu[j] ;
    } FEN(i,N-1)  mu[i]=(mu[i]==-1)?0:(mu[i]&1)?-1:1;
}

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
int n,m,l,r;
int fun(int val,bool eq=true)
{
  ll tmp2=(ll)val*val;
  int ans=0;
  rep(i,1,n+1)
    {
      int low=0,high=m;
      while(low<high)
	{
	  int mid=(low+high+1)>>1;
	  if(eq)
	    {
	      if((ll)i*(ll)i+(ll)mid*(ll)mid<=tmp2) low=mid;
	      else high=mid-1;
	    }
	  else
	    {
	      if((ll)i*(ll)i+(ll)mid*(ll)mid<tmp2) low=mid;
	      else high=mid-1;
	    }
	}
      if(eq && i>val) break;
      if(!eq && i>=val) break;
      int mx=high;
      if(mx==0)
	{
	  if(i==1) ans=add(ans,mult(n-1,m));
	}
      else
	{
	  for(int x:divs[i])
	    {
	      int fa=mx/x;
	      int tmp=mult(2*m,fa);
	      tmp=add(tmp,-mult(mult(fa,fa+1),x));
	      if(i==1) tmp=add(tmp,m);
	      tmp=mult(tmp,n-i);
	      ans=add(ans,mult(mu[x],tmp));
	    }
	}
    }
  if(val==1 && eq) ans=add(ans,mult(n,m-1));
  else if(val>1) ans=add(ans,mult(n,m-1));
  return ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  MF();
  rep(i,1,N)
    for(int j=i;j<N;j+=i)
      divs[j].pb(i);
  cin>>n>>m>>l>>r;
  cout<<add(fun(r),-fun(l,false))<<endl;
  return 0 ;
}
