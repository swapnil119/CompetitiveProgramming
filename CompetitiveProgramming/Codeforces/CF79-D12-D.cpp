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
const int N=10005;
bool a[N],b[N],vis[(1<<20)+100];
vi setbits;
int d[25][N],dp[(1<<20)+100];
vi gaps;
int fun(int mask)
{
  if(!mask) return 0;
  if(dp[mask]!=-1) return dp[mask];
  if(vis[mask]) return N;
  vis[mask]=true;
  int ans=N;
  int ind;
  rep(i,0,sz(setbits))
    if(mask&(1<<i))
      {
	ind=i;
	break;
      }
  rep(j,ind+1,sz(setbits))
    ans=min(ans,fun(mask^(1<<ind)^(1<<j))+d[ind][setbits[j]]);
  return dp[mask]=ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  memset(dp,-1,sizeof(dp));
  int n,k,l;
  cin>>n>>k>>l;
  rep(i,1,k+1)
    {
      int x;
      cin>>x; a[x]=true;
    }
  rep(i,0,n+1)
    {
      if(a[i]!=a[i+1]) b[i]=true,setbits.pb(i);
      else b[i]=false;
    }
  rep(i,1,l+1)
    {
      int x;
      cin>>x; gaps.pb(x);
    }
  sort(all(gaps));
  gaps.erase(unique(all(gaps)),gaps.end());
  int ind=0;
  for(int x:setbits)
    {
      queue<int> q;
      q.push(x);
      rep(i,0,n+1) d[ind][i]=N;
      d[ind][x]=0;
      while(!q.empty())
	{
	  int curr=q.front();
	  q.pop();
	  for(int y:gaps)
	    {
	      if(curr-y>=0 && d[ind][curr-y]==N)
		d[ind][curr-y]=d[ind][curr]+1,q.push(curr-y);
	      if(curr+y<=n && d[ind][curr+y]==N)
		d[ind][curr+y]=d[ind][curr]+1,q.push(curr+y);
	    }
	}
      ind++;
    }
  int sz=sz(setbits);
  int ans=fun((1<<sz)-1);
  if(ans>=N) ans=-1;
  cout<<ans<<endl;
  return 0 ;
}
