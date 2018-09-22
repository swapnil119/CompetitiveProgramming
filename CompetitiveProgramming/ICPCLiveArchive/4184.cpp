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
//mobius function
const int N=10005;
int mu[N];
void MF()
{
  ll temp;
  mu[1]=2;
  rep(i,2,N)
    {
      if(!mu[i])
	{
	  mu[i]=1;
	  temp=(ll)i*(ll)i;
	  if(temp<N)
	    for(int j=temp ;j<=N;j+=temp) mu[j]=-1 ;
	  for(int j = i<<1;j<=N;j+=i) if(mu[j]!=-1) ++mu[j] ;
	}
    }
  FEN(i,N-1)  mu[i]=(mu[i]==-1)?0:(mu[i]&1)?-1:1;
}
int a[N],cnt[N];
ll calc(ll x)
{
  ll tmp=x*(x-1)*(x-2)*(x-3);
  tmp/=24;
  return tmp;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  MF();
  int n;
  trace(mu[1]);
  while(cin>>n)
    {
      int mx=0;
      ll ans=0;
      rep(i,1,n+1) cin>>a[i],cnt[a[i]]++,mx=max(mx,a[i]);
      rep(i,1,mx+1)
	{
	  int tmp=0;
	  for(int j=i;j<=mx;j+=i) tmp+=cnt[j];
	  ans+=(ll)mu[i]*calc(tmp);
	}
      rep(i,1,n+1) cnt[a[i]]--;
      cout<<ans<<endl;
    }
  return 0 ;
}
