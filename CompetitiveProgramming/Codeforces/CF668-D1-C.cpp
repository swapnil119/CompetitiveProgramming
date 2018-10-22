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
//p1(i)+p2(i)=ai+bi and p1(1)p2(1)=a1
const int N=100005;
const db EPS=1e-9;
db mx[N],mn[N];
db a[N],b[N];
db fun(db b,db c)
{
  db dis=b*b-c*4.0;
  if(abs(dis)<EPS) dis=0.0;
  dis=sqrt(dis);
  return (dis-b)/2.0;
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n;
  cin>>n;
  rep(i,1,n+1) cin>>mx[i];
  rep(i,1,n+1) cin>>mn[i];
  a[1]=fun(-mx[1]-mn[1],mx[1]);
  b[1]=mx[1]+mn[1]-a[1];
  rep(i,2,n+1)
    {
      mx[i]+=mx[i-1]; mn[i]+=mn[i-1];
      a[i]=fun(-mx[i]-mn[i],mx[i]);
      b[i]=mx[i]+mn[i]-a[i];
    }
  repv(i,2,n+1) a[i]-=a[i-1],b[i]-=b[i-1];
  cout<<setprecision(10)<<fixed;
  rep(i,1,n+1) cout<<a[i]<<" "; cout<<endl;
  rep(i,1,n+1) cout<<b[i]<<" "; cout<<endl;
  return 0 ;
}
