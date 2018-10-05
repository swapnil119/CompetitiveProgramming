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
#define inf INT_MAX
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
int mina(int arr[],int n)
{
  int x=arr[0],i,pos=0;
  rep(i,1,n){ if(arr[i]<x) { x=arr[i]; pos=i; } }
  return x;
}
int maxa(int arr[],int n)
{
  int x=arr[0],i,pos=0;
  rep(i,1,n){ if(arr[i]>x) { x=arr[i]; pos=i; } }
  return x;
}
int child[100005],col[100005],mex[100005],cnt[100005],st[100005],ft[100005],timer,ver[100005],mxx;
ll ans[100005],sum;
vector<vi> v;
int dfs1(int u,int par)
{
  int i;
  child[u]=1;
  st[u]=timer;
  ver[timer]=u;
  timer++;
  rep(i,0,v[u].size())
    {
      int v1=v[u][i];
      if(v1!=par)
	{
	  dfs1(v1,u);
	  child[u]+=child[v1];
	}
    }
  ft[u]=timer;
}
void dfs(int u,int par,bool keep)
{
  int j,i,mx=0,bigchild=-1;
  rep(i,0,v[u].size())
    {
      int v1=v[u][i];
      if(v1!=par && child[v1]>mx)
	mx=child[v1],bigchild=v1;
    }
  rep(i,0,v[u].size())
    {
      int v1=v[u][i];
      if(v1!=par && v1!=bigchild)
        dfs(v1,u,0);
    }
  if(bigchild!=-1)
    dfs(bigchild,u,1);
  rep(i,0,v[u].size())
    {
      int v1=v[u][i];
      if(v1!=par && v1!=bigchild)
	{
	  rep(j,st[v1],ft[v1])
	    {
	      cnt[col[ver[j]]]++;
	      if(cnt[col[ver[j]]]>mxx)
		mxx=cnt[col[ver[j]]],sum=col[ver[j]];
	      else if(cnt[col[ver[j]]]==mxx)
		sum+=col[ver[j]];
	    }
	}
    }
  cnt[col[u]]++;
  if(cnt[col[u]]>mxx)
    mxx=cnt[col[u]],sum=col[u];
  else if(cnt[col[u]]==mxx)
    sum+=col[u];
  ans[u]=sum;
  if(!keep)
    {
      rep(j,st[u],ft[u])
	cnt[col[ver[j]]]--;
      mxx=sum=0;
    }
}
int main()
{
  int x,y,n,i,j,k;
  si(n); v.resize(n+2);
  rep(i,1,n+1)
    si(col[i]);
  rep(i,0,n-1)
    {
      si(x); si(y);
      v[x].PB(y); v[y].PB(x);
    }
  dfs1(1,-1);
  dfs(1,-1,1);
  rep(i,1,n+1)
    printf("%lld ",ans[i]);
  return 0;
}
