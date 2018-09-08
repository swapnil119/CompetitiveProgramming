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
const int N=18,N1=(1<<N);
int h,w,n,mx[N][N];//mx is maximum overlap of i and j
bool sub[N][N1];//sub is whether i is substring of any one of the mask
string s[N];
ii dp[N][N1];//min. x,y s.t mask strings are filled ending in i
vi common[N][N];//strings which occur when ind and joinind occur together
int getnewmask(int mask,int ind,int joinind)
{
  mask|=(1<<joinind);
  for(int x:common[ind][joinind])
    mask|=(1<<x);
  return mask;
}
vector<pair<int,ii> > ans;
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  cin>>h>>w>>n;
  rep(i,0,n) cin>>s[i];
  rep(i,0,n)
    rep(j,0,n)
    {
      if(i==j) continue;
      rep(k,0,sz(s[i]))//find maximum overlap
	{
	  int len=sz(s[i])-k;
	  if(sz(s[j])>=len && s[i].substr(k,len)==s[j].substr(0,len))
	    {
	      mx[i][j]=len;
	      break;
	    }
	}
      if(mx[i][j])//check which strings occur when they overlap, or present in j
	{
	  string tmp=s[i]+s[j];
	  rep(k,0,n)
	    {
	      if(k==i || k==j) continue;
	      rep(l,0,sz(tmp))
		{
		  int len=sz(s[k]);
		  if(l+len-1<sz(s[i])) continue;
		  if(l+len>=sz(tmp)) break;
		  if(tmp.substr(l,len)==s[k])
		    {
		      common[i][j].pb(k);
		      break;
		    }
		}
	    }
	}
      if(sz(s[j])<sz(s[i])) continue;
      rep(k,0,sz(s[j]))//check whether i occurs in j
	{
	  int len=sz(s[i]);
	  if(k+len-1>=sz(s[j])) break;
	  if(s[j].substr(k,len)==s[i])
	    {
	      sub[i][(1<<j)]=true;
	      break;
	    }
	}
    }
  rep(i,0,(1<<n))
    {
      vi rem,present;
      rep(j,0,n)
	{
	  if(i&(1<<j)) present.pb(j);
	  else rem.pb(j);
	}
      for(int x:rem)
	{
	  for(int y:present)
	    if(sub[x][(1<<y)])
	      {
		sub[x][i]=true;
		break;
	      }
	}
    }
  rep(i,0,n)
    if(sz(s[i])>w)
      {
	cout<<"impossible"<<endl;
	return 0;
      }
  rep(j,0,n)
    rep(i,0,(1<<n)) dp[j][i]=mp(h+1,w+1);
  rep(i,0,(1<<n))
    if(__builtin_popcount(i)==1)
      {
	rep(j,0,n)
	  if(i&(1<<j))
	    dp[j][i]=mp(1,sz(s[j]));
      }
  rep(i,1,(1<<n))
    {
      if(__builtin_popcount(i)==1) continue;
      vi rem;
      rep(j,0,n)
	if(i&(1<<j)) rem.pb(j);
      int newmask=i;
      for(int x:rem) if(sub[x][i]) newmask|=(1<<x);
      rep(j,0,n)//ending in jth string
	{
	  if(!(i&(1<<j))) continue;
	  for(int x:rem)
	    {
	      if(sub[x][i]) continue;
	      int tmp=getnewmask(newmask,j,x);
	      auto curr=dp[j][i];
	      if(w-curr.se>=sz(s[x])-mx[j][x])
		dp[x][tmp]=min(dp[x][tmp],mp(curr.fi,curr.se+sz(s[x])-mx[j][x]));
	      else
		dp[x][tmp]=min(dp[x][tmp],mp(curr.fi+1,sz(s[x])));
	    }
	}
    }
  bool ok=false;
  int prev=-1;
  ii mn=mp(h+1,w+1);
  rep(i,0,n)
    if(dp[i][(1<<n)-1]<=mp(h,w))
      {
	ok=true;
	if(dp[i][(1<<n)-1]<mx)
	  dp[i][(1<<n)-1]=mx,prev=i;
  if(!ok)
    {
      cout<<"impossible"<<endl;
      return 0;
    }
  assert(prev!=-1);
  ans.pb(mp(prev,dp[prev][(1<<n)-1]));
  int mask=(1<<n)-1;
  mask^=(1<<prev);
  //remove all strings from mask, which have already occured
  rep(i,0,n)
    {
      if(i==prev) continue;
      int nxt=(1<<n)-1; nxt^=(1<<i);
      if(dp[prev][(1<<n)-1]==dp[prev][nxt])
	mask^=(1<<i);
    }
  while(mask)
    {
      rep(i,0,n)
	{
	  if(!(mask&(1<<i))) continue;
	  auto curr=dp[i][mask];
	  int nxt=getnextmask(mask,i,prev);
	  if(w-curr.se>=sz(s[prev])-mx[j][prev])
	    {
	      if(dp[i][mask]==mp(dp[prev][nxt].fi,dp[prev][nxt].se-sz(s[prev])+mx[i][prev]))
		{
		  rep(j,0,n)
		    {
		      if(!(mask&(1<<j))) continue;
		    }
		}
	    }
	    dp[x][tmp]=min(dp[x][tmp],mp(curr.fi+curr.se+sz(s[x])-mx[j][x]));
	  else
	    dp[x][tmp]=min(dp[x][tmp],mp(curr.fi+1,sz(s[x])));
	}
    }
  return 0 ;
}
