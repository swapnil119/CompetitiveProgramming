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
const int N=30;
int p[]={2,3,5,7,11,13,17,19,23,29};
int cnt[10];
int calc(int x,int y)
{
  int ans=0,pw=y;
  while(x/pw)
    {
      ans+=x/pw;
      pw*=y;
    }
  return ans;
}
vector<pair<string,bool> > v;
vector<vector<string> > ans;
void fun(int ind,int n,int k,bool done=false)
{
  if(n%k==0) done=true;
  if(ind==n)
    {
      vector<string> tmp;
      for(auto it:v) tmp.pb(it.fi);
      ans.pb(tmp);
      return;
    }
  rep(i,0,sz(v))
    {
      if(sz(v[i].fi)==k) continue;
      if(v[i].se==true && sz(v[i].fi)==(n%k)) continue;
      v[i].fi+=(char)(ind+'A');
      fun(ind+1,n,k,done);
      v[i].fi.erase(sz(v[i].fi)-1);
    }
  int grp=(n+k-1)/k;
  if(sz(v)==grp) return;
  if(done)
    {
      string tmp;
      tmp+=(char)(ind+'A');
      v.pb(mp(tmp,false));
      fun(ind+1,n,k,done);
      v.pop_back();
    }
  else
    {
      string tmp;
      tmp+=(char)(ind+'A');
      v.pb(mp(tmp,true));
      fun(ind+1,n,k,true);
      v.pop_back();
      if(sz(v)<grp-1)
	{
	  string tmp;
	  tmp+=(char)(ind+'A');
	  v.pb(mp(tmp,false));
	  fun(ind+1,n,k,done);
	  v.pop_back();
	}
    }
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  string s;
  while(cin>>s)
    {
      if(s[0]=='E') break;
      int n,k;
      cin>>n>>k;
      int grp=(n+k-1)/k;
      rep(i,0,10) cnt[i]=calc(n,p[i]);
      rep(i,0,10) cnt[i]-=(n/k)*calc(k,p[i])+calc(n%k,p[i]);
      rep(i,0,10) cnt[i]-=calc(n/k,p[i]);
      unsigned ll ans=1;
      rep(i,0,10)
	rep(j,0,cnt[i]) ans*=p[i];
      cout<<ans<<endl;
      if(s[0]=='C') continue;
      ::ans.clear();
      fun(0,n,k);
      assert(sz(v)==0);
      sort(all(::ans));
      for(auto it:(::ans))
	{
	  rep(j,0,sz(it)-1) cout<<it[j]<<" ";
	  cout<<it.back()<<endl;
	}
      assert(sz(::ans)==ans);
    }
  return 0 ;
}
