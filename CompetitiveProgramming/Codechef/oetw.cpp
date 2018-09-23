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
const int N=2000005;
int pre[N],a[N],cnt[2*N];
bool mark[2*N],m1[2*N],m2[2*N];
vi v1,v2;
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int t;
  cin>>t;
  while(t--)
    {
      v1.clear(); v2.clear();
      int n;
      cin>>n;
      rep(i,1,n+1) cin>>a[i],pre[i]=pre[i-1]+a[i];
      rep(i,1,n+1) mark[pre[i]]=true;
      rep(i,1,n+1) v1.pb(pre[i]),v2.pb(pre[i]);
      rep(i,1,n)
	{
	  if(a[i]==1)
	    {
	      vi tmp;
	      for(int x:v1)
		{
		  m1[x]=true;
		  if(x-1>0 && !m1[x-1]) mark[x-1]=true,tmp.pb(x-1);
		}
	      swap(v1,tmp);
	    }
	  else
	    {
	      vi tmp;
	      for(int x:v2)
		{
		  m2[x]=true;
		  if(x-2>0 && !m2[x-2]) mark[x-2]=true,tmp.pb(x-2);
		}
	      swap(tmp,v2);
	    }
	}
      int ans=0;
      rep(i,1,2*n+1) ans+=mark[i];
      cout<<ans<<endl;
      rep(i,1,2*n+1) mark[i]=m1[i]=m2[i]=false;
    }
  return 0 ;
}
