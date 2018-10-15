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
//dp[i]=expected number of steps to reach from i to c. dp[i]=1.0+sum p(i,j)dp[j] (from j =i to i+n)
const int N=42;
db ncr[N][N],dp[N];
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  rep(i,0,N) ncr[i][0]=1.0;
  rep(i,1,N)
    rep(j,1,i+1) ncr[i][j]=ncr[i-1][j]+ncr[i-1][j-1];
  int T;
  cin>>T;
  rep(t,1,T+1)
    {
      int n,c;
      cin>>c>>n;
      db tmp=ncr[c][n];
      dp[c]=0.0;
      repv(i,0,c)
	{
	  db sum=1.0;
	  rep(j,i+1,min(i+n,c)+1)
	    {
	      int add=j-i,rem=c-i;
	      if(add>=0 && rem>=add && n-add>=0 && i>=n-add)
		{
		  db r=(ncr[rem][add]*ncr[i][n-add])/tmp;
		  sum+=r*dp[j];
		}
	    }
	  db r=ncr[i][n]/tmp;
	  dp[i]=sum/(1.0-r);
	}
      /*dp[n]=1.0/(1.0-(ncr[n][n]/tmp));
      rep(i,n+1,c+1)
	{
	  db sum=1.0;
	  rep(j,max(n,i-n),i)
	    {
	      int add=i-j,rem=c-j;
	      if(add>=0 && rem>=add && n-add>=0 && j>=n-add)
		{
		  db r=(ncr[rem][add]*ncr[j][n-add])/tmp;
		  sum+=r*dp[j];
		}
	    }
	  db r=ncr[i][n]/tmp;
	  trace(sum,r);
	  if(i==c) dp[i]=sum;
	  else dp[i]=sum/(1.0-r);
	  }*/
      cout<<"Case #"<<t<<": "<<setprecision(10)<<fixed<<dp[0]<<endl;
    }
  return 0 ;
}
