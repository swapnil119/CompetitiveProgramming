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
//add edge between rows in the columns where they are 1. If they belong to same component, they can be made from other columns
const int N=100005;
int p[N];
int finda(int x)
{
  if(p[x]==x) return x;
  return p[x]=finda(p[x]);
}
int join(int x,int y)
{
  int x1=finda(x),y1=finda(y);
  if(x1==y1) return 0;
  p[y1]=x1;
  return 1;
}
vi v[N];
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int m,n;
  cin>>m>>n;
  rep(i,1,m+1)
    {
      int k;
      cin>>k;
      rep(j,1,k+1)
	{
	  int x;
	  cin>>x;
	  v[x].pb(i);
	}
    }
  int ans=0;
  rep(i,1,m+1) p[i]=i;
  rep(i,1,n+1)
    ans+=join(v[i][0],v[i][1]);
  cout<<ans<<endl;
  return 0 ;
}
