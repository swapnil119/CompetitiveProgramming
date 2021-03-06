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
/*Answer should always with x between A and B. for each x calculate the range of y where our restaurant can lie. Now update it from xs before it and xs after. For each adjacent x range gets affected by 1.*/
const int N=60005;
int x[N],y[N],d[N];
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int t,n,m;
  cin>>t;
  while(t--)
    {
      cin>>m>>n;
      rep(i,1,n+1)
	cin>>x[i]>>y[i];
      rep(i,0,m) d[i]=m;
      rep(i,1,n+1) d[x[i]]=min(d[x[i]],abs(y[i]-y[1]));
      if(x[1]>x[2]) swap(x[1],x[2]);
      rep(i,x[1]+1,x[2]) d[i]=min(d[i],d[i-1]+1);
      repv(i,x[1]+1,x[2]) d[i]=min(d[i],d[i+1]+1);
      ll ans=0;
      rep(i,x[1],x[2]+1)
	ans+=max(0,min(d[i]-1,y[1]))+max(0,min(m-y[1],d[i]));
      cout<<ans<<endl;
    }
  return 0 ;
}
