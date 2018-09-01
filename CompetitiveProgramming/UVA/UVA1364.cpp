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
ll c[N];
vi v10,v01,v11;
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n;
  cin>>n;
  rep(i,1,n+1) cin>>c[i];
  string a,b;
  cin>>a>>b;
  rep(i,1,n+1)
    {
      if(a[i]==b[i])
	{
	  if(a[i]=='1') v11.pb(i);
	}
      else
	{
	  if(a[i]=='1') v10.pb(i);
	  else v01.pb(i);
	}
    }
  sort(all(v01),[](int i,int j){return c[i]<c[j];});
  sort(all(v10),[](int i,int j){return c[i]<c[j];});
  sort(all(v11),[](int i,int j){return c[i]<c[j];});
  reverse(all(v11)); reverse(all(v10));
  ll tot11=0,tot10=0,tot01=0;
  for(auto it:v11) tot11+=it;
  for(auto it:v10) tot10+=it;
  for(auto it:v01) tot01+=it;
  ll cost10=(ll)sz(v10)*sumv10,cost01=0;
  rep(i,0,sz(v10))
    cost10-=(ll)v10[i]*(sz(v10)-i);
  rep(i,0,sz(v01))
    cost01+=(ll)v01[i]*(sz(v01)-i);
  ll ans=LLONG_MAX;
  ll sumsofar=0;
  ll tmp=0;
  rep(j,0,sz(v11))
    {
      sumsofar+=v11[j];
      ll curr=0;
      tmp+=tot11-sumsofar;
      curr=tot10*(j+1)+tmp+(tot11-sumsofar)*sz(v10)+cost10+(tot11-sumsofar)*sz(v01)+cost01+tot01*(j+1)+tmp+sumsofar;
      ans=min(ans,curr);
    }
  ans=min(ans,tot11*(sz(v10)+sz(v01))+cost01+cost10);
  cout<<ans<<endl;
  return 0 ;
}
