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
//http://ceoi.inf.elte.hu/probarch/16/match-solution.pdf
const int N=100005,L=26;
int pre[L][N];
string s;
string solve(int l,int r)
{
  assert(((r-l)&1)==1);
  if(s[l]==s[r])
    {
      string ans="(";
      if(r-1>l+1) ans+=solve(l+1,r-1);
      ans+=")";
      return ans;
    }
  int ind=pre[s[l]-'a'][r];
  assert(ind>l);
  string ans="(";
  if(ind-1>l+1) ans+=solve(l+1,ind-1);
  ans+=")";
  if(r>ind+1) ans+=solve(ind+1,r);
  return ans;
}
bool check(string s,int n)
{
  stack<int> st;
  rep(i,1,n+1)
    {
      if(st.empty() || s[st.top()]!=s[i]) st.push(i);
      else st.pop();
    }
  if(!st.empty())
    {
      cout<<-1<<endl;
      exit(0);
    }
}
int main()
{
  std::ios::sync_with_stdio(false);
  cin.tie(NULL) ; cout.tie(NULL) ;
  cin>>s;
  int n=sz(s);
  s="#"+s;
  check(s,n);
  rep(i,3,n+1)
    {
      rep(j,0,26)
	{
	  if(s[i]==s[i-1])
	    {
	      if(((int)(s[i-2]-'a'))==j) pre[j][i]=i-2;
	      else pre[j][i]=pre[j][i-2];
	    }
	  else
	    {
	      int tmp=pre[(int)(s[i]-'a')][i-1];
	      if(!tmp) continue;
	      tmp--;
	      if(!tmp) continue;
	      if(((int)(s[tmp]-'a'))==j)
		{
		  pre[j][i]=tmp;
		  continue;
		}
	      pre[j][i]=pre[j][tmp];
	    }
	}
    }
  cout<<solve(1,n)<<endl;
  return 0 ;
}
