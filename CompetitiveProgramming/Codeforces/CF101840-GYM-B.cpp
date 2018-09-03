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
namespace sufftree
{//len:length of edge
  const int inf=1e9,N=2e5,dollar=257;//fps:index of 1st char on edge
  map<int,int> to[N];//to is adjacency list
  int len[N]={inf},s[N],fps[N],link[N];//link:sufflink
  int node,pos,sz=1,n=0;
  int sz1,sz2;
  int dp1[N],dp2[N],val[N];
  void init()
  {
    sz=1; n=0;
    rep(i,0,N) len[i]=inf,to[i].clear(),val[i]=0;
  }
  int make_node(int _pos,int _len)
  {
    fps[sz]=_pos,len[sz]=_len;
    return sz++;
  }
  void go_edge()
  {
    while(pos>len[to[node][s[n-pos]]])
      {
	node=to[node][s[n-pos]]; pos-=len[node];
      }
  }
  void add_letter(int c)
  {
    s[n++]=c; pos++; int last=0;
    while(pos>0)
      {
	go_edge();
	int edge=s[n-pos],&v=to[node][edge],t=s[fps[v]+pos-1];
	if(v==0)
	  {
	    v=make_node(n-pos,inf);
	    link[last]=node; last=0;
	  }
	else if(t==c)
	  {
	    link[last]=node; return;
	  }
	else
	  {
	    int u=make_node(fps[v],pos-1);
	    to[u][c]=make_node(n-1,inf); to[u][t]=v;
	    fps[v]+=pos-1,len[v]-=pos-1,v=u;
	    link[last]=u; last=u;
	  }
	if(node==0) pos--; else node=link[node];
      }
  }
  void dfs(int u,int done=0,int type=0)
  {
    if(!sz(to[u]))
      {
	if(type==0) dp1[u]=1;
	else dp1[u]=0;
	dp2[u]=1;
	return;
      }
    for(auto it:to[u])
      {
	int nxt=it.se,l=fps[it.se];
	if(l-done<=sz1) 
	  dfs(nxt,done+len[it.se],0);
	else
	  dfs(nxt,done+len[it.se],1);
	dp1[u]+=dp1[it.se]; dp2[u]+=dp2[it.se];
      }
  }
  void dfs1(int u,int done=0,int mx=0)
  {
    if(!sz(to[u]))
      return;
    for(auto it:to[u])
      {
	int nxt=it.se,l=fps[it.se];
	int newmx=mx;
	int currlen=min(done+len[it.se],sz1+sz2+1);
	if(dp2[it.se]>dp1[it.se] && dp1[it.se])
	  newmx=max(newmx,currlen);
	if(len[it.se]>=inf/2 && l-done<sz1) 
	  val[l-done]=max(val[l-done],newmx);
	dfs1(it.se,currlen,newmx);
      }
  }
};
const int N=300005;
ll sum[4*N];
vi seg[4*N],pre[4*N];
#define lc pos+pos
#define rc lc|1
void build(int low,int high,int pos)
{
  if(low==high)
    {
      seg[pos].pb(sufftree::val[low]);
      pre[pos].pb(sufftree::val[low]);
      return;
    }
  int mid=(low+high)>>1;
  build(low,mid,lc); build(mid+1,high,rc);
  seg[pos]=seg[lc];
  for(int x:seg[rc]) seg[pos].pb(x);
  sort(all(seg[pos]));
  pre[pos].pb(seg[pos][0]);
  rep(i,1,sz(seg[pos])) pre[pos].pb(pre[pos].back()+seg[pos][i]);
}
ll query(int low,int high,int pos,int l,int r,int k)
{
  if(low>r || high<l) return 0;
  if(low>=l && high<=r)
    {
      int ind=upper_bound(all(seg[pos]),k)-seg[pos].begin()-1;
      if(ind!=-1) return pre[pos][ind]+(ll)(high-low-ind)*k;
      else return (ll)(high-low+1)*k;
    }
  int mid=(low+high)>>1;
  return query(low,mid,lc,l,r,k)+query(mid+1,high,rc,l,r,k);
}
ll calc(ll l,ll r)
{
  if(l==0) return (r*(r+1))/2;
  return (r*(r+1)-l*(l-1))/2;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  freopen("curse.in","r",stdin);
  int T;
  cin>>T;
  rep(t,1,T+1)
    {
      sufftree::init();
      string s1,s2;
      cin>>s1>>s2;
      sufftree::sz1=sz(s1);
      sufftree::sz2=sz(s2);
      rep(i,0,sz(s1)) sufftree::add_letter(s1[i]);
      sufftree::add_letter(sufftree::dollar);
      rep(i,0,sz(s2)) sufftree::add_letter(s2[i]);
      sufftree::add_letter(sufftree::dollar+1);
      sufftree::dfs(0);
      sufftree::dfs1(0);
      rep(i,0,sz(s1)) sufftree::val[i]+=i;
      build(0,sz(s1)-1,1);
      int q;
      cin>>q;
      cout<<"Case "<<t<<": "<<endl;
      while(q--)
	{
	  int l,r;
	  cin>>l>>r;
	  l--; r--;
	  ll curr=query(0,sz(s1)-1,1,l,r,r+1);
	  curr-=calc(l,r);
	  cout<<curr<<endl;
	}
      rep(i,0,4*sz(s1)) seg[i].clear(),pre[i].clear();
    }
  return 0 ;
}
