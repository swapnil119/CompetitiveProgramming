#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long
#define db double
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
const int N=42,C=52;
class RandomColoring
{
  db dp[N][C][C][C],pre[C][C][C];
public:
  db getsum(int x1,int y1,int z1,int x2,int y2,int z2)
  {
    return (pre[x2][y2][z2]-pre[x1-1][y2][z2]-pre[x2][y1-1][z2]-pre[x2][y2][z1-1]+pre[x1-1][y1-1][z2]+pre[x1-1][y2][z1-1]+pre[x2][y1-1][z1-1]-pre[x1-1][y1-1][z1-1]);
  }
  bool check(int x1,int y1,int z1,int x2,int y2,int z2,int d1,int d2)
  {
    if(abs(x1-x2)>d2 || abs(y1-y2)>d2 || abs(z1-z2)>d2) return false;
    if(abs(x1-x2)<d1 && abs(y1-y2)<d1 && abs(z1-z2)<d1) return false;
    return true;
  }
  void calcpre(int ind,int R,int G,int B)
  {
    rep(i,1,R+1)
      rep(j,1,G+1)
      rep(k,1,B+1)
      pre[i][j][k]=pre[i-1][j][k]+pre[i][j-1][k]+pre[i][j][k-1]-pre[i-1][j-1][k]-pre[i-1][j][k-1]-pre[i][j-1][k-1]+pre[i-1][j-1][k-1]+dp[ind][i][j][k];
  }
  db getProbability(int n,int R,int G,int B,int r,int g,int b,int d1,int d2)
  {
    r++; g++; b++;
    memset(pre,0,sizeof(pre));
    rep(i,1,R+1)
      rep(j,1,G+1)
      rep(k,1,B+1)
      {
	if(check(i,j,k,r,g,b,d1,d2))
	  dp[n][i][j][k]=0.0;
	else
	  dp[n][i][j][k]=1.0;
      }
    calcpre(n,R,G,B);
    repv(ind,1,n)
      {
	rep(i,1,R+1)
	  rep(j,1,G+1)
	  rep(k,1,B+1)
	  {
	    int x1,x2,y1,y2,z1,z2;
	    x1=max(1,i-d2); x2=min(R,i+d2);
	    y1=max(1,j-d2); y2=min(G,j+d2);
	    z1=max(1,k-d2); z2=min(B,k+d2);
	    int cnt=(x2-x1+1)*(y2-y1+1)*(z2-z1+1);
	    dp[ind][i][j][k]=getsum(x1,y1,z1,x2,y2,z2);
	    if(d1)
	      {
		x1=max(1,i-d1+1); x2=min(R,i+d1-1);
		y1=max(1,j-d1+1); y2=min(G,j+d1-1);
		z1=max(1,k-d1+1); z2=min(B,k+d1-1);
		cnt-=(x2-x1+1)*(y2-y1+1)*(z2-z1+1);
		dp[ind][i][j][k]-=getsum(x1,y1,z1,x2,y2,z2);
	      }
	    if(cnt)
	      dp[ind][i][j][k]/=((db)cnt);
	    else
	      dp[ind][i][j][k]=1.0;
	  }
	calcpre(ind,R,G,B);
      }
    return dp[1][r][g][b];
  }
};
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  RandomColoring x;
  int n,R,G,B,r,g,b,d1,d2;
  cin>>n>>R>>G>>B>>r>>g>>b>>d1>>d2;
  cout<<x.getProbability(n,R,G,B,r,g,b,d1,d2)<<endl;
  return 0 ;
}
