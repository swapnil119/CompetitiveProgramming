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
#define int ll
void fun(int a[],int n,int b,int x[])
{
  int mn=INT_MAX,idx=-1,cnt=0;
  rep(i,1,n+1)
    {
      if(a[i])
	{
	  if(a[i]<mn) mn=a[i],idx=i;
	  cnt++;
	}
    }
  if(cnt==1)//only one non-zero element
    {
      assert(b%mn==0);
      x[idx]=b/mn;
      return;
    }
  int c[105];
  rep(i,1,n+1) c[i]=a[i];
  rep(i,1,n+1)
    if(i!=idx) c[i]%=mn;
  fun(c,n,b,x);
  rep(i,1,n+1)
    {
      if(i==idx) continue;
      x[idx]-=(a[i]/mn)*x[i];
    }
}
int a[105],x[105];
signed main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int t;
  cin>>t;
  while(t--)
    {
      int n,b,m;
      cin>>n;
      rep(i,1,n+1) cin>>a[i];
      cin>>b>>m;
      a[++n]=m;
      int g=0;
      rep(i,1,n+1)
	g=__gcd(g,a[i]);
      if(b%g)
	{
	  cout<<"NO"<<endl;
	  continue;
	}
      rep(i,1,n+1) x[i]=0;
      fun(a,n,b,x);
      rep(i,1,n)
	{
	  x[i]=(x[i]%m+m)%m;
	  cout<<x[i]<<" ";
	}
      cout<<endl;
    }
  return 0 ;
}
