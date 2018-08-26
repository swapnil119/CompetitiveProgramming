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
const int N=300005;
int x[N],ind[N];
ll pre[N];
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,k;
  cin>>n;
  rep(i,1,n+1) cin>>x[i],ind[i]=i;
  cin>>k;
  sort(ind+1,ind+n+1,[](int i,int j){return x[i]<x[j];});
  rep(i,1,n+1) pre[i]=x[ind[i]]+pre[i-1];
  int indans=1;
  ll curr=0;
  rep(i,1,k+1) curr+=(ll)x[ind[i]]*(i-1)-pre[i-1];
  ll mn=curr;
  rep(i,k+1,n+1)
    {
      curr-=(pre[i-1]-pre[i-k])-(ll)(k-1)*x[ind[i-k]];
      curr+=(ll)(k-1)*x[ind[i]]-(pre[i-1]-pre[i-k]);
      if(curr<mn) mn=curr,indans=i-k+1;
    }
  rep(i,indans,indans+k) cout<<ind[i]<<" "; cout<<endl;
  return 0 ;
}
