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
const int N=200005;
set<int> v[N],ad[N];
int a[N],b[N],deg[N],tmp[N],ret[N];
bool vis[N];
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,m,k;
  cin>>n>>m>>k;
  rep(i,1,m+1)
    {
      cin>>a[i]>>b[i];
      v[a[i]].insert(b[i]); v[b[i]].insert(a[i]);
      deg[a[i]]++; deg[b[i]]++;
    }
  rep(i,1,n+1) tmp[i]=deg[i];
  queue<int> q;
  rep(i,1,n+1)
    {
      if(deg[i]<k) q.push(i),vis[i]=true;
    }
  while(!q.empty())
    {
      int u=q.front();
      q.pop();
      for(int v1:v[u])
	{
	  if(vis[v1]) continue;
	  deg[v1]--;
	  if(deg[v1]<k)
	    {
	      assert(deg[v1]==k-1);
	      vis[v1]=true;
	      q.push(v1);
	    }
	}
    }
  rep(i,1,n+1) deg[i]=tmp[i];
  int ans=0;
  rep(i,1,n+1)
    {
      if(!vis[i])
	{
	  ans++;
	  for(int v1:v[i])
	    {
	      if(!vis[v1])
		ad[i].insert(v1);
	    }
	}
    }
  repv(i,1,m+1)
    {
      ret[i]=ans;
      int x=a[i],y=b[i];
      if(vis[x] || vis[y])
	continue;
      ad[x].erase(y); ad[y].erase(x);
      if(sz(ad[x])<k) q.push(x),vis[x]=true;
      if(sz(ad[y])<k) q.push(y),vis[y]=true;
      while(!q.empty())
	{
	  int u=q.front();
	  q.pop();
	  ans--;
	  for(int v1:ad[u])
	    {
	      if(vis[v1]) continue;
	      ad[v1].erase(u); 
	      if(sz(ad[v1])<k)
		{
		  vis[v1]=true;
		  q.push(v1);
		}
	    }
	}
    }
  rep(i,1,m+1) cout<<ret[i]<<endl;
  return 0 ;
}
