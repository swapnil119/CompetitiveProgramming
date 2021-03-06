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
const int L = 5005 ;
struct edge
{
  int a,b;
  ll c,f ;
  edge(int u,int v,ll cap):a(u),b(v),c(cap),f(0){}
} ;
struct flows
{
  const static ll inf = 1e18 ;
  int Dlevel[L], Dptr[L], s, t, nodeCt ;
  queue<int> Q; vector<edge> E,E2; vi ad[L] ;
  void addEdge(int a,int b,int c)
  {
    if(a==b)return ;
    ad[a].pb(sz(E)),E.pb(edge(a,b,c)) ;
    ad[b].pb(sz(E)),E.pb(edge(b,a,0)) ;
  }

  bool Dbfs(void)
  {
    FEN(i,nodeCt)Dlevel[i]=0;Q.push(s),Dlevel[s]=1;
    while(!Q.empty())
      {
	int levelsz=sz(Q),v ;
	while(levelsz--)
	  {
	    v = Q.front();Q.pop() ;
	    for(auto &e:ad[v]) if(!Dlevel[E[e].b]&&E[e].f<E[e].c)
				 {
				   Dlevel[E[e].b]=Dlevel[v]+1;
				   Q.push(E[e].b);
				 }
	  }
      }
    return Dlevel[t]>0 ;
  }
  ll Ddfs(int x,ll flow)
  {
    if(!flow) return 0;
    if(x==t) return flow ;
    for(int &pt=Dptr[x];pt<sz(ad[x]);++pt)
      {
	int e=ad[x][pt];
	if(Dlevel[E[e].b]==Dlevel[x]+1)
	  {
	    if(ll pushed=Ddfs(E[e].b,min(flow,E[e].c-E[e].f)))
	      {
		E[e].f+=pushed ;
		E[e^1].f -= pushed;
		return pushed ;
	      }
	  }
      }
    return 0 ;
  }

  ll dinic(void)
  {
    ll flow=0 ;
    while(Dbfs())
      {
	// trace("yes") ;
	FEN(i,nodeCt)Dptr[i]=0;
	while(ll pushed=Ddfs(s,inf)) flow+=pushed;	
      }
    return flow ;
  }

  void reset(void)
  {
    for(auto &e:E)e.f=0;
  }
} ;

int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int M, N, K ; cin>>M>>N>>K ;
  int x,y ;
  flows F ;
  FN(i,K)
    {
      cin>>x>>y ;
      F.addEdge(y,x+N,1) ;
    }
  // trace("here") ;
  F.s = N+M+1 ;
  F.t = N+M+2 ;
  F.nodeCt = N+M+2 ;
  FEN(i,N) F.addEdge(F.s,i,1) ;
  FEN(i,M) F.addEdge(i+N,F.t,1) ;
  ll ans = F.dinic() ;
  // trace(ans) ;
  F.E2 = F.E ;
  ll extra = 0 ;
  FEN(i,M)
    {
      F.E = F.E2 ;
      for(int v:F.ad[i+N]) if(F.E[v].b == F.t)
			     {
			       F.E[v].c += 2 ;
			       break ;
			     }
      extra = max(extra, F.dinic()) ;
    }
  cout << ans + extra << "\n" ;
  return 0 ;
}
