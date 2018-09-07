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
/*Using mobius function. Inclusion exclusion */
const int N=1000005,L=61;
int sp[N],pre[N],mu[L];
bool calc(ll x,int k,ll n)
{
  ll ans=1;
  while(k)
    {
      if(k&1)
	{
	  if(ans>n/x) return false;
	  ans*=x;
	}
      k>>=1;
      if(x>n/x && k) return false;
      x*=x;
    }
  return true;
}
int arr[L];
ll findk(ll n,int k)
{
  ll low=1,high=arr[k];
  if(high>n) high=n;
  while(low<high)
    {
      ll mid=(low+high+1)>>1;
      if(calc(mid,k,n)) //less than n
	low=mid;
      else
	high=mid-1;
    }
  return low;
}
ll findk2(int k)
{
  ll n=(ll)1e18;
  ll low=1,high=n;
  while(low<high)
    {
      ll mid=(low+high+1)>>1;
      if(calc(mid,k,n)) //less than n
	low=mid;
      else
	high=mid-1;
    }
  return low;
}
void MF()
{
  ll temp ;
  mu[1]=2;
  rep(i,2,L)
    if(!mu[i])
      {
	mu[i] = 1 ; temp = (ll)i*(ll)i ;
	if(temp<=N)
	  for(int j=temp ;j<L;j+=temp) mu[j]=-1 ;
	for(int j = i<<1;j<L;j+=i) if(mu[j]!=-1) ++mu[j] ;
      }
  FEN(i,L-1)  mu[i]=(mu[i]==-1)?0:(mu[i]&1)?-1:1;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL);
  rep(i,2,L) arr[i]=findk2(i);
  MF();
  int t;
  cin>>t;
  while(t--)
    {
      ll n;
      cin>>n;
      ll ans=n-1;
      rep(i,2,61)
	{
	  ll tmp=findk(n,i);
	  ans+=(ll)mu[i]*(tmp-1);
	}
      cout<<ans<<endl;
    }
  return 0 ;
}
