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
//sort by x+y, prefix for bridge B1, and suffix for bridge B2
const int N=100005;
int st[N],en[N],cnt,ind[N];
void adjust(multiset<int> &x,multiset<int> &y,ll &sum1,ll &sum2)
{
  while(sz(y)>sz(x))
    {
      int tmp=*y.begin(); sum2-=tmp;
      y.erase(y.begin()); x.insert(tmp); sum1+=tmp;
    }
  while(sz(x)>sz(y)+1)
    {
      int tmp=*x.rbegin(); sum1-=tmp;
      x.erase(x.find(tmp)); y.insert(tmp); sum2+=tmp;
    }
}
void insert(multiset<int> &x,multiset<int> &y,ll &sum1,ll &sum2,ll val)
{
  if(!sz(x))
    {
      x.insert(val); sum1+=val;
      return;
    }
  if(*x.rbegin()>=val) x.insert(val),sum1+=val;
  else y.insert(val),sum2+=val;
  adjust(x,y,sum1,sum2);
}
void erase(multiset<int> &x,multiset<int> &y,ll &sum1,ll &sum2,ll val)
{
  if(*x.rbegin()>=val) x.erase(x.find(val)),sum1-=val;
  else y.erase(y.find(val)),sum2-=val;
  adjust(x,y,sum1,sum2);
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  int k,n;
  cin>>k>>n;
  ll sum=0;
  rep(i,1,n+1)
    {
      char x,y;
      int st,en;
      cin>>x>>st>>y>>en;
      if(st>en) swap(st,en);
      if(x==y) sum+=en-st;
      else
	{
	  cnt++;
	  ::st[cnt]=st; ::en[cnt]=en;
	  ind[cnt]=cnt;
	}
    }
  sort(ind+1,ind+cnt+1,[](int i,int j){ return ((st[i]+en[i]!=st[j]+en[j])?((st[i]+en[i])<(st[j]+en[j])):(st[i]<st[j]));});
  ll ans=LLONG_MAX;
  multiset<int> s1,s2,s3,s4;
  ll sum1=0,sum2=0,sum3=0,sum4=0;
  rep(i,1,cnt+1)
    {
      insert(s3,s4,sum3,sum4,st[ind[i]]);
      insert(s3,s4,sum3,sum4,en[ind[i]]);
    }
  rep(i,0,cnt+1)
    {
      ll curr=0;
      if(sz(s1))
	{
	  auto it=*s1.rbegin();
	  int sz1=sz(s1),sz2=sz(s2);
	  auto it2=*s2.begin();
	  ll curr1=(ll)sz1*it-sum1+sum2-(ll)sz2*it;
	  ll curr2=(ll)sz1*it2-sum1+sum2-(ll)sz2*it2;
	  curr+=min(curr1,curr2);
	}
      if(sz(s3))
	{
	  auto it=*s3.rbegin();
	  int sz1=sz(s3),sz2=sz(s4);
	  auto it2=*s4.begin();
	  ll curr1=(ll)sz1*it-sum3+sum4-(ll)sz2*it;
	  ll curr2=(ll)sz1*it2-sum3+sum4-(ll)sz2*it2;
	  curr+=min(curr1,curr2);
	}
      curr+=cnt;
      ans=min(ans,curr);
      if(k==1) break;
      if(i==cnt) continue;
      erase(s3,s4,sum3,sum4,st[ind[i+1]]);
      erase(s3,s4,sum3,sum4,en[ind[i+1]]);
      insert(s1,s2,sum1,sum2,st[ind[i+1]]);
      insert(s1,s2,sum1,sum2,en[ind[i+1]]);
    }
  if(ans==LLONG_MAX) ans=0;
  ans+=sum;
  cout<<ans<<endl;
  return 0 ;
}
