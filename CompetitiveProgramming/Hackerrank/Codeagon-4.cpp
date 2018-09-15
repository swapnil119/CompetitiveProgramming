#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")

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

const int mod=1e9+7;
const int N=305;
int add(int x,int y)
{
  x+=y;
  if(x>=mod) x-=mod;
  if(x<0) x+=mod;
  return x;
}
int dp[3][N][N][N];
string a,b,c;
int fun(int type,int x,int y,int z)
{
  if(z==sz(c)) return 1;
  if(x==sz(a) && y==sz(b)) return 0;
  if(dp[type][x][y][z]!=-1) return dp[type][x][y][z];
  int ans=0;
  if(type!=2 && x<sz(a))
    {
      if(a[x]==c[z]) ans=add(ans,fun(0,x+1,y,z+1));
      ans=add(ans,fun(1,x+1,y,z));
    }
  if(type!=1 && y<sz(b))
    {
      if(b[y]==c[z]) ans=add(ans,fun(0,x,y+1,z+1));
      ans=add(ans,fun(2,x,y+1,z));
    }
  return dp[type][x][y][z]=ans;
}
int fun2(int x,int y)
{
  if(y==sz(c)) return 1;
  if(x==sz(a)) return 0;
  if(dp[0][0][x][y]!=-1) return dp[0][0][x][y];
  int ans=fun2(x+1,y);
  if(a[x]==c[y]) ans=add(ans,fun2(x+1,y+1));
  return dp[0][0][x][y]=ans;
}
int fun3(int x,int y)
{
  if(y==sz(c)) return 1;
  if(x==sz(b)) return 0;
  if(dp[0][0][x][y]!=-1) return dp[0][0][x][y];
  int ans=fun3(x+1,y);
  if(b[x]==c[y]) ans=add(ans,fun3(x+1,y+1));
  return dp[0][0][x][y]=ans;
}
int main()
{
  memset(dp,-1,sizeof(dp));
  cin>>a>>b>>c;
  int ans=fun(0,0,0,0);
  memset(dp,-1,sizeof(dp));
  ans=add(ans,-fun2(0,0));
  memset(dp,-1,sizeof(dp));
  ans=add(ans,-fun3(0,0));
  cout<<ans<<endl;
  return 0; 
}
