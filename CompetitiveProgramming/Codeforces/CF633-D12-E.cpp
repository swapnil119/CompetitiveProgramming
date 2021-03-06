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
const int N=1000005,L=N*10;
int v[N],c[N],p[N],bit[L],bit2[L],val[N];
void update1(int i,int val)
{
  while(i)
    {
      bit[i]=min(bit[i],val);
      i-=(i&(-i));
    }
}
int query1(int i)
{
  int ans=L;
  while(i<L)
    {
      ans=min(ans,bit[i]);
      i+=(i&(-i));
    }
  return ans;
}
void update2(int i,int val)
{
  while(i<L)
    {
      bit2[i]=min(bit2[i],val);
      i+=(i&(-i));
    }
}
int query2(int i)
{
  int ans=L;
  while(i)
    {
      ans=min(ans,bit2[i]);
      i-=(i&(-i));
    }
  return ans;
}
/*first calculate optimal answer for each li using binary search on answer. Then simple probability*/
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,k;
  cin>>n>>k;
  rep(i,0,L) bit[i]=bit2[i]=N;
  rep(i,1,n+1) cin>>v[i];
  rep(i,1,n+1) cin>>c[i];
  vi v;
  repv(i,1,n+1)//calculate optimal answer for t
    {
      update1(min((int)1e7,100*::v[i]),i);
      update2(c[i],i);
      int low=1,high=1e7;
      while(low<high)
	{
	  int mid=(low+high+1)>>1;
	  int l1=query1(mid);//first index which has value greater equal to this
	  int l2=query2(mid-1);//first index which has value less than this
	  l2=min(l2,n+1); l1=min(l1,n+1);
	  if(l1>=l2) high=mid-1;
	  else low=mid;
	}
      val[i]=high;
      v.pb(val[i]);
    }
  sort(all(v));
  db ans=0.0,curr=(db)k/(db)n,num=n-k+1,den=n;
  rep(i,1,n-k+2)
    {
      ans+=(db)v[i-1]*curr;
      num--; den--;
      curr*=(num/den);
    }
  cout<<setprecision(10)<<fixed<<ans<<endl;
  return 0 ;
}
