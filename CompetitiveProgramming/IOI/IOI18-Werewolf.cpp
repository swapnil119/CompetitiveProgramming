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
const int L=3*N,LN=20;
vi ad[N];
int par[L],val[2][L],val2[L],p[2][LN][L];
vi v[2][L];//edges for 1st tree and 2nd tree
int st[2][L],en[2][L],child[2][L],timer[]={1,1};
int rev[2][L],bit[L];
vector<ii> queries[L];
int finda(int u)
{
  if(par[u]==u) return u;
  return par[u]=finda(par[u]);
}
int cnt;
void dfs(int u,int type=0,int pa=0)
{
  p[type][0][u]=pa;
  rev[type][timer[type]]=u;
  st[type][u]=timer[type]++;
  child[type][u]=1;
  for(int v1:v[type][u])
    dfs(v1,type,u),child[type][u]+=child[type][v1];
  en[type][u]=timer[type];
}
void update(int i,int val)
{
  while(i<L)
    {
      bit[i]+=val;
      i+=(i&(-i));
    }
}
int query(int i)
{
  int ans=0;
  while(i)
    {
      ans+=bit[i];
      i-=(i&(-i));
    }
  return ans;
}
/* to check whether two subtrees intersect, use dsu on tree, for each node, add st[v](of 2nd tree) corr. to each v in u's subtree, and then check if this has any common element by checking st[x],en[x] has any 1 or not*/
//alternate to check if in two permutation, any two subarrays (l,r) and (L,R) have anything in common, simply make a point (i,b-1(a[i])) for each element and check if there is any point in (l,L) to (r,R), this can be done by offline BIT
void calcdfs(int u,int type,bool keep,int n,vi &ans)
{
  int mx=-1,bigchild=-1;
  for(int v1:v[type][u])
    {
      if(child[type][v1]>mx)
	mx=child[type][v1],bigchild=v1;
    }
  for(int v1:v[type][u])
    if(v1!=bigchild)
      calcdfs(v1,type,0,n,ans);
  if(bigchild!=-1)
    calcdfs(bigchild,type,1,n,ans);
  for(int v1:v[type][u])
    {
      if(v1==bigchild) continue;
      rep(i,st[type][v1],en[type][v1])
	{
	  int x=rev[type][i];
	  if(x>=1 && x<=n)
	    update(st[1-type][x],1);
	}
    }
  if(u>=1 && u<=n) update(st[1-type][u],1);
  for(auto it:queries[u])
    {
      int tmp=query(en[1-type][it.fi]-1)-query(st[1-type][it.fi]-1);
      if(tmp) ans[it.se]=1;
    }
  if(!keep)
    {
      rep(i,st[type][u],en[type][u])
	{
	  int x=rev[type][i];
	  if(x>=1 && x<=n)
	    update(st[1-type][x],-1);
	}
    }
}
vi solve(int n,vi X,vi Y,vi S,vi E,vi L,vi R)
{
  //let U be set of reachable nodes from s which are at >R, we need to represent it as a subtree, similarly for nodes<L
  cnt=n;
  rep(i,0,sz(X)) X[i]++,Y[i]++;
  rep(i,0,sz(X))
    ad[min(X[i],Y[i])].pb(max(X[i],Y[i]));
  rep(i,1,n+1) par[i]=i,val[0][i]=n;
  repv(i,1,n)//add edges in reverse order
    {
      for(int v1:ad[i])
	{
	  int x=finda(i),y=finda(v1);
	  if(x==y) continue;
	  cnt++; par[x]=par[y]=par[cnt]=cnt;//make a new node
	  v[0][cnt].pb(x); v[0][cnt].pb(y);
	  val[0][cnt]=i;//index till which edges are added
	}
    }
  int root[2];
  root[0]=cnt;
  rep(i,1,n+1) ad[i].clear(),par[i]=i,val[1][i]=1;
  rep(i,0,sz(X))
    ad[max(X[i],Y[i])].pb(min(X[i],Y[i]));
  rep(i,2,n+1)//add edges in reverse order
    {
      for(int v1:ad[i])
	{
	  int x=finda(i),y=finda(v1);
	  if(x==y) continue;
	  cnt++; par[x]=par[y]=par[cnt]=cnt;//make a new node
	  v[1][cnt].pb(x); v[1][cnt].pb(y);
	  val[1][cnt]=i;//index till which edges are added
	}
    }
  root[1]=cnt;
  //make euler tour of both trees
  rep(i,0,2) dfs(root[i],i,root[i]);
  rep(k,0,2)
    rep(i,1,LN)
    rep(j,1,cnt+1)
    p[k][i][j]=p[k][i-1][p[k][i-1][j]];
  vi ans(sz(S),0);
  rep(i,0,sz(S))
    {
      int x=S[i],y=E[i],l=L[i],r=R[i]; x++,y++,l++,r++;
      if(x<l || y>r)
	continue;
      //find subtree corr. to x s.t. only nodes >=l are reachable
      int curr1=x;
      repv(j,0,LN)
	{
	  if(val[0][p[0][j][curr1]]>=l)
	    curr1=p[0][j][curr1];
	}
      int curr2=y;
      repv(j,0,LN)
	if(val[1][p[1][j][curr2]]<=r)
	  curr2=p[1][j][curr2];
      //now check if subtrees of curr1 and curr2 intersect
      queries[curr1].pb(mp(curr2,i));
    }
  calcdfs(root[0],0,0,n,ans);
  return ans;
}
vi check_validity(int n,vi X,vi Y,vi S,vi E,vi L,vi R)
{
  return solve(n,X,Y,S,E,L,R);
}
