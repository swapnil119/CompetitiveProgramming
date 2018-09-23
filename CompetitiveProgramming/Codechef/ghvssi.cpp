#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ll long long
#define db long double
#define ii pair<ll,ll>
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
const int N=305;
int a[N];
int dp[4][N][N][N],cnt[4];
int fun(int sum,int rem1,int rem2,int rem3)//return 1 if previous player won
{
  if(sum==2) return 0;//lose
  if(rem1+rem2+rem3==0) return 1;//previous player won
  if(dp[sum][rem1][rem2][rem3]!=-1) return dp[sum][rem1][rem2][rem3];
  bool win=false;
  if(rem1)//take x%4=1 odd
    win|=fun((sum+1)%4,rem1-1,rem2,rem3);
  if(rem2)//take bad even
    win|=fun((sum+2)%4,rem1,rem2-1,rem3);
  if(rem3)//take x%4=3 odd
    win|=fun((sum+3)%4,rem1,rem2,rem3-1);
  return dp[sum][rem1][rem2][rem3]=1-win;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  memset(dp,-1,sizeof(dp));
  int t;
  cin>>t;
  while(t--)
    {
      int n;
      cin>>n;
      rep(i,0,4) cnt[i]=0;
      rep(i,1,n+1) cin>>a[i],cnt[a[i]%4]++;
      int ans=fun(0,cnt[1],cnt[2],cnt[3]);
      if(cnt[0]%2==0)//win and lose are reversed
	{
	  if(ans==0) cout<<"Ghayeeth"<<endl;
	  else cout<<"Siroj"<<endl;
	}
      else
	{
	  if(ans==1) cout<<"Ghayeeth"<<endl;
	  else cout<<"Siroj"<<endl;
	}
    }
  return 0 ;
}
