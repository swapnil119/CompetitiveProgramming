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
//https://discuss.codechef.com/questions/4055/buying-editorial
const int N=50005,W=42,K=22;
const ll inf=(ll)1e16;
int a[N],ind[N],cnt[K];
ll dp[K][K][4*K*W];//ind,sum of remove and insert, sum of numbers %k
pair<ll,int> val[K*W];
vi v[K];
vector<ll> pre[K],premod[K];
bool mark[N];
int n,m,k;
inline pair<ll,int> calc(int idx,int l,int r)
{
  if(l>r) return mp(0,0);
  if(!l) return mp(pre[idx][r],premod[idx][r]);
  int tmp=premod[idx][r]-premod[idx][l-1];
  if(tmp<0) tmp+=k;
  return mp(pre[idx][r]-pre[idx][l-1],tmp);
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int t;
  cin>>t;
  while(t--)
    {
      cin>>n>>m>>k;
      rep(i,0,k) v[i].clear();
      rep(i,1,n+1)
	{
	  mark[i]=false; ind[i]=i;
	  cin>>a[i];
	  v[a[i]%k].pb(i);
	}
      rep(i,0,k)
	sort(all(v[i]),[](int x,int y){return a[x]<a[y];});
      sort(ind+1,ind+n+1,[](int x,int y){return a[x]<a[y];});
      ll currans=0;
      rep(i,1,m+1) mark[ind[i]]=true,currans+=a[ind[i]];
      if(currans%k==0)
	{
	  cout<<currans<<endl;
	  continue;
	}
      rep(i,0,k)
	{
	  cnt[i]=0;
	  pre[i].clear(); premod[i].clear();
	  for(int x:v[i])
	    {
	      if(!mark[x]) break;
	      cnt[i]++;
	    }
	  ll tmp=0;
	  for(int x:v[i])
	    {
	      tmp+=a[x];
	      pre[i].pb(tmp);
	      premod[i].pb(tmp%k);
	    }
	}
      rep(i,0,K) rep(j,0,K) rep(x,0,4*K*W) dp[i][j][x]=inf;
      dp[0][currans%k][2*K*W]=0;
      rep(idx,0,k)
	{
	  const int tot=sz(v[idx]),lim=2*k-2;
	  const int l=max(-cnt[idx],-lim),r=min(tot-cnt[idx],lim);
	  rep(i,l,r+1)
	    {
	      pair<ll,int> tmp1;
	      if(i>=0) tmp1=calc(idx,cnt[idx],cnt[idx]+i-1);
	      else
		{
		  tmp1=calc(idx,cnt[idx]+i,cnt[idx]-1);
		  tmp1=mp(-tmp1.fi,((tmp1.se==0)?0:k-tmp1.se));
		}
	      val[i-l]=tmp1;
	    }
	  rep(currsum,0,k)
	    {
	      rep(delta,-lim*idx,lim*idx+1)
		{
		  const int tmp=delta+2*K*W;
		  rep(i,l,r+1)
		    {
		      auto tmp1=val[i-l];
		      int nxt=currsum+tmp1.se;
		      if(nxt>=k) nxt-=k;
		      dp[idx+1][nxt][tmp+i]=min(dp[idx+1][nxt][tmp+i],dp[idx][currsum][tmp]+tmp1.fi);
		    }
		}
	    }
	}
      ll ans=dp[k][0][2*K*W];
      if(ans>=inf/2) ans=-1;
      else ans+=currans;
      cout<<ans<<endl;
    }
  return 0 ;
}
