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
const int N=505;
#define lc (pos)+(pos)
#define rc (lc)|1

int n;
struct segy
{
  ll seg[4*N],lazy[4*N];
  void update(int low,int high,int pos,int y1,int y2,int len,ll val)
  {
    if(low>y2 || high<y1) return;
    if(low>=y1 && high<=y2)
      {
	if(len&1) lazy[pos]^=val;
	return;
      }
    int mid=(low+high)>>1;
    update(low,mid,lc,y1,y2,len,val);
    update(mid+1,high,rc,y1,y2,len,val);
    int sz=(min(y2,high)-max(y1,low)+1)*len;
    if(sz&1) seg[pos]^=val;
  }
  ll query(int low,int high,int pos,int y1,int y2,int len)
  {
    if(low>y2 || high<y1) return 0;
    if(low>=y1 && high<=y2)
      {
	ll tmp=seg[pos];
	int sz=high-low+1;
	if(sz&1) tmp^=lazy[pos];
	return tmp;
      }
    int mid=(low+high)>>1;
    ll tmp=(query(low,mid,lc,y1,y2,len)^query(mid+1,high,rc,y1,y2,len));
    int sz=(min(y2,high)-max(y1,low)+1);
    if(sz&1) tmp^=lazy[pos];
    return tmp;
  }
};

struct segx
{
  segy seg[4*N],lazy[4*N];
  void update(int low,int high,int pos,int x1,int x2,int y1,int y2,ll val)
  {
    if(low>x2 || high<x1) return;
    if(low>=x1 && high<=x2)
      {
	lazy[pos].update(1,n,1,y1,y2,high-low+1,val);
	return;
      }
    int mid=(low+high)>>1;
    update(low,mid,lc,x1,x2,y1,y2,val);
    update(mid+1,high,rc,x1,x2,y1,y2,val);
    int sz=min(x2,high)-max(x1,low)+1;
    if(sz%2==0) val=0;
    seg[pos].update(1,n,1,y1,y2,sz,val);
  }
  ll query(int low,int high,int pos,int x1,int x2,int y1,int y2)
  {
    if(low>x2 || high<x1) return 0;
    if(low>=x1 && high<=x2)
      {
	ll tmp=seg[pos].query(1,n,1,y1,y2,high-low+1);
	int sz=high-low+1;
	if(sz&1) 
	  tmp^=lazy[pos].query(1,n,1,y1,y2,high-low+1);
	return tmp;
      }
    int mid=(low+high)>>1;
    ll tmp=(query(low,mid,lc,x1,x2,y1,y2)^query(mid+1,high,rc,x1,x2,y1,y2));
    int sz=min(x2,high)-max(x1,low)+1;
    if(sz&1) 
      tmp^=lazy[pos].query(1,n,1,y1,y2,sz);
    return tmp;
  }
};
segx seg;
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; 
  int q;
  cin>>n>>q;
  while(q--)
    {
      int ch,x1,y1,x2,y2;
      cin>>ch>>x1>>y1>>x2>>y2;
      if(ch==1) cout<<seg.query(1,n,1,x1,x2,y1,y2)<<endl;
      else
	{
	  ll val;
	  cin>>val;
	  seg.update(1,n,1,x1,x2,y1,y2,val);
	}
    }
  return 0 ;
}
