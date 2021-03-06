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
//using alien's trick
const db inf=(double)6e18;
const int N=200005,iter=105;
ll c[N];
db pre[N],pre2[N],dp[N],pre3[N];
#define ddi pair<pair<db,db>,int> 
int st,en;
ddi arr[N];
void addline(db m,db c,int ind)
{
  arr[en]=mp(mp(m,c),ind);
  while(st+1<en && (arr[en-1].fi.se-arr[en-2].fi.se)*(arr[en].fi.fi-arr[en-1].fi.fi)<=(arr[en-1].fi.se-arr[en].fi.se)*(arr[en-2].fi.fi-arr[en-1].fi.fi))
    arr[en-1]=arr[en],en--;
  en++;
}
pair<db,int> query(db x)
{
  while(st+1<en && arr[st+1].fi.se-arr[st].fi.se>=x*(arr[st].fi.fi-arr[st+1].fi.fi)) st++;
  return mp(arr[st].fi.fi*x+arr[st].fi.se,arr[st].se);
}
int n,cnt[N];
int fun(db mid)
{
  //b->pre[i]*pre3[i]-pre2[i]+dp[i]
  //m->-pre[i]
  st=en=0;
  addline(0,0,0);
  rep(i,1,n+1)
    {
      auto it=query(pre3[i]);
      cnt[i]=cnt[it.se]+1;
      dp[i]=-it.fi+pre2[i]+mid;
      addline(pre[i],-dp[i]-(pre[i]*pre3[i])+pre2[i],i);
    }
  return cnt[n];
}
int main()
{
  int k,i,j;
  cin>>n>>k;
  k=min(k,n);
  rep(i,1,n+1)
    {
      cin>>c[i];
      pre[i]=pre[i-1]+c[i];
      pre3[i]=pre3[i-1]+1.0/(double)c[i];
    }
  rep(i,1,n+1)
    pre2[i]=pre2[i-1]+pre[i]/(db)c[i];
  db low=0.0,high=1e18;
  rep(i,0,iter)
    {
      db mid=(low+high)/2.0;
      if(fun(mid)>k) low=mid;
      else high=mid;
    }
  int tmp=fun(high);
  cout<<setprecision(10)<<fixed;
  cout<<dp[n]-high*tmp<<endl;
  return 0;
}
