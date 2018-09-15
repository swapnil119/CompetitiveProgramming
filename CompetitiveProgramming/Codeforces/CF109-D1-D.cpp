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
const int N=100005;
bool mark[N];
vector<ii> ans;
map<ii,int> m;
map<int,ii> rev;
int a[N],val[N],pos[N];
ii b[N];
bool check(int x)
{
  while(x)
    {
      int tmp=x%10;
      if(tmp!=4 && tmp!=7) return false;
      x/=10;
    }
  return true;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n;
  cin>>n;
  rep(i,1,n+1) cin>>a[i],b[i]=mp(a[i],i),val[i]=i,pos[i]=i;
  sort(b+1,b+n+1);
  int special=-1;
  rep(i,1,n+1)
    {
      m[b[i]]=i;
      if(check(b[i].fi)) mark[b[i].se]=true,special=b[i].se;
      rev[i]=b[i];
    }
  if(special==-1)//no luck
    {
      rep(i,1,n+1)
	{
	  if(b[i].fi!=a[i])
	    {
	      cout<<-1<<endl;
	      return 0;
	    }
	}
      cout<<0<<endl;
      return 0;
    }
  //val[i] contains val[i] index at i,pos[i] is where is actual ith index
  rep(i,1,n+1)
    {
      ii curr=mp(a[val[i]],val[i]);//take element at this ind
      if(m[curr]==i) continue;
      auto it=rev[i];//get actual el. which should be here
      if(mark[val[i]] || mark[it.se])//one of them is special
	{
	  ans.pb(mp(i,pos[it.se]));
	  int tmp=val[i];
	  val[i]=it.se,val[pos[it.se]]=tmp;
	  swap(pos[tmp],pos[it.se]);
	}
      else
	{
	  //first swap i with special
	  ans.pb(mp(i,pos[special]));
	  int tmp=val[i];
	  val[i]=special; val[pos[special]]=tmp;
	  swap(pos[tmp],pos[special]);
	  //now swap special with actual
	  ans.pb(mp(i,pos[it.se]));
	  tmp=val[i];
	  val[i]=it.se,val[pos[it.se]]=tmp;
	  swap(pos[tmp],pos[it.se]);
	}
    }
  assert(sz(ans)<=2*n);
  cout<<sz(ans)<<endl;
  for(auto it:ans) cout<<it.fi<<" "<<it.se<<endl;
  return 0 ;
}
