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
const int N=100005;
vi v[N];
bool vis[N];
ll ans;
int n,m;
//for subtask 1,2
bool mark[N];
//for subtask 4,5
ll sumd[N]; int d[N],child[N];
bool checksub12()
{
  if(n>20) return false;
  function<void (int,int,int,vi&) > dfs = [&](int u,int s,int f,vi &tmp)->void
    {
      if(u==f)
	{
	  for(int x:tmp) mark[x]=true;
	  return;
	}
      vis[u]=true;
      tmp.pb(u);
      for(int v1:v[u]) if(!vis[v1]) dfs(v1,s,f,tmp);
      tmp.pop_back();
      vis[u]=false;
    };
  rep(i,1,n+1)
    rep(j,i+1,n+1)
    {
      rep(k,1,n+1) mark[k]=false;
      vi tmp;
      dfs(i,i,j,tmp);
      rep(k,1,n+1)
	if(k!=i && k!=j && mark[k]) ans+=2;
    }
  cout<<ans<<endl;
  return true;
}
bool checksub3()
{
  bool sub3=true;
  rep(i,1,n+1) if(sz(v[i])>2) sub3=false;
  if(!sub3) return false;
  function<void (int, vi&)> dfs = [&](int u,vi &tmp)->void
    {
      vis[u]=true; tmp.pb(u);
      for(int v1:v[u]) if(!vis[v1]) dfs(v1,tmp);
    };
  memset(vis,false,sizeof(vis));
  rep(i,1,n+1)
    {
      if(vis[i]) continue;
      vi tmp;
      dfs(i,tmp);
      bool chain=false;
      for(int x:tmp) if(sz(v[x])==1) chain=true;
      int tot=sz(tmp);
      if(!chain) ans+=(ll)(tot-2)*(ll)tot*(tot-1);
      else rep(j,1,tot-1) ans+=((ll)j*(j+1));
    }
  cout<<ans<<endl;
  return true;
}
bool checksub45()
{
  function<bool (int, int)> dfs = [&](int u,int par)->bool
    {
      child[u]=1;
      vis[u]=true;
      for(int v1:v[u])
	{
	  if(v1==par) continue;
	  if(vis[v1]) return false;
	  d[v1]=d[u]+1;
	  dfs(v1,u);
	  child[u]+=child[v1];
	}
      return true;
    };
  function<void (int, int)> dfs2 = [&](int u,int par)->void
    {
      vis[u]=true;
      for(int v1:v[u])
	{
	  if(v1==par) continue;
	  dfs2(v1,u);
	  sumd[u]+=sumd[v1];
	}
      for(int v1:v[u])
	{
	  if(v1==par) continue;
	  ans+=(ll)(child[u]-child[v1]-1)*(ll)sumd[v1];
	  ans+=(ll)child[v1]*(ll)(sumd[u]-sumd[v1]);
	  ans-=(ll)child[v1]*(child[u]-(ll)child[v1]-1)*(ll)(d[u]*2+1);
	}
      ans+=(ll)(sumd[u]-(ll)(child[u]-1)*(ll)(d[u]+1))*(ll)2;
      sumd[u]+=d[u];
    };
  rep(i,1,n+1)
    {
      if(vis[i]) continue;
      if(!dfs(i,-1)) return false;
    }
  memset(vis,false,sizeof(vis));
  rep(i,1,n+1)
    {
      if(vis[i]) continue;
      dfs2(i,-1);
    }
  cout<<ans<<endl;
  return true;
}
namespace bt//bridge tree
{
  const int N=200005;
  vi v[N],tree[N],nodes[N];
  int a[N],b[N],low[N],st[N],d[N],timer,cno=1;//dp is no. of s,f pairs in its subtree
  map<ii,ii> ed;
  bool bridge[N],vis[N],mark[N],art[N];
  queue<int> Q[N];
  ll dp[N],child[N],ans=0;
  void findbridges(int u,int par=-1)
  {
    vis[u]=true;
    low[u]=st[u]=timer++;
    int cnt=0;
    for(int ind:v[u])
      {
	if(ind==par) continue;
	int v1=(a[ind]^b[ind]^u);
	if(vis[v1]) low[u]=min(low[u],st[v1]);
	else
	  {
	    cnt++;
	    findbridges(v1,ind);
	    low[u]=min(low[u],low[v1]);
	    if(par==-1 && cnt>=2) art[u]=true;
	    if(low[v1]>st[u])
	      bridge[ind]=true;
	    if(low[v1]>=st[u] && par!=-1)
	      art[u]=true;
	  }
      }
  }
  void dfs(int u)
  {
    int curr=cno;
    Q[curr].push(u);
    nodes[curr].pb(u);
    vis[u]=true;
    while(!Q[curr].empty())
      {
	u=Q[curr].front();
	Q[curr].pop();
	for(int ind:v[u])
	  {
	    if(mark[ind]) continue;
	    int v1=(a[ind]^b[ind]^u);
	    mark[ind]=true;
	    if(vis[v1])
	      continue;
	    if(bridge[ind])
	      {
		cno++;
		tree[curr].pb(cno);
		tree[cno].pb(curr);
		ed[mp(curr,cno)]=mp(u,v1);
		ed[mp(cno,curr)]=mp(v1,u);
		dfs(v1);
	      }
	    else
	      {
		Q[curr].push(v1);
		nodes[curr].pb(v1);
		vis[v1]=true;
	      }
	  }
      }
  }
  void dfstree(int u)
  {
    child[u]=sz(nodes[u]);
    vis[u]=true;
    for(int v1:tree[u])
      {
	if(vis[v1]) continue;
	dfstree(v1);
	child[u]+=child[v1];
      }
  }
  void dfstree2(int u,int par=-1)
  {
    vis[u]=true;
    int sz=sz(nodes[u]);
    for(int v1:tree[u])
      {
	if(v1==par) continue;
	dfstree2(v1,u);
	dp[u]+=dp[v1];//f,s pairs of its children
      }
    map<int,vi> tmp;
    for(int v1:tree[u])
      {
	if(v1==par) continue;
	ans+=(dp[u]-dp[v1])*(ll)child[v1];//s in v1 and f,t in other comp.
	ans+=(ll)(child[u]-child[v1]-sz)*dp[v1];//t in other comp, and s,f in v1
	auto it=ed[mp(u,v1)];
	tmp[it.fi].pb(v1);
      }
    for(auto it:tmp)//s in v1, f is u, t in other
      {
	ll tmpsum=0;
	for(int x:it.se) tmpsum+=child[x];
	for(int x:it.se)
	  {
	    ans+=(ll)child[x]*(tmpsum-child[x]);//with same node as edge
	    ans+=(ll)child[x]*(ll)sz*(child[u]-tmpsum-sz);//with diff.nodes
	  }
      }
    //consider u as t
    ans+=(ll)dp[u]*sz*(ll)2;
    //for this component
    ans+=(ll)sz*(ll)(sz-1)*(sz-2);
    //f,t is u
    ans+=((ll)(child[u]-sz)*(ll)(sz-1)*(ll)(sz-1))*(ll)2;
    if(par==-1) return;
    for(int v1:tree[u])
      {
	if(v1==par) continue;
	auto it1=ed[mp(u,v1)],it2=ed[mp(u,par)];
	//consider it as f
	if(it1.fi!=it2.fi)//diff. incoming and outgoing node
	  dp[u]+=(ll)child[v1]*sz;
	else
	  dp[u]+=child[v1];
      }
    dp[u]+=(ll)(sz-1)*(sz-1);
  }
};
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  cin>>n>>m;
  rep(i,1,m+1)
    {
      int x,y;
      cin>>x>>y;
      v[x].pb(y); v[y].pb(x);
      bt::a[i]=x; bt::b[i]=y;
      bt::v[x].pb(i); bt::v[y].pb(i);
    }
  if(checksub12()) return 0;//brute
  //if(checksub45()) return 0;// a tree
  //if(checksub3()) return 0; //degree at most 2
  rep(i,1,n+1)
    {
      if(bt::vis[i]) continue;
      bt::findbridges(i);
    }
  rep(i,1,n+1) bt::vis[i]=false;
  bt::cno=0;
  rep(i,1,n+1)
    {
      if(bt::vis[i]) continue;
      ++bt::cno;
      bt::dfs(i);
    }
  rep(i,1,n+1) bt::vis[i]=false;
  rep(i,1,n+1)
    {
      if(bt::vis[i]) continue;
      bt::dfstree(i);
    }
  rep(i,1,n+1) bt::vis[i]=false;
  rep(i,1,bt::cno+1)
    {
      if(bt::vis[i]) continue;
      bt::dfstree2(i);
    }
  cout<<bt::ans<<endl;
  return 0 ;
}
