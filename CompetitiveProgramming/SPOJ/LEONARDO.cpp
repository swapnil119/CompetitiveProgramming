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
/*odd cyles can be there. Because a permutation with odd cycle produces corresponding odd cycle. A permutation with even cycle produces 2 even cycles of half length, so each length of even cycles should be even number of times.*/
bool vis[26];
int c[30];
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int t;
  cin>>t;
  while(t--)
    {
      string s;
      cin>>s;
      rep(i,0,26) vis[i]=false;
      rep(i,0,30) c[i]=0;
      int cnteven=0;
      rep(i,0,sz(s))
	{
	  if(vis[i]) continue;
	  int curr=i,cnt=0;
	  while(!vis[curr])
	    {
	      vis[curr]=true; cnt++;
	      int d=s[curr]-'A';
	      curr=d;
	    }
	  if(cnt%2==0) c[cnt]++;
	}
      bool ok=true;
      rep(i,0,30) if(c[i]&1) ok=false;
      if(!ok) cout<<"No"<<endl;
      else cout<<"Yes"<<endl;
    }
  return 0 ;
}
