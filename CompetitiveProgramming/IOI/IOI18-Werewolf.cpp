#include <bits/stdc++.h>
#include "werewolf.h"
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

const int N=200005;
vi v[N];
bool vis[N];
void dfs(int u,int l,int r,vi &tmp,int type=0)
{
  if(type==0 && u<l) return;
  if(type==1 && u>r) return;
  vis[u]=true;
  tmp.pb(u);
  for(int v1:v[u])
    {
      if(vis[v1]) continue;
      dfs(v1,l,r,tmp,type);
    }
}
vi subtask12(int n,vi S,vi E,vi L,vi R)
{
  int q=sz(S);
  vi ans(q,0);
  rep(i,0,q)
    {
      int x=S[i],y=E[i],l=L[i],r=R[i];
      if(x<l || y>r)
	continue;
      vi tmp1,tmp2;
      rep(j,0,n) vis[j]=false;
      dfs(x,l,r,tmp1);
      dfs(y,l,r,tmp2,1);
      sort(all(tmp1)); sort(all(tmp2));
      bool ok=false;
      for(int x:tmp1)
	{
	  int ind=lower_bound(all(tmp2),x)-tmp2.begin();
	  if(ind!=sz(tmp2) && tmp2[ind]==x) ok=true;
	}
      if(ok) ans[i]=1;
    }
  return ans;
}
vector<ii> seg[4*N];
vi pre[2][4*N];
int pos[N],a[N];
#define lc (pos)+(pos)
#define rc (lc)|1
void build(int low,int high,int pos)
{
  if(low==high)
    {
      seg[pos].pb(mp(a[low],low));
      pre[pos].pb(low);
      return;
    }
  int mid=(low+high)>>1;
  build(low,mid,lc); build(mid+1,high,rc);
  seg[pos]=seg[lc];
  for(int x:seg[rc]) seg[pos].pb(x);
  sort(all(seg[pos]));
  rep(i,0,2)
    pre[i][pos].pb(seg[pos][0].se);
  rep(i,1,sz(seg[pos]))
    {
      pre[0][pos].pb(min(pre[0][pos].back(),seg[pos][i].se));
      pre[1][pos].pb(min(pre[1][pos].back(),seg[pos][i].se));
    }
}
int query(int low,int high,int pos,int l,int r,int k,int type=0)
{
  if(low>r || high<l) return ((type==0)?N:-1);
  if(low>=l && high<=r)
    {
      int ind=upper_bound(all(seg[pos]),mp(k,N))-seg[pos].begin()-1;
      if(ind<0 || seg[pos][ind]>k) return N;
      return pre[type][pos][ind];
    }
  int mid=(low+high)>>1;
  if(!type)
    return min(query(low,mid,lc,l,r,k),query(mid+1,high,rc,l,r,k));
  return max(query(low,mid,lc,l,r,k),query(mid+1,high,rc,l,r,k));
}
int query2(int low,int high,int pos,int l,int r)
{
  if(low>r || high<l) return N;
  if(low>=l && high<=r)
    return seg[pos].back().fi;
  int mid=(low+high)>>1;
  return max(query2(low,mid,lc,l,r),query2(mid+1,high,rc,l,r));
}
vi subtask3(int n,vi S,vi E,vi L,vi R)
{
  int q=sz(S);
  vi ans(q,0);
  int ind=-1;
  rep(i,1,n+1) if(sz(v[i])==1) ind=i;
  if(ind==-1) return ans;
  a[1]=ind; pos[ind]=1;
  rep(i,2,n+1)
    {
      for(int v1:v[ind])
	{
	  if(v1==a[i-1]) continue;
	  ind=v1; break;
	}
      a[i]=ind;
      pos[ind]=i;
    }
  build(1,n,1);
  rep(i,0,q)
    {
      int x=S[i],y=E[i],l=L[i],r=R[i]; x++,y++,l++,r++;
      if(x<l || y>r)
	continue;
      int nx=pos[x],ny=pos[y];
      if(nx<ny)
	{
	  //find 1st element smaller than l in nx,ny
	  ind=query(1,n,1,nx,ny,l-1);
	  if(ind>nx && && ind!=N && a[ind-1]>=l && a[ind-1]<=r)
	    {
	      //check if max element in ind,ny is <=r
	      int mx=query2(1,n,1,ind,ny);
	      if(mx<=r) ans[i]=1;
	    }
	}
      else
	{
	  //find last element smaller than l in nx,ny
	  ind=query(1,n,1,ny,nx,l-1,1);
	  if(ind<nx && && ind!=-1 && a[ind+1]>=l && a[ind+1]<=r)
	    {
	      //check if max element in ny,ind is <=r
	      int mx=query2(1,n,1,ny,ind);
	      if(mx<=r) ans[i]=1;
	    }
	}
    }
  return ans;
}
vi check_validity(int n,vi X,vi Y,vi S,vi E,vi L,vi R)
{
  int q=sz(S);
  rep(i,0,sz(x))
    {
      v[x[i]].pb(y[i]);
      v[y[i]].pb(x[i]);
    }
  if(n<=3000 && q<=3000)
    return subtask12(n,S,E,L,R);
  if(m==n-1)
    return subtask3(n,S,E,L,R);
  return S;
}
