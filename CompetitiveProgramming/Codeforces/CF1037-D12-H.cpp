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
#define lc (pos)+(pos)
#define rc (lc)|1
namespace sufftree
{//len:length of edge
  const int inf=1e9,N=4e5,dollar=257;//fps:index of 1st char on edge
  map<int,int> to[N];//to is adjacency list
  int len[N]={inf},s[N],fps[N],link[N],st[N],en[N];//link:sufflink
  int node,pos,sz=1,n=0,timer=0;
  vi seg[4*N],v[N];
  void init()
  {
    sz=1; n=0;
    rep(i,0,N) len[i]=inf,to[i].clear();
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
  void dfs(int u,int done=0)
  {
    st[u]=timer++;
    if(!sz(to[u]))
      {
	en[u]=timer;
	return;
      }
    for(auto it:to[u])
      {
	int nxt=it.se,l=fps[it.se];
	dfs(nxt,done+len[it.se]);
	if(done+len[it.se]>=inf/2 && !(l==n-1 && !done))
	  v[st[it.se]].pb(l-done);
      }
    en[u]=timer;
  }
  void build(int low=0,int high=sz-1,int pos=1)
  {
    if(low==high)
      {
	seg[pos]=v[low];
	return;
      }
    int mid=(low+high)>>1;
    build(low,mid,lc); build(mid+1,high,rc);
    seg[pos]=seg[lc];
    for(int x:seg[rc]) seg[pos].pb(x);
    sort(all(seg[pos]));
  }
  int query(int low,int high,int pos,int l,int r,int l1,int r1)
  {
    if(low>r || high<l) return -1;
    if(low>=l && high<=r)
      {
	int indr=upper_bound(all(seg[pos]),r1)-seg[pos].begin()-1;
	if(indr>=0 && seg[pos][indr]>=l1) return seg[pos][indr];
	return -1;
      }
    int mid=(low+high)>>1;
    int lft=query(low,mid,lc,l,r,l1,r1);
    if(lft!=-1) return lft;
    return query(mid+1,high,rc,l,r,l1,r1);
  }
  ii getans(vector<ii> &currnodes,string &t,int l,int r)
  {
    reverse(all(currnodes));
    for(auto it:currnodes)
      {
	int currchar=t[it.se],curr=it.fi,currlen=it.se+1;
	if(it.se==sz(t)) currchar=1;
	for(auto it2:to[curr])
	  {
	    if(it2.fi<=currchar) continue;
	    int nxt=it2.se;
	    int tmp=query(0,sz-1,1,st[nxt],en[nxt]-1,l,r-currlen+1);
	    if(tmp!=-1) return mp(tmp,currlen);
	  }
      }
    return mp(-1,-1);
  }
  ii traverse(string &t,int l,int r)
  {
    int curr=0,ind=0,done=0;
    vector<ii> currnodes;
    while(ind<sz(t))
      {
	int currchar=t[ind];
	currnodes.pb(mp(curr,ind));
	if(!to[curr].count(currchar))//iterate back
	  return getans(currnodes,t,l,r);
	int nxt=to[curr][currchar];
	int idx=fps[nxt];
	while(idx<n && ind<sz(t) && t[ind]==s[idx])
	  {
	    if(idx-fps[nxt]+1>len[nxt]) break;
	    ind++,idx++;
	  }
	if(ind==sz(t))//full string found
	  {
	    //check here also
	    if(idx-fps[nxt]<len[nxt])
	      {
		int currlen=sz(t)+1;
		int tmp=query(0,sz-1,1,st[nxt],en[nxt]-1,l,r-currlen+1);
		if(tmp!=-1)
		  return mp(tmp,currlen);
		return getans(currnodes,t,l,r);
	      }
	    //put some small character for this node and look in its child too
	    currnodes.pb(mp(nxt,ind));
	    return getans(currnodes,t,l,r);
	  }
	if(idx-fps[nxt]!=len[nxt])//mismatch in between
	  {
	    if(s[idx]>t[ind])
	      {
		int currlen=ind+1;
		int tmp=query(0,sz-1,1,st[nxt],en[nxt]-1,l,r-currlen+1);
		if(tmp!=-1) return mp(tmp,currlen);
	      }
	    return getans(currnodes,t,l,r);
	  }
	curr=nxt;
      }
  }
};
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ;
  string s;
  cin>>s;
  rep(i,0,sz(s)) sufftree::add_letter(s[i]);
  sufftree::add_letter(2);
  sufftree::dfs(0);
  sufftree::build();
  int q;
  cin>>q;
  while(q--)
    {
      int l,r; string x;
      cin>>l>>r>>x; l--; r--;
      ii ans=sufftree::traverse(x,l,r);
      if(ans.fi==-1) cout<<-1<<'\n';
      else cout<<s.substr(ans.fi,ans.se)<<'\n';
    }
  return 0 ;
}
