#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;
typedef pair<ii,int> pii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<pii> vpii;
typedef long long int ll;
typedef unsigned long long int ull;

#define mi 1000000007
#define rep(i,a,b) for(i=a;i<b;i++)
#define repv(i,a,b) for(i=b-1;i>=a;i--)
#define pr(arr,n) rep(i,0,n) cout<<arr[i]<<" "; cout<<endl;
#define pr1(arr,n) rep(i,1,n+1) cout<<arr[i]<<" "; cout<<endl;
#define gc getchar_unlocked
#define PB push_back
#define MP make_pair
#define fi first
#define se second
#define SET(a,b) memset(a,b,sizeof(a))
#define MAX 500005
#define gu getchar
#define pu putchar
#define si(n) scanf("%d",&n)
#define dout(n) printf("%d\n",n)
#define sll(n) scanf("%lld",&n)
#define lldout(n) printf("%lld\n",n)

#define TRACE

#ifdef TRACE
#define trace1(x)                cerr << #x << ": " << x << endl;
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;
#define trace5(a, b, c, d, e)    cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << endl;
#define trace6(a, b, c, d, e, f) cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << " | " << #f << ": " << f << endl;

#else

#define trace1(x)
#define trace2(x, y)
#define trace3(x, y, z)
#define trace4(a, b, c, d)
#define trace5(a, b, c, d, e)
#define trace6(a, b, c, d, e, f)

#endif

int mult(int x,int y)
{
  ll ans,x1=(ll)x,y1=(ll)y;
  ans=(x1*y1)%mi;
  return (int)ans;
}
int gcd(int a,int b) { return b==0 ? a : gcd (b,a%b);}
int lcm(int a,int b) { return a*(b/gcd(a,b));}

ll pow1(ll a,ll b)
{
  ll ans=1;
  while(b>0)
    {
      if(b&1) ans=(ans*a)%mi;	
      a=(a*a)%mi; b>>=1;
    }	
  return ans;
}
ll inf=(ll)1e8;
struct edge
{
  int a,b;
  ll cap,flow;
};
int n,src,dest,d[100005],ptr[100005];
vector<vi> v;
vector<edge> e;
bool bfs()
{
  int i;
  queue<int> q;
  rep(i,0,n+2) d[i]=-1;
  q.push(src);
  d[src]=0;
  while(!q.empty() && d[dest]==-1)
    {
      int u=q.front();
      q.pop();
      rep(i,0,v[u].size())
	{
	  int ind=v[u][i],v1=e[ind].b;
	  ll cap=e[ind].cap,fl=e[ind].flow;
	  if(d[v1]==-1 && fl<cap)
	    {
	      q.push(v1);
	      d[v1]=d[u]+1;
	    }
	}
    }
  return (d[dest]!=-1);
}
ll dfs(int u,ll curr)
{
  if(!curr) return 0;
  if(u==dest) return curr;
  for(;ptr[u]<v[u].size();++ptr[u])
    {
      int ind=v[u][ptr[u]],v1=e[ind].b;
      if(d[v1]==d[u]+1 && e[ind].flow<e[ind].cap)
	{
	  ll pushed=dfs(v1,min(curr,e[ind].cap-e[ind].flow));
	  if(pushed>0)
	    {
	      e[ind].flow+=pushed;
	      e[(ind^1)].flow-=pushed;
	      return pushed;
	    }
	}
    }
  return 0;
}
ll dinic()
{
  ll flow=0,i;
  while(bfs())
    {
      rep(i,0,n+2) ptr[i]=0;
      while(ll curr=dfs(src,inf))
	flow+=curr;
    }
  return flow;
}
void addedge(int x,int y,ll tmp)
{
  if(tmp<0) tmp=inf;
  else if(tmp!=inf) tmp=100-tmp;
  edge e1={x,y,tmp,0};
  edge e2={y,x,0,0};
  v[x].PB((int)e.size());
  e.PB(e1);
  v[y].PB((int)e.size());
  e.PB(e2);
}
int arr[105][105];
int main()
{
  int m,i,j,x,y,w,k,n1;
  si(n1); si(m); si(k);
  rep(i,1,n1+1)
    rep(j,1,m+1)
    si(arr[i][j]);
  n=n1*m+2;
  v.resize(n+5);
  rep(i,1,k+1)
    {
      int x1,y1;
      si(x1); si(y1);
      arr[y1][1]=-1;
      rep(j,1,m)
	{
	  x=(x1-1)*m+1+j; y=(y1-1)*m+1+j+1;
	  addedge(x,y,inf);
	}
    }
  rep(i,1,n1+1)
    {
      addedge(1,(i-1)*m+2,arr[i][1]);
      rep(j,2,m+1)
	addedge((i-1)*m+1+j-1,(i-1)*m+1+j,arr[i][j]);
      addedge((i-1)*m+m+1,n,inf);
    }
  src=1; dest=n;
  double ans=((100*n1-dinic())*1.0)/n1;
  printf("%.2lf\n",ans);
  return 0;
}
