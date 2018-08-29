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
struct event
{
  ii p1,p2;
  int time;
  event() {}
  event(ii p1a,ii p2a,int t)
  {
    p1=p1a,p2=p2a,time=t;
  }
  bool operator < (const event &e) const
  {
    return time>e.time;
  }
};
#define lc (pos)+(pos)
#define rc (lc)|1
namespace rua//rectangle union area
{
  struct rectangle
  {
    int x1,y1,x2,y2;
    rectangle() { x1=x2=y1=y2=0; }
    rectangle(int X1,int Y1,int X2,int Y2)
    {
      x1=X1; y1=Y1; x2=X2; y2=Y2;
    }
  };
  struct event
  {
    int x,y1,y2,type;
    event() { }
    event(int X,int Y1,int Y2,int Type)
    {
      x=X; y1=Y1; y2=Y2; type=Type;
    }
  };
  bool operator < (const event &A,const event&B)
  {
    return A.x<B.x;
  }
  struct node
  {
    int sum,ans,prob;
    node() { sum=ans=prob=0; }
    node(int Sum,int Ans,int Prob)
    {
      sum=Sum; ans=Ans; prob=Prob;
    }
  };
  const int L=1000005;
  node tree[L*4];
  vector<rectangle> rect;
  vector<event> sweep;
  vi sorted;
  int interval[L];
  void build(int pos,int low,int high)
  {
    tree[pos]=node();
    if(low==high)
      {
	tree[pos].sum+=interval[low];
	return;
      }
    int mid=(low+high)>>1;
    build(lc,low,mid); build(rc,mid+1,high);
    tree[pos].sum=tree[lc].sum+tree[rc].sum;
  }
  void compressandcalc()
  {
    sweep.clear();
    sorted.clear();
    //make segtree of y coordinates
    for(auto i:rect) sorted.pb(i.y1),sorted.pb(i.y2);
    sort(all(sorted));
    sorted.erase(unique(all(sorted)),sorted.end());
    assert(sz(sorted)<L);
    rep(i,0,sz(sorted)-1)
      interval[i+1]=sorted[i+1]-sorted[i];
    for(auto r: rect)
      {
	sweep.pb(event(r.x1,r.y1,r.y2,1));
	sweep.pb(event(r.x2,r.y1,r.y2,-1));
      }
    sort(all(sweep));
    build(1,1,sz(sorted)-1);
  }
  int ask(int x)
  {
    if(tree[x].prob) return tree[x].sum;
    return tree[x].ans;
  }
  void update(int pos,int low,int high,int l,int r,int val)
  {
    if(low>r || high<l) return;
    if(low>=l && high<=r)
      {
	tree[pos].prob+=val;
	return;
      }
    int mid=(low+high)>>1;
    update(lc,low,mid,l,r,val);
    update(rc,mid+1,high,l,r,val);
    tree[pos].ans=ask(lc)+ask(rc);
  }
  ll Sweep()
  {
    if(sorted.empty() || sweep.empty()) return 0;
    int prev=0;
    ll ans=0;
    for(auto it:sweep)
      {
	ans+=(ll)(it.x-prev)*(ll)ask(1);
	prev=it.x;
	int st=lower_bound(all(sorted),it.y1)-sorted.begin()+1;
	int en=lower_bound(all(sorted),it.y2)-sorted.begin();
	update(1,1,sz(sorted)-1,st,en,it.type);
      }
    return ans;
  }
}
map<ii,int> dir;
unordered_map<int,set<int> > R,L,U,D,RD,DR,LD,DL,UR,RU,LU,UL;
priority_queue<event> pq;
set<ii> deleted,delnow;
int getnext(int x,set<int> &l,set<int> &r)
{
  auto it=r.lower_bound(x);
  if(it==r.end()) return -1;
  auto it2=l.lower_bound(*it);
  it2=prev(it2);
  if((*it2)!=x) return -1;
  return *it;
}
int getprev(int x,set<int> &l,set<int> &r)
{
  auto it=r.lower_bound(x);
  if(it==r.begin()) return -1;
  it=prev(it);
  auto it2=l.lower_bound(*it);
  if((*it2)!=x) return -1;
  return *it;
}
int n,m;
void make_rectangle(ii pt,int time)
{
  int d=dir[pt];
  if(time!=-1)
    {
      if(d==0) rua::rect.pb(rua::rectangle(pt.fi-1,pt.se-1,pt.fi+time,pt.se));
      else if(d==1) rua::rect.pb(rua::rectangle(pt.fi-1,pt.se-time-1,pt.fi,pt.se));
      else if(d==2) rua::rect.pb(rua::rectangle(pt.fi-time-1,pt.se-1,pt.fi,pt.se));
      else rua::rect.pb(rua::rectangle(pt.fi-1,pt.se-1,pt.fi,pt.se+time));
      return;
    }
  if(d==0) rua::rect.pb(rua::rectangle(pt.fi-1,pt.se-1,n,pt.se));
  else if(d==1) rua::rect.pb(rua::rectangle(pt.fi-1,0,pt.fi,pt.se));
  else if(d==2) rua::rect.pb(rua::rectangle(0,pt.se-1,pt.fi,pt.se));
  else rua::rect.pb(rua::rectangle(pt.fi-1,pt.se-1,pt.fi,m));
}
void tmpremove(ii pt)
{
  int d=dir[pt];
  int x=pt.fi,y=pt.se;
  if(d==0) R[y].erase(x),RU[x-y].erase(x),RD[x+y].erase(x);
  else if(d==1) U[x].erase(y),UR[x-y].erase(x),UL[x+y].erase(x);
  else if(d==2) L[y].erase(x),LD[x-y].erase(x),LU[x+y].erase(x);
  else D[x].erase(y),DL[x-y].erase(x),DR[x+y].erase(x);
}
void remove(ii pt)
{
  int d=dir[pt];
  if(d==0)
    {
      auto it=R[pt.se].lower_bound(pt.fi);
      if(it!=R[pt.se].begin())//modify point left to it
	{
	  it=prev(it);
	  int l=*it,r=getnext(l,R[pt.se],L[pt.se]);
	  if(r!=-1)
	    pq.push(event(mp(l,pt.se),mp(r,pt.se),(r-l)/2));
	}
      int add=pt.fi+pt.se;
      it=RD[add].lower_bound(pt.fi);
      if(it!=RD[add].begin())
	{
	  it=prev(it);
	  int l=*it,r=getnext(l,RD[add],DR[add]);
	  if(r!=-1)
	    pq.push(event(mp(l,add-l),mp(r,add-r),r-l));
	}
      int sub=pt.fi-pt.se;
      it=RU[sub].lower_bound(pt.fi);
      if(it!=RU[sub].begin())
	{
	  it=prev(it);
	  int l=*it,r=getnext(l,RU[sub],UR[sub]);
	  if(r!=-1)
	    pq.push(event(mp(l,l-sub),mp(r,r-sub),r-l));
	}
    }
  else if(d==3)
    {
      auto it=D[pt.fi].lower_bound(pt.se);
      if(it!=D[pt.fi].begin())//modify point left to it
	{
	  it=prev(it);
	  int l=*it,r=getnext(l,D[pt.fi],U[pt.fi]);
	  if(r!=-1)
	    pq.push(event(mp(pt.fi,l),mp(pt.fi,r),(r-l)/2));
	}
      int sub=pt.fi-pt.se;
      it=DL[sub].lower_bound(pt.fi);
      if(it!=DL[sub].begin())
	{
	  it=prev(it);
	  int l=*it,r=getnext(l,DL[sub],LD[sub]);
	  if(r!=-1)
	    pq.push(event(mp(l,l-sub),mp(r,r-sub),r-l));
	}
      int add=pt.fi+pt.se;
      it=DR[add].lower_bound(pt.fi);
      if(it!=DR[add].end())
	{
	  int l=*it,r=getprev(l,DR[add],RD[add]);
	  swap(l,r);
	  if(l!=-1)
	    pq.push(event(mp(l,add-l),mp(r,add-r),r-l));
	}
    }
  else if(d==1)
    {
      auto it=U[pt.fi].lower_bound(pt.se);
      if(it!=U[pt.fi].end())//modify point left to it
	{
	  int l=*it,r=getprev(l,U[pt.fi],D[pt.fi]);
	  swap(l,r);
	  if(l!=-1)
	    pq.push(event(mp(pt.fi,l),mp(pt.fi,r),(r-l)/2));
	}
      int add=pt.fi+pt.se;
      it=UL[add].lower_bound(pt.fi);
      if(it!=UL[add].begin())
	{
	  it=prev(it);
	  int l=*it,r=getnext(l,UL[add],LU[add]);
	  if(r!=-1)
	    pq.push(event(mp(l,add-l),mp(r,add-r),r-l));
	}
      int sub=pt.fi-pt.se;
      it=UR[sub].lower_bound(pt.fi);
      if(it!=UR[sub].end())
	{
	  int l=*it,r=getprev(l,UR[sub],RU[sub]);
	  swap(l,r);
	  if(l!=-1)
	    pq.push(event(mp(l,l-sub),mp(r,r-sub),r-l));
	}
    }
  else
    {
      auto it=L[pt.se].lower_bound(pt.fi);
      if(it!=L[pt.se].end())//modify point left to it
	{
	  int l=*it,r=getprev(l,L[pt.se],R[pt.se]);
	  swap(l,r);
	  if(l!=-1)
	    pq.push(event(mp(l,pt.se),mp(r,pt.se),(r-l)/2));
	}
      int sub=pt.fi-pt.se;
      it=LD[sub].lower_bound(pt.fi);
      if(it!=LD[sub].end())
	{
	  int l=*it,r=getprev(l,LD[sub],DL[sub]);
	  swap(l,r);
	  if(l!=-1)
	    pq.push(event(mp(l,l-sub),mp(r,r-sub),r-l));
	}
      int add=pt.fi+pt.se;
      it=LU[add].lower_bound(pt.fi);
      if(it!=LU[add].end())
	{
	  int l=*it,r=getprev(l,LU[add],UL[add]);
	  swap(l,r);
	  if(l!=-1)
	    pq.push(event(mp(l,add-l),mp(r,add-r),r-l));
	}
    }
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  cin>>n>>m;
  int t;
  cin>>t;
  rep(i,1,t+1)
    {
      int x,y,d;
      cin>>x>>y>>d;
      dir[mp(x,y)]=d;
      if(d==0) R[y].insert(x),RU[x-y].insert(x),RD[x+y].insert(x);
      else if(d==1) U[x].insert(y),UR[x-y].insert(x),UL[x+y].insert(x);
      else if(d==2) L[y].insert(x),LD[x-y].insert(x),LU[x+y].insert(x);
      else D[x].insert(y),DL[x-y].insert(x),DR[x+y].insert(x);
    }
  for(auto it:R)//diff. ys
    {
      for(auto it2:it.se)//diff xs corr. to ys
	{
	  int l=it2,r=getnext(l,it.se,L[it.fi]);
	  if(r!=-1)
	    pq.push(event(mp(l,it.fi),mp(r,it.fi),(r-l)/2));
	}
    }
  for(auto it:D)//diff. xs
    {
      for(auto it2:it.se)//diff ys corr. to xs
	{
	  int l=it2,r=getnext(l,it.se,U[it.fi]);
	  if(r!=-1)
	    pq.push(event(mp(it.fi,l),mp(it.fi,r),(r-l)/2));
	}
    }
  for(auto it:RD)//diff. x+y s
    {
      for(auto it2:it.se)//diff xs corr. to x+y s
	{
	  int l=it2,r=getnext(l,it.se,DR[it.fi]);
	  if(r!=-1)
	    pq.push(event(mp(l,it.fi-l),mp(r,it.fi-r),r-l));
	}
    }
  for(auto it:RU)//diff. x-y s
    {
      for(auto it2:it.se)//diff xs corr. to x-y s
	{
	  int l=it2,r=getnext(l,it.se,UR[it.fi]);
	  if(r!=-1)
	    pq.push(event(mp(l,l-it.fi),mp(r,r-it.fi),r-l));
	}
    }
  for(auto it:UL)//diff. x+y s
    {
      for(auto it2:it.se)//diff xs corr. to x+y s
	{
	  int l=it2,r=getnext(l,it.se,LU[it.fi]);
	  if(r!=-1)
	    pq.push(event(mp(l,it.fi-l),mp(r,it.fi-r),r-l));
	}
    }
  for(auto it:DL)//diff. x-y s
    {
      for(auto it2:it.se)//diff xs corr. to x-y s
	{
	  int l=it2,r=getnext(l,it.se,LD[it.fi]);
	  if(r!=-1)
	    pq.push(event(mp(l,l-it.fi),mp(r,r-it.fi),r-l));
	}
    }
  while(!pq.empty())
    {
      delnow.clear();
      auto it=pq.top();
      int currt=it.time;
      while(!pq.empty() && pq.top().time==currt)
	{
	  it=pq.top();
	  pq.pop();
	  bool deleted1=deleted.count(it.p1),deleted2=deleted.count(it.p2);
	  bool ok=(!deleted1 || delnow.count(it.p1));
	  ok&=(!deleted2 || delnow.count(it.p2));
	  if(!ok) continue;
	  if(!deleted1) tmpremove(it.p1);
	  if(!deleted2) tmpremove(it.p2);
	  if(!deleted1)
	    {
	      deleted.insert(it.p1); delnow.insert(it.p1);
	      make_rectangle(it.p1,currt);
	      remove(it.p1);
	    }
	  if(!deleted2)
	    {
	      deleted.insert(it.p2); delnow.insert(it.p2);
	      make_rectangle(it.p2,currt);
	      remove(it.p2);
	    }
	}
    }
  for(auto it:dir)//these will go till the end of grid
    {
      if(deleted.count(it.fi)) continue;
      make_rectangle(it.fi,-1);
    }
  rua::compressandcalc();
  cout<<rua::Sweep()<<endl;
  return 0 ;
}
