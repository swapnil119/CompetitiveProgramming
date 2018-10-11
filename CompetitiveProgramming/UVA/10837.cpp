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
int mulmod(int x,int y,int mod)
{
  ll tmp=(ll)x*y;
  if(tmp>=mod) tmp%=mod;
  return tmp;
}int powmod(int x,int y,int mod) { int ans=1;//x^y mod m
  while(y) {
    if(y&1) ans=mulmod(ans,x,mod); x=mulmod(x,x,mod); y>>=1;
  } return ans;
}bool miller_rabin(int N){//primality check
  static const int p[12]={2,3,5,7,11,13,17,19,23,29,31,37};
  if(N<=1)return false;
  rep(i,0,12){
    if(p[i]==N)return true;if(N%p[i]==0)return false;
  }int c=N-1,g=0;while(!(c&1))c>>=1,++g;
  rep(i,0,12) { int k=powmod(p[i],c,N);
    rep(j,0,g) {
      int kk=mulmod(k,k,N);if(kk==1&&k!=1&&k!=N-1)return false;
      k=kk;}if(k!=1)return false;
  }return true;
}
const int inf=(int)(2e9)+2;
unordered_map<int,int> dp;
int fun(int phi)
{
  if(phi==1) return 1;
  if(dp.count(phi)) return dp[phi];
  int sq=sqrt(phi);
  vi tmp;
  rep(i,1,sq+1)
    {
      if(phi%i) continue;
      if(miller_rabin(i+1)) tmp.pb(i+1);
      if(i*i!=phi && miller_rabin(phi/i+1)) tmp.pb(phi/i+1);
    }
  int ans=inf;
  reverse(all(tmp));
  for(int x:tmp)
    {
      int curr=x,pre=1;
      while(phi%(curr-pre)==0)
	{
	  if(curr!=2)
	    {
	      int n=fun(phi/(curr-pre));
	      if(n!=-1 && curr<=inf/n)
		{
		  if(__gcd(curr,n)==1)
		    ans=min(ans,curr*n);
		}
	    }
	  pre=curr;
	  if(curr>inf/x) break;
	  curr*=x;
	}
    }
  if(ans==inf) ans=-1;
  return dp[phi]=ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int t=0,phi;
  while(true)
    {
      cin>>phi; t++;
      if(!phi) break; 
      cout<<"Case "<<t<<": "<<phi<<" "<<max(0,fun(phi))<<endl;
    }
  return 0 ;
}
