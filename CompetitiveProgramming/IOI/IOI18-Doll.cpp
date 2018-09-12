#include <bits/stdc++.h>
#include "doll.h"
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
vi X,Y;
int cnt=0,p=1,n;
bool state[N*10];
int build(int low,int high)
{
  if(low>=high) return 0;
  if(high<p-n) return -1;
  int mid=(low+high)>>1;
  int ind=++cnt;
  X.pb(0); Y.pb(0);
  int x=build(low,mid),y=build(mid+1,high);
  X[ind-1]=x;
  Y[ind-1]=y;
  return -ind;
}
void solve(int ind,int nxt)
{
  int &curr=((state[-ind])?Y[-ind-1]:X[-ind-1]);
  state[-ind]=!state[-ind];
  if(curr==0) curr=nxt;
  else solve(curr,nxt);
}
void create_circuit(int m,vi A)
{
  n=sz(A);
  if(n==1)
    {
      vi C(m+1,0);
      C[0]=A[0];
      return answer(C,X,Y);
    }
  while(p<n) p<<=1;
  build(0,p-1);
  rep(i,1,n) solve(-1,A[i]);
  if(n&1) solve(-1,-1);
  solve(-1,0);
  vi C(m+1,-1);
  C[0]=A[0];
  answer(C,X,Y);
}
