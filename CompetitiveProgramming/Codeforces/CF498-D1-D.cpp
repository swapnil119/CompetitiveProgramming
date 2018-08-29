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
/* using sqrt decomposition, for each number from 0 to LC-1 compute what time will be spent for each block. On update, update 1 block. For query do brute on corner blocks, and for middle blocks use answer which is already computed*/
const int N=100005,sq=40,L=N/sq+50,LC=60;
int block[N];
int ans[L][LC],l[L],r[L],a[N];
void updateblock(int i)
{
  rep(k,0,LC)
    {
      int curr=k;
      int cnt=0;
      rep(j,l[i],r[i]+1)
	{
	  if(curr%a[j]==0) curr+=2,cnt+=2;
	  else curr++,cnt++;
	  curr%=LC;
	}
      ans[i][k]=cnt;
    }
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n;
  cin>>n;
  rep(i,0,L) l[i]=N,r[i]=0;
  rep(i,1,n+1)
    {
      cin>>a[i],block[i]=i/sq;
      l[block[i]]=min(l[block[i]],i);
      r[block[i]]=max(r[block[i]],i);
    }
  int tot=n/sq;
  rep(i,0,tot+1) updateblock(i);
  int q;
  cin>>q;
  while(q--)
    {
      char ch;
      int x,y;
      cin>>ch>>x>>y;
      if(ch=='C')
	{
	  a[x]=y;
	  updateblock(block[x]);
	}
      else
	{
	  y--;
	  if(block[y]-block[x]<=1)
	    {
	      int curr=0;
	      rep(i,x,y+1)
		{
		  if(curr%a[i]==0) curr+=2;
		  else curr++;
		}
	      cout<<curr<<endl;
	    }
	  else
	    {
	      int curr=0;
	      rep(i,x,r[block[x]]+1)
		{
		  if(curr%a[i]==0) curr+=2;
		  else curr++;
		}
	      rep(i,block[x]+1,block[y])
		{
		  int tmp=curr%LC;
		  curr+=ans[i][tmp];
		}
	      rep(i,l[block[y]],y+1)
		{
		  if(curr%a[i]==0) curr+=2;
		  else curr++;
		}
	      cout<<curr<<endl;
	    }
	}
    }
  return 0 ;
}
