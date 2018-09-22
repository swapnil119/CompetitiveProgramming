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
//use crt for ncr
const int N=200001;
int add(int x,int y,int mod)
{
  x+=y;
  if(x>=mod) x-=mod;
  if(x<0) x+=mod;
  return x;
}
int mult(int x,int y,int mod)
{
  ll tmp=(ll)x*y;
  if(tmp>=mod) tmp%=mod;
  return tmp;
}
int pow1(int x,int y,int mod)
{
  int ans=1;
  while(y)
    {
      if(y&1) ans=mult(ans,x,mod);
      x=mult(x,x,mod);
      y>>=1;
    }
  return ans;
}
const int mod=1e9+7,mod2=mod-1,mod3=mod2/2;
int f[N],f2[N];
int ncr(int n,int r)
{
  int tmp=f[n],tmp2=mult(f[r],f[n-r],mod3);
  tmp=mult(tmp,pow1(tmp2,mod3-2,mod3),mod3);
  return tmp;
}
int ncr2(int n,int r)
{
  int tmp=f2[n],tmp2=mult(f2[r],f2[n-r],2);
  tmp=mult(tmp,pow1(tmp2,0,2),2);
  return tmp;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int t;
  cin>>t;
  f[0]=f2[0]=1;
  rep(i,1,N)
    {
      f[i]=mult(f[i-1],i,mod3);
      f2[i]=mult(f2[i-1],i,2);
    }
  while(t--)
    {
      int a,b,n;
      cin>>a>>b>>n;
      if(a==0)
	{
	  cout<<0<<endl;
	  continue;
	}
      int x1=ncr(2*n,n),x2=ncr2(2*n,n);
      //add answer for first
      int curr=0;
      int rem=mod2/mod3;
      int inv=pow1(rem,mod3-2,mod3);
      curr=mult(x1,mult(rem,inv,mod2),mod2);
      //add answer for second
      rem=mod2/2; 
      inv=1;
      curr=add(curr,mult(x2,mult(rem,inv,mod2),mod2),mod2);
      if(curr==0) cout<<1<<endl;
      else cout<<pow1(a,pow1(curr,b,mod2),mod)<<endl;
    }
  return 0 ;
}
