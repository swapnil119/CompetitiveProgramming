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
const int N=100005,LN=20;
vi v[N];
string s,s1;
int nch=1,narr,sub[N],pos[N];
int chain[N],CH[N],CP[N],CE[N]; //CH:head(top)of chain,CE: end of chain
int p[LN][N],d[N];
int lps[N];
vi KMPlen[2][N];//max. matched index for each element grouped by chain
vi pre[2][N];//BIT for occurences grouped by chain
string pat;
void update(int i,vi &bit,int val)
{
  i++;
  while(i<sz(bit))
    {
      bit[i]+=val;
      i+=(i&(-i));
    }
}
int query(int i,vi &bit)
{
  i++; int ans=0;
  while(i)
    {
      ans+=bit[i];
      i-=(i&(-i));
    }
  return ans;
}
void compute()
{//lps represents
  const int sz=sz(pat);
  int i=1,j=0; lps[0]=0;//longest length
  while(i<sz)
    {
      if(pat[i]==pat[j]) lps[i]=j+1,i++,j++;
      else
	{
	  if(j) j=lps[j-1];
	  else lps[i++]=0;
	}
    }
}
void dfs(int u,int par=0)
{
  p[0][u]=par; sub[u]=1;
  for(int v1:v[u])
    {
      if(v1==par) continue;
      d[v1]=d[u]+1;
      dfs(v1,u);
      sub[u]+=sub[v1];
    }
}
void HLD(int u,int par=0)
{
  pos[u]=++narr; chain[u]=nch;
  s1+=s[u];
  CE[nch]=u;
  int big=0; //chain:#chain
  for(int v1:v[u])
    {
      if(v1!=par)
	{
	  if(!big) big=v1;
	  else if(sub[v1]>sub[big]) big=v1;
	}
    }
  if(big)
    HLD(big,u);
  for(int v1:v[u])
    {
      if(v1!=par && v1!=big)
	{
	  ++nch; CH[nch]=v1;
	  CP[nch]=u;
	  HLD(v1,u);
	}
    }
}// CP: node(not in curr chain) to jump to.
int lca(int x,int y)
{
  if(d[x]<d[y]) swap(x,y);
  int diff=d[x]-d[y];
  rep(i,0,LN) if(diff&(1<<i)) x=p[i][x];
  if(x==y) return x;
  repv(i,0,LN) if(p[i][x]!=p[i][y]) x=p[i][x],y=p[i][y];
  return p[0][x];
}//pos: basearray pos
int findkth(int x,int k)
{
  rep(i,0,LN)
    if(k&(1<<i)) x=p[i][x];
  return x;
}
int KMP2(string &t)//for exact number of occurences
{
  int ans=0;
  const int sz=sz(pat);
  int i=0,j=0;
  while(i<sz(t))
    {//max matching string till i
      if(t[i]==pat[j])
	{
	  ans+=(j==(sz-1));
	  i++,j++;
	}
      if(j==sz) j=lps[j-1];
      else if(i<sz(t) && t[i]!=pat[j])
	{
	  if(!j) i++; else j=lps[j-1];
	}
    }
  return ans;
}
string getstring(int r,int q)
{
  int t=chain[q];
  int len=pos[q]-pos[CH[t]]+1;
  int diff=max(0,len-(sz(pat)-1));
  int u=findkth(q,diff);
  string tmp="";
  while(true)
    {
      tmp+=s[u];
      if(u==CH[t]) break;
      u=p[0][u];
    }
  u=p[0][u];
  rep(i,0,sz(pat)-1)
    {
      tmp+=s[u];
      if(u==r) break;
      u=p[0][u];
    }
  return tmp;
}
int query_up(int r,int q,int ind)//for going from q to r upwards
{
  int ans=0,t;
  while(chain[q]!=chain[r])
    {
      t=chain[q];
      //in this chain elements are from CH to q
      int nxt=pos[q]-sz(pat)+1;
      if(nxt>=pos[CH[t]]) ans+=query(nxt-pos[CH[t]],pre[ind][t]);
      if(sz(pat)>1)
	{
	  string tmp=getstring(r,q);
	  ans+=KMP2(tmp);
	}
      q=CP[t];
    }
  t=chain[q];
  int st=pos[q]-sz(pat)+1;
  if(st>=pos[r])
    ans+=query(st-pos[CH[t]],pre[ind][t])-query(pos[r]-pos[CH[t]]-1,pre[ind][t]);
  return ans;
}
int query_down(int r,int q,int ind)//for going from r to q downwards
{
  int ans=0,t;
  while(chain[q]!=chain[r])
    {
      t=chain[q];
      //in this chain elements are from CH to q
      ans+=query(pos[q]-pos[CH[t]],pre[ind][t]);
      int len=pos[q]-pos[CH[t]]+1;
      if(sz(pat)>1)
	{
	  string tmp=getstring(r,q);
	  reverse(all(tmp));
	  ans+=KMP2(tmp);
	}
      q=CP[t];
    }
  t=chain[q];
  int en=pos[r]+sz(pat)-1;
  en=min(en-1,pos[q]);
  ans+=query(pos[q]-pos[CH[t]],pre[ind][t])-query(en-pos[CH[t]],pre[ind][t]);
  return ans;
}
int KMP(int l,int r,vi &arr,int offset,int ind)//get number of occurences for l,r
{
  int ans=0;
  const int sz=sz(pat);
  int i=r-l,j=0;
  if(ind==0) //KMPdown
    {
      i=0;
      if(offset) j=arr[offset-1];
    }
  else//KMPup
    {
      if(offset+r-l!=sz(arr)-1) j=arr[offset+r-l+1];
      i=r-l;
    }
  if(j==sz) j=lps[j-1];
  int add=1;//KMPdown
  if(ind) add=-1;
  while(true)
    {//max matching string till i
      if(ind==0 && i>=r-l+1) break;//KMPdown
      if(ind==1 && i<0) break;
      if(s1[l+i]==pat[j])
	{
	  arr[offset+i]=j+1;
	  ans+=(j==(sz-1));
	  i+=add,j++;
	}
      if(j==sz) j=lps[j-1];
      else if(i>=0 && s1[l+i]!=pat[j])
	{
	  if(!j) arr[offset+i]=0,i+=add; else j=lps[j-1];
	}
    }
  return ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,q;
  cin>>n>>q;
  cin>>pat;
  cin>>s; s="#"+s;
  rep(i,1,n)
    {
      int x,y;
      cin>>x>>y;
      v[x].pb(y); v[y].pb(x);
    }
  dfs(1);
  rep(i,1,LN)
    rep(j,1,n+1) p[i][j]=p[i-1][p[i-1][j]];
  CH[1]=1;
  HLD(1); s1="#"+s1;
  compute();//calc lps for pattern
  rep(i,1,nch+1)//calculate KMP array for each chain
    {
      int st=CH[i],en=CE[i];
      int len=pos[en]-pos[st]+1;
      rep(j,0,2)
	{
	  KMPlen[j][i].resize(len,0),pre[j][i].resize(len+1,0);
	  KMP(pos[st],pos[en],KMPlen[j][i],0,j);
	  rep(k,0,len)
	    update(k,pre[j][i],(KMPlen[j][i][k]==sz(pat)));
	}
    }
  int tmpq=0;
  while(q--)
    {
      int type;
      cin>>type;
      if(type==2)//update letter
	{
	  int x; char y;
	  cin>>x>>y;
	  int currchain=chain[x];
	  int ind=pos[x];
	  int st[2],en[2];
	  st[0]=ind,en[0]=min(pos[CE[currchain]],ind+sz(pat)-1);
	  st[1]=max(ind-sz(pat)+1,pos[CH[currchain]]),en[1]=ind;
	  s[x]=s1[pos[x]]=y;
	  rep(j,0,2)
	    {
	      rep(i,st[j]-pos[CH[currchain]],en[j]-pos[CH[currchain]]+1)
		update(i,pre[j][currchain],-(KMPlen[j][currchain][i]==sz(pat)));
	      KMP(st[j],en[j],KMPlen[j][currchain],st[j]-pos[CH[currchain]],j);
	      rep(i,st[j]-pos[CH[currchain]],en[j]-pos[CH[currchain]]+1)
		update(i,pre[j][currchain],(KMPlen[j][currchain][i]==sz(pat)));
	    }
	}
      else
	{
	  tmpq++;
	  int x,y;
	  cin>>x>>y;
	  int lc=lca(x,y);
	  if(lc==x)
	    {
	      cout<<query_down(x,y,0)<<endl;
	      continue;
	    }
	  if(lc==y)
	    {
	      cout<<query_up(y,x,1)<<endl;
	      continue;
	    }
	  int ans=query_up(lc,x,1);
	  ans+=query_down(lc,y,0);
	  if(sz(pat)==1)
	    {
	      ans-=(s[lc]==pat[0]);
	      cout<<ans<<endl;
	      continue;
	    }
	  //calculate part over lca
	  int diff=max(0,d[x]-d[lc]+1-(sz(pat)-1));
	  int u=findkth(x,diff);
	  string tmp="",tmp2="";
	  while(true)
	    {
	      tmp+=s[u];
	      if(u==lc) break;
	      u=p[0][u];
	    }
	  diff=max(0,d[y]-d[lc]+1-(sz(pat)-1));
	  u=findkth(y,diff);
	  while(true)
	    {
	      if(u==lc) break;
	      tmp2+=s[u];
	      u=p[0][u];
	    }
	  reverse(all(tmp2));
	  tmp+=tmp2;
	  ans+=KMP2(tmp);
	  cout<<ans<<endl;
	}
    }
  return 0 ;
}
