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
/*answer for a particular element with index i, Let elements smaller than it be x, and larger than it be y
answer is C(x,x)(C(y,x)+C(y,x-1)+..+C(y,0)) + C(x,x-1) (C(y,x-1)+... + C(y,0)) + ... + C(x,0) C(y,0)
this can be reduced to C(x,x) C(y,x) + C(x,x-1) C(y,x-1) +..... +C(x,0)C(y,0)
+ C(x,x) C(y,x-1) + C(x,x-1) C(y,x-2) +.......... + C(x,1) C(y,0)
+ ....
+ C(x,x) C(y,0)
which is equal to
summation i=0 to x summation j = 0 to x  { C(x,x-j) * C(y,i-j) } 
= sumi sumj { C(x,j) C(n-1-x,i-j) }
= sumi C(n-1,i) [USING PASCAL IDENTITY]
*/
const int N=100005,mod=1e9+7;
int f[N],inv[N];
int add(int x,int y)
{
  x+=y;
  if(x>=mod) x-=mod;
  if(x<0) x+=mod;
  return x;
}
int mult(int x,int y)
{
  ll tmp=(ll)x*y;
  if(tmp>=mod) tmp%=mod;
  return tmp;
}
int pow1(int x,int y)
{
  int ans=1;
  while(y)
    {
      if(y&1) ans=mult(ans,x);
      x=mult(x,x);
      y>>=1;
    }
  return ans;
}
int ncr(int x,int y)
{
  if(y<0 || y>x) return 0;
  return mult(f[x],mult(inv[y],inv[x-y]));
}
int a[N];
map<int,int> m;
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  f[0]=inv[0]=1;
  rep(i,1,N) f[i]=mult(f[i-1],i);
  inv[N-1]=pow1(f[N-1],mod-2);
  repv(i,1,N-1)
    {
      inv[i]=mult(inv[i+1],i+1);
      assert(mult(inv[i],f[i])==1);
    }
  int n,q;
  cin>>n>>q;
  rep(i,1,n+1)
    cin>>a[i];
  sort(a+1,a+n+1);
  int sum=0;
  rep(i,1,n+1)
    {
      int tmp=ncr(n-1,i-1);
      sum=add(sum,tmp);
      m[a[i]]=sum;
    }
  while(q--)
    {
      int val;
      cin>>val;
      cout<<m[val]<<endl;
    }
  return 0 ;
}
