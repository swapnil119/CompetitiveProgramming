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
int findSample(int n,int confidence[],int host[],int protocol[])
{
  int extracost=0;
  repv(i,1,n)
    {
      if(protocol[i]==1)//my friends are your friends
	{
	  //in this case we can remove this node and update weight of host by sum of weights as optimal soln can use both nodes
	  confidence[host[i]]+=confidence[i];
	}
      else if(protocol[i]==2)//we are your friends
	{
	  //in this case we will remove this node and use one with greater weight, so update host weight with max of both weights
	  confidence[host[i]]=max(confidence[host[i]],confidence[i]);
	}
      else//i am your friend
	{
	  //go with assumption that i will go into optimal soln and if we change our opinion and take its host, then reduce its cost, so subtract its cost from its host
	  confidence[host[i]]-=confidence[i];
	  confidence[host[i]]=max(0,confidence[host[i]]);
	  extracost+=confidence[i];
	}
    }
  return extracost+confidence[0];
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int n;
  cin>>n;
  int confidence[n],host[n],protocol[n];
  rep(i,0,n) cin>>confidence[i];
  rep(i,1,n) cin>>host[i]>>protocol[i];
  cout<<findSample(n,confidence,host
  return 0 ;
}
