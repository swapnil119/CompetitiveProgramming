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
struct edge{
  int a,b;ll c,f;
  edge(int u,int v,ll cap):a(u),b(v),c(cap),f(0){}
};
const int L=400005;
struct flow
{
  const static ll inf = 1e18;//set s=source,t=sink,nodeCt
  int Dlevel[L],Dptr[L],s,t,nodeCt;
  queue<int> Q;
  vector<edge> E; vi ad[L] ;
  void addEdge(int a,int b,int c,bool directed=1)
  {
    if(a==b)return ;//1 based index
    ad[a].pb(sz(E)),E.pb(edge(a,b,c));
    ad[b].pb(sz(E)),E.pb(edge(b,a,directed?0:c));
  }
  bool Dbfs(void)
  {
    FEN(i,nodeCt)Dlevel[i]=0;
    Q.push(s),Dlevel[s]=1;
    while(!Q.empty())
      {
	int levelsz=sz(Q),v;
	while(levelsz--)
	  {
	    v=Q.front();Q.pop() ;
	    for(auto &e:ad[v])
	      if(!Dlevel[E[e].b]&&E[e].f<E[e].c)
		{
		  Dlevel[E[e].b]=Dlevel[v]+1;
		  Q.push(E[e].b);
		}
	  }
      }
    return Dlevel[t]>0;
  }//by default edges are undirected
  ll Ddfs(int x,ll flow)
  {
    if(!flow) return 0;
    if(x==t) return flow ;
    for(int &pt=Dptr[x];pt<sz(ad[x]);++pt)
      {
	int e=ad[x][pt];//call dinic()
	if(Dlevel[E[e].b]==Dlevel[x]+1)
	  {
	    if(ll pushed=Ddfs(E[e].b,min(flow,E[e].c-E[e].f)))
	      {
		E[e].f+=pushed;E[e^1].f-=pushed;return pushed;
	      }
	  }
      }
    return 0 ;
  }
  ll dinic(void)
  {
    ll flow=0;
    while(Dbfs())
      {
	FEN(i,nodeCt)Dptr[i]=0;
	while(ll pushed=Ddfs(s,inf)) flow += pushed ;
      }
    return flow ;
  }
  void reset(void)
  {
    for(auto &e:E)e.f=0;
  }
};//!!!don't forget to set L
const int N=405,N1=40005;
int a[N],b[N];
vi p,ps;
bool prime[N1];
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int t;
  cin>>t;
  memset(prime,true,sizeof(prime));
  rep(i,2,N1)
    {
      if(!prime[i]) continue;
      for(int j=2*i;j<N1;j+=i)
	prime[j]=false;
      p.pb(i);
    }
  while(t--)
    {
      int n;
      cin>>n;
      ps.clear();
      rep(i,1,n+1) cin>>a[i];
      rep(i,1,n+1) cin>>b[i];
      rep(i,1,n+1)
	{
	  int curr=a[i];
	  for(int j=0;j<sz(p) && p[j]*p[j]<=curr;j++)
	    {
	      int cnt=0;
	      while(curr%p[j]==0) curr/=p[j],cnt++;
	      if(cnt) ps.pb(p[j]);
	    }
	  if(curr!=1) ps.pb(curr);
	  curr=b[i];
	  for(int j=0;j<sz(p) && p[j]*p[j]<=curr;j++)
	    {
	      int cnt=0;
	      while(curr%p[j]==0) curr/=p[j],cnt++;
	      if(cnt) ps.pb(p[j]);
	    }
	  if(curr!=1) ps.pb(curr);
	}
      sort(all(ps));
      ps.erase(unique(all(ps)),ps.end());
      assert(sz(ps)<=3600);
      vi v1,v2;
      vector<vi> p1,p2;
      rep(i,1,n+1)
	{
	  vi tmp;
	  int curr=a[i];
	  for(int j=0;j<sz(p) && p[j]*p[j]<=curr;j++)
	    {
	      int cnt=0;
	      while(curr%p[j]==0) curr/=p[j],cnt++;
	      if(cnt) tmp.pb(p[j]);
	    }
	  if(curr!=1) tmp.pb(curr);
	  rep(j,1,n+1)
	    {
	      int x=__gcd(a[i],b[j]);
	      vi tmp2;
	      for(int y:tmp) if(x%y==0) tmp2.pb(y);
	      if(b[j]>a[i] && x>1)
		{
		  v1.pb(x);
		  p1.pb(tmp2);
		}
	      if(b[j]<a[i] && x>1)
		{
		  v2.pb(x);
		  p2.pb(tmp2);
		}
	    }
	}
      assert(sz(v1)<=160000);
      assert(sz(v2)<=160000);
      flow f;
      f.nodeCt=sz(v1)+sz(v2)+sz(ps)+2;
      f.s=f.nodeCt-1; f.t=f.nodeCt;
      rep(i,0,sz(v1)) f.addEdge(f.s,i+1,1);
      rep(i,0,sz(v2)) f.addEdge(sz(v1)+sz(ps)+i+1,f.t,1);
      rep(i,0,sz(v1))
	{
	  for(int x:p1[i])
	    {
	      int ind=lower_bound(all(ps),x)-ps.begin();
	      f.addEdge(i+1,sz(v1)+ind+1,1);
	    }
	}
      rep(i,0,sz(v2))
	{
	  for(int x:p2[i])
	    {
	      int ind=lower_bound(all(ps),x)-ps.begin();
	      f.addEdge(sz(v1)+ind+1,sz(v1)+sz(ps)+i+1,1);
	    }
	}
      cout<<f.dinic()<<endl;
    }
  return 0 ;
}
