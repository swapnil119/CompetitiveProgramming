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
const int N=100005,L=26;
vi queries[N],inds[N],dp[N];
int nxt[L][N],pre[L][N];
int s2[N],l[N],r[N],timer,val[105],dpfrom[L][N],dpto[L][N];
int post[N];
int fun(int i,int j)
{
  if(i>j) return 0;
  auto it=lower_bound(all(inds[i]),j);
  assert(it!=inds[i].end()); assert(*it==j);
  int tmpind=it-inds[i].begin();
  return dp[i][tmpind];
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  string s;
  cin>>s; int n=sz(s);
  s="#"+s;
  rep(i,1,n+1) s2[i]=(int)(s[i]-'a');
  rep(i,0,26) nxt[i][n+1]=n+1;
  repv(i,1,n+1)
    {
      rep(j,0,26) nxt[j][i]=nxt[j][i+1];
      nxt[s2[i]][i]=i;
    }
  rep(i,1,n+1)
    {
      rep(j,0,26) pre[j][i]=pre[j][i-1];
      pre[s2[i]][i]=i;
    }
  int m;
  cin>>m;
  rep(i,1,m+1)
    {
      cin>>l[i]>>r[i];
      queries[l[i]].pb(r[i]);
      rep(j,0,L)//add this because when we get dpto for r[i], then this index won't be there
	{
	  int pr=pre[j][r[i]];
	  if(pr<r[i] && pr>=l[i])
	    queries[pr+1].pb(r[i]);
	}
    }
  repv(i,1,n+1)
    {
      int next=nxt[s2[i]][i+1];
      if(next!=n+1)//post[i] is xor of all substrings after partitioning with char s2[i]
	post[i]=(post[next]^fun(i+1,next-1));
      rep(j,0,L)
	{
	  int x=nxt[j][i];
	  if(x!=n+1 && x!=i)
	    inds[i].pb(x-1);
	}
      inds[i].pb(n);
      for(int x:queries[i]) inds[i].pb(x);
      sort(all(inds[i]));
      inds[i].erase(unique(all(inds[i])),inds[i].end());
      dp[i].resize(sz(inds[i]));
      int currind=-1;
      for(int x:inds[i])//inds[i] contain valid indexes for which we want to find the answer
	{
	  timer++; currind++;
	  rep(j,0,L)//remove jth char
	    {
	      int l1=nxt[j][i],r1=pre[j][x];
	      if(l1>x) continue;
	      int curr=0;
	      if(l1>i)//grundy for string from i to l1-1
		curr^=dpfrom[j][i];
	      if(r1<x)//grundy for string from r1+1 to x
		curr^=dpto[j][x];
	      curr^=(post[l1]^post[r1]);//exclude char of l1
	      val[curr]=timer;
	    }
	  int &ans=dp[i][currind];
	  while(val[ans]==timer) ans++;
	  if(x<n)//dpfrom[j][i] is grundy of string i to next(j)-1
	    {
	      if(nxt[s2[x+1]][i]==x+1)
		dpfrom[s2[x+1]][i]=ans;
	    }
	  if(i>1)//dpto[j][i] is grundy of string prev(j)+1 to i
	    {
	      if(pre[s2[i-1]][x]==i-1)
		dpto[s2[i-1]][x]=ans;
	    }
	}
    }
  rep(i,1,m+1)
    {
      int ans=fun(l[i],r[i]);
      cout<<((ans==0)?"Bob":"Alice")<<endl;
    }
  return 0 ;
}
