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
const int N=1205;
ll l[N],r[N],y[N],d[N];
map<ll,int> dist;
vector<ii> v[N];
int cnt=0,n;
bool check(int val)
{
  rep(i,0,cnt+1) v[i].clear();
  rep(i,1,n+1)
    {
      v[l[i]].pb(mp(r[i],val));//(pre[r[i]]-pre[l[i]]<=k)
      v[r[i]].pb(mp(l[i],-1));//(pre[l[i]]-pre[r[i]]<=-1)
    }
  rep(i,1,cnt+1) v[0].pb(mp(i,0));//from src to i
  rep(i,1,cnt) v[i+1].pb(mp(i,0));//pre[i]-pre[i+1]<=0
  rep(i,1,cnt) v[i].pb(mp(i+1,1));//pre[i+1]-pre[i]<=1
  rep(i,0,cnt+1) d[i]=1e9;
  //total cnt+1 vertices
  d[0]=0;
  rep(i,1,cnt+1)//cnt no. of rounds
    {
      rep(j,0,cnt+1)//cnt+1 vertices
	{
	  for(auto it:v[j])
	    d[it.fi]=min(d[j]+it.se,d[it.fi]);
	}
    }
  rep(j,0,cnt+1)
    {
      for(auto it:v[j])
	{
	  int old=d[it.fi];
	  d[it.fi]=min(d[j]+it.se,d[it.fi]);
	  if(d[it.fi]!=old) return false;
	}
    }
  return true;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  cin>>n;
  rep(i,1,n+1)
    {
      cin>>l[i]>>r[i]>>y[i];
      dist[l[i]]; dist[r[i]];
    }
  for(auto &it:dist)
    it.se=++cnt;
  rep(i,1,n+1)
    {
      l[i]=dist[l[i]]; r[i]=dist[r[i]];
    }
  int low=1,high=n;
  while(low<high)
    {
      int mid=(low+high)>>1;
      if(check(mid)) high=mid;
      else low=mid+1;
    }
  cout<<low<<endl;
  return 0 ;
}
