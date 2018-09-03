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
const int L=100005;
vi vpart[L],ad[L];
bool vis[L],mark2[L];
int SZ[L],par[L],part[L],H[L],cpart,a[L],b[L],w[L];
vi p;
bool prime[L];
int cnt[L],cnt0,cnt2;
int tot;
ll ans;
void sieve()
{
  memset(prime,true,sizeof(prime));
  prime[0]=prime[1]=false;
  rep(i,2,L)
    {
      if(!prime[i]) continue;
      for(int j=2*i;j<L;j+=i) prime[j]=false;
      p.pb(i);
    }
}
int dfsSZ(int u,int p=-1)
{
  SZ[u]=1;
  for(int ind:ad[u])
    {
      int v=(a[ind]^b[ind]^u);
      if(!vis[v] && v!=p) SZ[u]+=dfsSZ(v,u);
    }
  return SZ[u];
}
int dfsFC(int u,int r,int p=-1)
{
  for(int ind:ad[u])
    {
      int v=(a[ind]^b[ind]^u);
      if(!vis[v] && v!=p)
	{
	  if(SZ[v]>SZ[r]/2)return dfsFC(v,r,u);
	}
    }
  return u;
}
int val[L];
void dfs1(int u,int r,int p=-1,int pr=0)
{//pr=0 means no prime, pr=-1 means not possible,pr=L means 2 prime
  if(p==r)
    {
      part[u]=++cpart; vpart[cpart].clear();
    }
  else if(p!=-1) part[u]=part[p];
  if(p!=-1) vpart[cpart].pb(u);
  val[u]=pr;
  for(int ind:ad[u])
    {
      int v1=(a[ind]^b[ind]^u);
      if(!vis[v1]&&v1!=p)
	{
	  int newpr=pr;
	  if(pr==-1) newpr=-1;
	  else if(pr==0)
	    {
	      if(w[ind]==1) newpr=0;
	      if(prime[w[ind]]) newpr=w[ind];
	      else if(mark2[w[ind]]) newpr=L;
	      else newpr=-1;
	    }
	  else if(pr==L)
	    {
	      if(w[ind]!=1) newpr=-1;
	    }
	  else
	    {
	      if(w[ind]==1) newpr=pr;
	      else if(prime[w[ind]] && w[ind]!=pr) newpr=L;
	      else newpr=-1;
	    }
	  dfs1(v1,r,u,newpr);
	}
    }
}
void calc(int x,int add=1)
{
  if(x==0) cnt0+=add;
  else if(x==L) cnt2+=add;
  else if(x!=-1) cnt[x]+=add,tot+=add;
}
void solve(int r,int szr)
{
  H[r]=cpart=0; dfs1(r,r);
  rep(i,1,cpart+1)
    {
      for(int v1:vpart[i])
        calc(val[v1]);
    }
  calc(0);//for root
  rep(i,1,cpart+1)
    {
      for(int v1:vpart[i])
	calc(val[v1],-1);
      for(int v1:vpart[i])
	{
	  if(val[v1]==0) ans+=cnt2;
	  else if(val[v1]==L) ans+=cnt0;
	  else if(val[v1]!=-1) ans+=tot-cnt[val[v1]];
	}
      for(int v1:vpart[i]) calc(val[v1]);
    } ; //ans for root
  ans+=cnt2;
  rep(i,1,cpart+1)
    {
      for(int v1:vpart[i])
        calc(val[v1],-1);
    }
  calc(0,-1);
}
void dfsMCT(int u,int p=-1)
{
  dfsSZ(u);
  int r=dfsFC(u,u);
  par[r]=p; solve(r,SZ[u]); vis[r]=true;
  for(int ind:ad[r])
    {
      int v=(a[ind]^b[ind]^r);
      if(!vis[v]) dfsMCT(v,r);
    }
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  freopen("evaluations.in","r",stdin);
  sieve();
  int T;
  cin>>T;
  rep(i,1,L)
    {
      int sq=sqrt(i);
      int c=0;
      bool ok=false;
      rep(j,2,sq+1)
	{
	  if(i%j==0)
	    {
	      c++;
	      if(j!=i/j) c++;
	      if(j!=i/j && prime[j] && prime[i/j]) ok=true;
	    }
	}
      if(c==2 && ok) mark2[i]=true;
    }
  rep(t,1,T+1)
    {
      ans=0;
      int n;
      cin>>n;
      rep(i,1,n+1) vis[i]=false,ad[i].clear();
      rep(i,1,n)
	{
	  int x,y;
	  cin>>x>>y>>w[i];
	  a[i]=x,b[i]=y;
	  ad[x].pb(i); ad[y].pb(i);
	}
      dfsMCT(1);
      cout<<"Case "<<t<<": "<<ans/2<<endl;
    }
  return 0 ;
}
