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
typedef tree<pair<int, int> ,null_type,less<pair<int, int>>,rb_tree_tag,tree_order_statistics_node_update>ordered_set ;
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
const int N=700005;
int z[N],a[N],b[N],c[N],n,d[N];
void calc()
{
  z[0]=3*n+4;
  int l,r=-1;
  rep(i,1,3*n+1)
    {
      z[i]=0;
      if(r>i) z[i]=min(z[i-l],r-i+1);
      while(d[i+z[i]]==d[z[i]]) ++z[i];
      if(i+z[i]-1>r) r=i+z[i]-1,l=i;
    }
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int m;
  cin>>n>>m;
  rep(i,0,n) cin>>a[i];
  a[n]=a[0]+m;
  rep(i,0,n) b[i]=a[i+1]-a[i];
  rep(i,0,n) d[i]=b[i];
  d[n]=-1;
  rep(i,0,n) d[2*n-i]=d[i];
  rep(i,2*n+1,3*n+1) d[i]=d[i-n];
  calc();
  vi ans;
  rep(i,n+1,2*n+1)
    {
      if(z[i]==n)
	{
	  ans.pb((a[0]+a[2*n-i+1])%m);
	}
    }
  sort(all(ans));
  cout<<sz(ans)<<endl;
  if(!sz(ans)) return 0;
  for(int x:ans)
    cout<<x<<" "; cout<<endl;
  return 0 ;
}
