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
//Binary search on answer, add edge between nodes with dist. less than this val.. Now we need to find maximal independent set which is A+B-max matching for bipartite graphs
namespace hcraft {//make left side from 1 to n
  const int N=505,inf=1e9;//make right side from n+1 to n+m
  vi v[N]; int dist[N],match[N],n;//match contains matched vertices
  void init() { rep(i,0,N) match[i]=dist[i]=0,v[i].clear(); }//assign n
  bool bfs() {queue<int> q;//v is adjacency list
   rep(i,1,n+1){if(!match[i])dist[i]=0,q.push(i);else dist[i]=inf;}
    dist[0]=inf; while(!q.empty()) {int u=q.front();q.pop();
      if(u) for(int v1:v[u]) if(dist[match[v1]]==inf) {
	    dist[match[v1]]=dist[u]+1,q.push(match[v1]); }
    } return (dist[0]!=inf);}
  bool dfs(int u) { if(!u) return true;for(int v1:v[u])
      if(dist[match[v1]]==dist[u]+1) if(dfs(match[v1])) {
	  match[v1]=u,match[u]=v1;
	  return true;
	} return false;}
  int karp() { int ans=0;
    while(bfs()) rep(i,1,n+1)
      if(match[i]==0 && dfs(i)) ans++;
    return ans;}};

const int N=505;
int x[N],y[N];
ll dist(int i,int j)
{
  ll tmp=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
  return tmp;
}
int n,b,r;
bool check(ll val)
{
  hcraft::init();
  hcraft::n=b;
  rep(i,1,b+1)
    rep(j,1,r+1)
    if(dist(i,j+b)<val)
      hcraft::v[i].pb(j+b);
  int ans=hcraft::karp();
  ans=b+r-ans;
  return (ans>=n);
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  cin>>n>>b>>r;
  rep(i,1,b+1)
    cin>>x[i]>>y[i];
  rep(i,1,r+1)
    cin>>x[i+b]>>y[i+b];
  ll low=0,high=(ll)1e10;
  while(low<high)
    {
      ll mid=(low+high+1)>>1;
      if(check(mid)) low=mid;
      else high=mid-1;
    }
  cout<<setprecision(10)<<fixed;
  cout<<sqrt((db)high)<<endl;
  return 0 ;
}
