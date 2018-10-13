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
const int iter=1400,N=52;
const db EPS=1e-12;
db dp[2][3*N][3*N][3*N],p[N],ans[N];
bool vis[2][3*N][3*N][3*N];
struct node
{
  int l,r,ind;
  node(){}
  node(int l1,int r1,int ind1)
  {
    l=l1,r=r1,ind=ind1;
  }
};
queue<node> q;
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n,K;
  while(cin>>n>>K)
    {
      rep(i,1,n) cin>>p[i];
      rep(i,1,n+1) ans[i]=0.0;
      dp[0][K+n][K+n][K+n]=1.0;
      vis[0][K+n][K+n][K+n]=true;
      int curr=1;
      q.push(node(K+n,K+n,K+n));
      while(!q.empty())
	{
	  int bit=(curr&1);
	  queue<node> tmp;
	  while(!q.empty())
	    {
	      auto it=q.front();
	      q.pop();
	      db val=dp[1-bit][it.l][it.r][it.ind];
	      dp[1-bit][it.l][it.r][it.ind]=0.0;
	      vis[1-bit][it.l][it.r][it.ind]=false;
	      if(it.r-it.l+1==n)//this is end of this node
		{
		  ans[1+(it.ind-1)%n]+=val;
		  continue;
		}
	      if(it.ind%n==0) continue;
	      if(curr==iter-1) continue;
	      //move left
	      db val1=val*(1.0-p[1+(it.ind-1)%n]);
	      db val2=val*p[1+(it.ind-1)%n];
	      if(val1<EPS) val1=0.0;
	      if(val2<EPS) val2=0.0;
	      if(val1!=0.0)
		{
		  if(it.ind==it.l)
		    {
		      dp[bit][it.l-1][it.r][it.ind-1]+=val1;
		      if(!vis[bit][it.l-1][it.r][it.ind-1])
			{
			  tmp.push(node(it.l-1,it.r,it.ind-1));
			  vis[bit][it.l-1][it.r][it.ind-1]=true;
			}
		    }
		  else
		    {
		      dp[bit][it.l][it.r][it.ind-1]+=val1;
		      if(!vis[bit][it.l][it.r][it.ind-1])
			{
			  tmp.push(node(it.l,it.r,it.ind-1));
			  vis[bit][it.l][it.r][it.ind-1]=true;
			}
		    }
		}
	      //move right
	      if(val2!=0.0)
		{
		  if(it.ind==it.r)
		    {
		      dp[bit][it.l][it.r+1][it.ind+1]+=val2;
		      if(!vis[bit][it.l][it.r+1][it.ind+1])
			{
			  tmp.push(node(it.l,it.r+1,it.ind+1));
			  vis[bit][it.l][it.r+1][it.ind+1]=true;
			}
		    }
		  else
		    {
		      dp[bit][it.l][it.r][it.ind+1]+=val2;
		      if(!vis[bit][it.l][it.r][it.ind+1])
			{
			  tmp.push(node(it.l,it.r,it.ind+1));
			  vis[bit][it.l][it.r][it.ind+1]=true;
			}
		    }
		}
	    }
	  curr++;
	  swap(q,tmp);
	}
      cout<<setprecision(10)<<fixed<<ans[n]<<endl;
    }
  return 0 ;
}
