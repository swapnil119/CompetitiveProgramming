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
const int L=5005;
struct edge{int a,b;ll c,f;
  edge(int u,int v,ll cap):a(u),b(v),c(cap),f(0){}};
struct flow{
  const static ll inf = 1e18;//set s=source,t=sink,nodeCt
  int Dlevel[L],Dptr[L],s,t,nodeCt;
  queue<int> Q;vector<edge> E;vi ad[L] ;
  void addEdge(int a,int b,int c,bool directed=1){
    if(a==b)return ;//1 based index
    ad[a].pb(sz(E)),E.pb(edge(a,b,c));
    ad[b].pb(sz(E)),E.pb(edge(b,a,directed?0:c)); }
  bool Dbfs(void){FEN(i,nodeCt)Dlevel[i]=0;Q.push(s),Dlevel[s]=1;
    while(!Q.empty()){int levelsz=sz(Q),v;
      while(levelsz--){v=Q.front();Q.pop() ;
	for(auto &e:ad[v]) if(!Dlevel[E[e].b]&&E[e].f<E[e].c){
	    Dlevel[E[e].b]=Dlevel[v]+1;
	    Q.push(E[e].b);}}}
    return Dlevel[t]>0;}//by default edges are undirected
  ll Ddfs(int x,ll flow){if(!flow) return 0;if(x==t) return flow ;
    for(int &pt=Dptr[x];pt<sz(ad[x]);++pt){
      int e=ad[x][pt];//call dinic()
      if(Dlevel[E[e].b]==Dlevel[x]+1){
	if(ll pushed=Ddfs(E[e].b,min(flow,E[e].c-E[e].f))){
	  E[e].f+=pushed;E[e^1].f-=pushed;return pushed;}}}
    return 0 ;}
  ll dinic(void){ll flow=0;while(Dbfs()){FEN(i,nodeCt)Dptr[i]=0;
      while(ll pushed=Ddfs(s,inf)) flow += pushed ;} return flow ;}
  void reset(void){for(auto &e:E)e.f=0;}};//!!!don't forget to set L
const int N=1005;
int p,r,c,d[N],sum=0,e[N];
vector<pair<int,ii> > v;
bool check(int val)
{
  flow f;
  f.s=r+p+1; f.t=r+p+2; f.nodeCt=f.t;
  rep(i,1,r+1)
    f.addEdge(f.s,i,e[i]);
  rep(i,1,p+1)
    f.addEdge(r+i,f.t,d[i]);
  rep(i,0,sz(v))
    {
      if(v[i].fi>val) break;
      f.addEdge(v[i].se.se,v[i].se.fi+r,1e9);
    }
  int ans=f.dinic();
  return (ans==sum);
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  cin>>p>>r>>c;
  rep(i,1,p+1)
    cin>>d[i],sum+=d[i];
  rep(i,1,r+1)
    cin>>e[i];
  rep(i,1,c+1)
    {
      int x,y,t;
      cin>>x>>y>>t;
      v.pb(mp(t,mp(x,y)));
    }
  sort(all(v));
  int low=1,high=1005*1005;
  while(low<high)
    {
      int mid=(low+high)>>1;
      if(check(mid)) high=mid;
      else low=mid+1;
    }
  if(!check(low)) low=-1;
  cout<<low<<endl;
  return 0 ;
}
