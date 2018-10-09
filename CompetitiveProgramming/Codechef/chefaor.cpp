#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<
int ,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>pbd_set;
typedef pair<int,int> ii;
typedef pair<ii,int> pii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<pii> vpii;
typedef long long int ll;

#define rep(i,a,b) for(i=a;i<b;i++)
#define repv(i,a,b) for(i=b-1;i>=a;i--)
#define pr(arr,n) rep(i,0,n) cout<<arr[i]<<" "; cout<<endl;
#define pr1(arr,n) rep(i,1,n+1) cout<<arr[i]<<" "; cout<<endl;
#define PB push_back
#define MP make_pair
#define fi first
#define se second
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

int gcd(int a,int b) { return b==0 ? a : gcd (b,a%b);}
int lcm(int a,int b) { return a*(b/gcd(a,b));}

const ll inf=(ll)1e15;
const int N=5005;
int a[N],orrange[N][N];
ll dp[2][N];
void fun(int l,int r,int bestl,int bestr,int curr)
{
  if(l>r) return;
  int mid=(l+r)>>1;
  int best=0,i;
  dp[curr][mid]=-inf;
  rep(i,bestl,min(bestr,mid-1)+1)
    {
      if(dp[1-curr][i]+orrange[i+1][mid]>=dp[curr][mid])
	{
	  dp[curr][mid]=dp[1-curr][i]+orrange[i+1][mid];
	  best=i;
	}
    }
  fun(l,mid-1,bestl,best,curr);
  fun(mid+1,r,best,bestr,curr);
}
int main()
{
  int t,n,i,j,k;
  si(t);
  while(t--)
    {
      si(n); si(k);
      rep(i,1,n+1)
	{
	  si(a[i]);
	  orrange[i][i]=a[i];
	}
      rep(i,1,n+1)
	rep(j,i+1,n+1)
	orrange[i][j]=(orrange[i][j-1]|a[j]);
      rep(i,1,n+1)
	dp[1][i]=orrange[1][i];
      rep(i,2,k+1)
	fun(1,n,1,n,(i&1));
      lldout(dp[(k&1)][n]);
    }
  return 0;
}
