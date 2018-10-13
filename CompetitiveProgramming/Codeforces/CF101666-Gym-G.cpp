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
//if sum of n elements is 0, we can solve it in at most n-1 transactions. If the answer is less we can divide it into multiple components with sum 0. So problem reduces to finding max subsets with sum 0
const int N=21;
int val[N],dp[(1<<N)],sum[(1<<N)];
int dp2[(1<<N)][N];
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,m;
  cin>>n>>m;
  sum[0]=123321;
  rep(i,0,m)
    {
      int x,y,z;
      cin>>x>>y>>z;
      val[x]+=z; val[y]-=z;
    }
  rep(i,0,(1<<n))
    {
      rep(j,0,n)
	if(i&(1<<j)) sum[i]+=val[j];
    }
  rep(j,0,(1<<n))
    dp[j]=(sum[j]==0);
  rep(j,0,(1<<n))
  rep(i,0,n)
    {
      if(j&(1<<i))
	dp[j]=max(dp[j],dp[j^(1<<i)]+(sum[j]==0));
    }
  cout<<n-dp[(1<<n)-1]<<endl;
  return 0 ;
}
