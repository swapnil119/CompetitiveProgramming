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
const double inf=(double)6e18;
const int N=200005;
ll c[N],pre[N];
double pre2[N],dp[2][N],pre3[N];
void fun(int l,int r,int bestl,int bestr,int curr)
{
  if(l>r) return;
  int mid=(l+r)>>1,i,best=0;
  dp[curr][mid]=inf;
  rep(i,bestl,min(bestr,mid-1)+1)
    {
      if(dp[1-curr][i]+pre2[mid-1]-pre2[i]-pre[i]*(pre3[mid]-pre3[i+1])+(double)mid-i<=dp[curr][mid])
	{
	  dp[curr][mid]=dp[1-curr][i]+pre2[mid-1]-pre2[i]-pre[i]*(pre3[mid]-pre3[i+1])+(double)mid-i;
	  best=i;
	}
    }
  fun(l,mid-1,bestl,best,curr);
  fun(mid+1,r,best,bestr,curr);
}
int main()
{
  int n,k,i,j;
  si(n); si(k);
  k=min(k,n);
  rep(i,1,n+1)
    {
      sll(c[i]);
      pre[i]=pre[i-1]+c[i];
      pre3[i]=pre3[i-1]+1.0/(double)c[i];
    }
  rep(i,1,n)
    pre2[i]=pre2[i-1]+(double)pre[i]/(double)c[i+1];
  rep(i,1,n+1)
    dp[1][i]=i+pre2[i-1];
  rep(i,2,k+1)
    fun(1,n,1,n,(i&1));
  printf("%.10lf\n",dp[(k&1)][n]);
  return 0;
}
