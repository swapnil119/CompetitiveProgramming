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
const int N=105;
db dp[N][N];//games played, games won
int main()
{
  int T;
  scanf("%d",&T);
  rep(t,1,T+1)
    {
      memset(dp,0,sizeof(dp));
      int n,num,den;
      db p;
      scanf("%d/%d %d",&num,&den,&n);
      p=(db)num/(db)den;
      dp[1][1]=p; dp[1][0]=1.0-p;
      rep(i,2,n+1)
	{
	  rep(j,0,i)
	    {
	      db won=j;
	      if((won/(db)(i-1))>p) continue;
	      //win this game
	      dp[i][j+1]=dp[i-1][j]*p;
	      //lose this game
	      dp[i][j]=dp[i-1][j]*(1.0-p);
	    }
	}
      db winday=0.0;
      rep(i,1,n+1)
	{
	  rep(j,0,i+1)
	    {
	      db won=j;
	      if(won/(db)i>p) winday+=dp[i][j];
	    }
	}
      db loseday=1.0-winday;
      db ret=1.0/loseday;
      int ans=ret;
      cout<<"Case #"<<t<<": "<<ans<<endl;
    }
  return 0 ;
}
