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
const int N=1005;
class MonstersAndBunnies
{
  db dp[N][N];
  bool vis[N][N];
public:
  db fun(int m,int b)
  {
    if(m==0) return 1.0;
    if(vis[m][b]) return dp[m][b];
    vis[m][b]=true;
    db den=(m+b)*(m+b+1.0);
    den=1.0/den;
    db pbb=0.0,pbi=0.0,pmm=0.0,pmi=0.0,pmb=0.0;
    pbb=den*b*(b-1.0);//bunny bunny
    pbi=2.0*den*b;//bunny and me
    pmm=den*m*(m-1.0);//monster and monster
    pmi=2.0*den*m;//monster and me
    pmb=2.0*den*m*b;//bunny and monster
    db ans=0.0,sum=0.0;
    //kill bunnies
    if(b) sum+=pbi*fun(m,b-1);
    if(m>=2) sum+=pmm*fun(m-2,b);
    if(b && m) sum+=pmb*fun(m,b-1);
    ans=sum/(1.0-pbb);
    //don't kill bunnies
    sum=0.0;
    if(m>=2) sum+=pmm*fun(m-2,b);
    if(b && m) sum+=pmb*fun(m,b-1);
    ans=max(ans,sum/(1.0-pbb-pbi));
    return dp[m][b]=ans;
  }
  db survivalProbability(int m,int b)
  {
    memset(vis,false,sizeof(vis));
    return fun(m,b);
  }
};
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  MonstersAndBunnies x;
  int m,b;
  cin>>m>>b;
  cout<<setprecision(10)<<fixed<<x.survivalProbability(m,b)<<endl;
  return 0 ;
}
